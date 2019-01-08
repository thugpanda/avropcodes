#include <avr/pgmspace.h>
#include <avr/io.h>
#include <Arduino.h>

#include "InstructionSniffer.h"
#include <AccelStepper.h>

#define MEMSIZE 0x1A74

// #define pgm_read_word_near(address_short) __LPM_word((uint16_t)(address_short))
// #define pgm_read_byte_near(address_short) __LPM((uint16_t)(address_short))

// word        flashAddress    =   0;
// word        pgm_word        =   0;

InstructionSniffer sniffer(MEMSIZE);
AccelStepper stepper;

void setup() {
    Serial.begin(115200);
    while(!Serial);

    stepper.setMaxSpeed(250);
    stepper.setAcceleration(75);
    // Serial.println("Hi, I am here and ready to communicate.");

    // for(int pFlash=0x0; pFlash<=MEMSIZE; pFlash++) {
    //     byte    __returnCode    =   sniffer.findInstruction(pFlash);
    //     if(__returnCode > 220) {
    //         break;
    //     // } else if(__returnCode<3) {
    //     //     Serial.print(sniffer.returnInstructionWord(__returnCode),HEX);
    //     //     Serial.print(" at ");
    //     //     Serial.print(pFlash);
    //     //     pFlash++;
    //     // } else if(__returnCode<200) {
    //     //     Serial.print(sniffer.returnInstructionWord(__returnCode),HEX);
    //     //     Serial.print(" at ");
    //     //     Serial.println(pFlash);
    //     // }
    //     } else {
    //         Serial.print("0x");
    //         Serial.println(sniffer.returnInstructionWord(__returnCode),HEX);
    //         // Serial.print(",");
    //     }
    // }
}

void loop() {
    for(int pFlash=0x0; pFlash<=MEMSIZE; pFlash++) {
        byte        __returnCode    =   sniffer.findInstruction(pFlash);

        if(__returnCode == 0x1C | __returnCode == 0xC | __returnCode == 0x96) {
            Serial.print(__returnCode,HEX);
            Serial.print(" found at 0x");
            Serial.println(pFlash,HEX);
            stepper.setMaxSpeed(250);
            stepper.run();
        } else if(__returnCode == 0x8 | __returnCode == 0x40 | __returnCode == 0x97 | __returnCode == 0x18 | __returnCode == 0x50) {
            Serial.print(__returnCode,HEX);
            Serial.print(" found at 0x");
            Serial.println(pFlash,HEX);
            stepper.setMaxSpeed(-250);
            stepper.run();
        }
    }
}