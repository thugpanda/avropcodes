#include <InstructionSniffer.h>
#include <Wire.h>

#define MASTER 1

InstructionSniffer sniffer(0x8000);

void setup() {
    Serial.begin(115200);
    while(!Serial);
    Serial.println("Starting to sniff");

    Wire.begin();
    Wire.onReceive(receiveHandler);

    DDRD    =   0b11111100;
    DDRB    =   0b00111111;
    DDRC    =   0b00001111;
}

void loop() {
    for(word pFlash = 0; pFlash<0x8000; pFlash++) {
        word    instructionType     =   sniffer.findInstruction(pFlash);
        word    firstpayload        =   sniffer.getFirstPayloadAddress(pFlash);
        word    firstpayloadSRAM    =   sniffer.getPayloadFromSRAMW(firstpayload);

        Serial.print("Found 0x");
        Serial.print(sniffer.findInstruction(pFlash),HEX);
        Serial.print("\tat address 0x");
        Serial.print(pFlash);
        Serial.print("\twith first address payload 0x");
        Serial.println(firstpayload,HEX);
        Serial.print("\twith value in SRAM::0x");
        Serial.println(firstpayloadSRAM,HEX);
        delay(100);
        //PORTD   =   firstpayload<<2;
        //PORTB   =   firstpayload>>6;
        //PORTC   =   firstpayload>>12;
        PORTD   =   instructionType<<2;
        PORTB   =   instructionType>>6;
        PORTC   =   instructionType>>12;

        delay(250);
        PORTD   =   0x0;
        PORTB   =   0x0;
        PORTC   =   0x0;
    }

    // while(Serial.available() > 0) {
    //     word    pFlash  =   Serial.parseInt();

    //             PORTD   =   pFlash<<2;
    //             PORTB   =   pFlash>>6;
    //             PORTC   =   pFlash>>12;

    //             Serial.print("Got ");
    //             Serial.print(pFlash);
    //             Serial.println(" and writing it to PORTS");
    // }
}

void receiveHandler(byte __no) {
	sniffer.wireReceiveHandlerMaster(__no);
}
