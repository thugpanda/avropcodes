#include <InstructionSniffer.h>
#include <Wire.h>

#define MASTERSPI 32
#define SLAVESPI 9
#define NO_OF_SLAVES 4
#define SPI true

InstructionSniffer sniffer(SPI);

byte    currentSlave    =   0;


void setup() {
    Serial.begin(115200);
    while(!Serial);
    Serial.println("Starting to sniff");
    Wire.begin();
    // Wire.onReceive(receiveHandler);
//    resetBus();
    for(byte i=0; i<NO_OF_SLAVES; i++) {
        resetBus(i);
        Serial.print("Reset Bus ");
        Serial.println(i);
    }

    DDRD    =   0xFC;
    DDRB    =   0x3F;
    DDRC    =   0xF;
}

void loop() {
    Serial.print("----------------\n----------------\nTalking to Slave #");
    Serial.println(currentSlave);
    for(word pFlash = 0; pFlash < 0x80; pFlash++) {
        word    slavePGM    =   0;
//        Serial.println("Requesting...");
        Wire.requestFrom(currentSlave, 2);
        while(Wire.available() == 2) {
//          Serial.println("2b available");
            slavePGM        =   (Wire.read())<<0x8;
        }
        while(Wire.available() == 1) {
//          Serial.println("1b available");
            slavePGM        |=  Wire.read();
        }
        
//          Serial.println("No available");
        word    instruction =   sniffer.OTFfindInstruction(slavePGM);

        if(instruction == 0x0) {
            Serial.print("Found no instruction at 0x");
            Serial.println(pFlash,HEX);
        } else {
            Serial.print("Found 0x");
            Serial.print(instruction,HEX);
            Serial.print(" at address 0x");
            Serial.println(pFlash,HEX);
        }

        delay(100);

        PORTD               =   instruction<<2;
        PORTB               =   instruction>>6;
        PORTC               =   instruction>>12;

        delay(100);

        PORTD               =   0x0;
        PORTB               =   0x0;
        PORTC               =   0x0;
    }
    resetBus();
    currentSlave++;
    currentSlave    %=  NO_OF_SLAVES;
}

void resetBus() {
    Wire.beginTransmission(currentSlave);
    Wire.write(0x0);
    Wire.endTransmission();
}

void resetBus(byte address) {
    Wire.beginTransmission(address);
    Wire.write(0x0);
    Wire.endTransmission();
}
