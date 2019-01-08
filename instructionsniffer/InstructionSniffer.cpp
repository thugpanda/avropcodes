#include "Arduino.h"
#include "InstructionSniffer.h"

#define pgm_read_word_near(address_short) __LPM_word((uint16_t)(address_short))

InstructionSniffer::InstructionSniffer(word __pgmLength) {
    word    pgmLength   =   __pgmLength;
    initInstructionCodes();
}

word InstructionSniffer::findInstruction(word __pFlash) {
    word    pgmRead         =   pgm_read_word_near(__pFlash);
    byte    pgmReadByte     =   pgmRead>>8;

    for(int i=0; i<3; i++) {
        if(((pgmRead & doubleWordInstructionCode[i])^doubleWordInstructionCode[i]) == 0) {
            return i;
        }
    }

    for(int i=0; i<30; i++) {
        if((pgmRead^fixedInstructionsCode[i]) == 0) {
            return i+3;
        }
    }
    
    for(int i=0; i<60; i++) {
        if(((pgmRead & singleWordInstructionCode[i]) ^ singleWordInstructionCode[i]) == 0) {
            return i+33;
        }
    }

    for(int i=0; i<40; i++) {
        if(((pgmReadByte & oneByteInstructions[i]) ^ oneByteInstructions[i]) == 0 ) {
            return i+93;
        }
    }

    return 0;
}

unsigned long InstructionSniffer::returnInstructionWord(byte __pos) {
    if(__pos<3) {
        return doubleWordInstructionCode[__pos];
    } else if(__pos<33) {
        return fixedInstructionsCode[__pos-3];
    } else if(__pos<93) {
        return singleWordInstructionCode[__pos-33];
    } else if(__pos<=133) {
        return oneByteInstructions[__pos-93];
    }
    return 225;
}

// String InstructionSniffer::returnInstructionString(byte __pos) {
//     if(__pos<3) {
//         return doubleWordStrings[__pos];
//     } else if(__pos<33) {
//         return fixedInstructionsStrings[__pos-3];
//     } else if(__pos<93) {
//         return singleWordInstructionString[__pos-33];
//     } else if(__pos<=133) {
//         return oneByteStrings[__pos-93];
//     }

//     return "NULL";
// }

