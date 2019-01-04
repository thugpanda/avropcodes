byte    movCheck    =   0b00101100;
byte    addCheck    =   0b00001100;
byte    subCheck    =   0b00011000;
byte    eorCheck    =   0b00100100;

byte checkForMovInstruction(word __local) {
    byte    movCheck                =   0b00101100;
    byte    __localInstructionPart  =   __local>>8;
            __localInstructionPart  &=  ~(1<<0);
            __localInstructionPart  &=  ~(1<<1);

    byte    returnInstruction       =   __localInstructionPart ^ movCheck;

    return returnInstruction;
}

byte checkForInstruction(word __local) {
    byte    __localInstructionPart  =   __local>>8;
            __localInstructionPart  &=  ~(1<<0);
            __localInstructionPart  &=  ~(1<<1);

    if((__localInstructionPart^movCheck) == 0) {
        return 0;
    } else if((__localInstructionPart^addCheck) == 0) {
        return 1;
    } else if((__localInstructionPart^subCheck) == 0) {
        return 2;
    } else if((__localInstructionPart^eorCheck) == 0) {
        return 3;
    }

    return 4;
}

byte loadNextWord(word __pFlash) {
    word    __pgmWord           =   pgm_read_word_near(__pFlash);

    byte    __nextInstruction   =   checkForInstruction(__pgmWord);

    return __nextInstruction;
}