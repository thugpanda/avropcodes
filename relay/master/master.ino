#include <InstructionSniffer.h>
#include <Wire.h>

#define MASTERSPI 8
#define SLAVESPI 9
#define SPI true

InstructionSniffer sniffer(SPI);


void setup() {
    Serial.begin(115200);
    while(!Serial);
    Serial.println("Starting to sniff");
    Wire.begin();
    // Wire.onReceive(receiveHandler);
    resetBus();

    DDRD    =   0xFC;
    DDRB    =   0x3F;
    DDRC    =   0xF;
}

void loop() {
    for(word pFlash = 0; pFlash < 0x8000; pFlash++) {
        word    slavePGM    =   0;
        Wire.requestFrom(SLAVESPI, 2);
        while(Wire.available() == 2) {
            slavePGM        =   (Wire.read())<<0x8;
        }
        while(Wire.available() == 1) {
            slavePGM        |=  Wire.read();
        }
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

        delay(250);

        PORTD               =   0x0;
        PORTB               =   0x0;
        PORTC               =   0x0;
    }
}

void resetBus() {
    Wire.beginTransmission(SLAVESPI);
    Wire.write(0x0);
    Wire.endTransmission();
}