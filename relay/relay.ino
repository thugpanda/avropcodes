#include <InstructionSniffer.h>
#include <Arduino.h>

InstructionSniffer sniffer(0x8000);

void setup() {
    Serial.begin(115200);
    while(!Serial);
    Serial.println("Starting to sniff");

    DDRD    =   0b11111100;
    DDRB    =   0b00111111;
    DDRC    =   0b00001111;
}

void loop() {
    for(word pFlash = 0; pFlash<0x8000; pFlash++) {
        word    instructionType     =   sniffer.findInstruction(pFlash);
        word    firstpayload        =   sniffer.getFirstPayload(pFlash);

        Serial.print("Found 0x");
        Serial.print(sniffer.findInstruction(pFlash),HEX);
        Serial.print(" at address 0x");
        Serial.print(pFlash);
        Serial.print(" with first payload 0x");
        Serial.println(firstpayload,HEX);
        delay(100);
        PORTD   =   firstpayload<<2;
        PORTB   =   firstpayload>>6;
        PORTC   =   firstpayload>>12;

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
