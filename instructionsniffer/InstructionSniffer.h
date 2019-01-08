#ifndef InstructionSniffer_h
#define InstructionSniffer_h

#if (ARDUINO>=100)
    #include <Arduino.h>
#else
    #include <wProgram.h>
#endif

class InstructionSniffer {
    public:
                    InstructionSniffer(word __pgmLength);
    word            findInstruction(word __pFlash);
    unsigned long   returnInstructionWord(byte __pos);
    // String          returnInstructionString(byte __pos);

    private:
    void            initInstructionCodes();
    word            pgmLength;

    byte    oneByteInstructions[40]   =   {
                                                0x1C, 0xC, 0x96, 0x70, 0x94, 0xF8, 0xF4, 0xF0,
                                                0x98, 0x24, 0x14, 0x4, 0x30, 0x10, 0xB0, 0xE0,
                                                0xA0, 0x2C, 0x1, 0x9C, 0x2, 0x28, 0x60, 0xB8,
                                                0xD0, 0xC0, 0x8, 0x40, 0x9A, 0x99, 0x9B, 0x97,
                                                0xA8, 0x18, 0x50, 0x20
                                            };
    // String  oneByteStrings[40]        =   {
    //                                             "ADC", "ADD", "ADIW", "ANDICBR", "ASR", "BLD", "BRBC", "BRBS",
    //                                             "CBI", "CLREOR", "CP", "CPC", "CPI", "CPSE", "IN", "LDI",
    //                                             "LSL", "MOV", "MOVW", "MUL", "MULS", "OR", "OSRISBR", "OUT",
    //                                             "RCALL", "RJMP", "SBC", "SBCI", "SBI", "SBIC", "SBIS", "SBIW",
    //                                             "STS16", "SUB", "SUBI", "TSTAND"
    //                                         };

    /* Below are the AVR-Instructions for Bitmasking */

    /* 1-Byte Instructions */
    // byte    adc     =   0x1C;
    // byte    add     =   0b00001100;
    // byte    adiw    =   0x96;
    // byte    andicbr =   0x70;
    // byte    asr     =   0x94;
    // byte    bld     =   0xF8;
    // byte    brbc    =   0xF4;
    // byte    brbs    =   0xF0;
    // byte    cbi     =   0x98;
    // byte    clreor  =   0x24;
    // byte    cp      =   0x14;
    // byte    cpc     =   0x4;
    // byte    cpi     =   0x30;
    // byte    cpse    =   0x10;
    // byte    in      =   0xB0;
    // byte    ldi     =   0xE0;
    // byte    lsl     =   0xA0;
    // byte    mov     =   0x2C;
    // byte    movw    =   0x1;
    // byte    mul     =   0x9C;
    // byte    muls    =   0x2;
    // byte    or_     =   0x28;
    // byte    orisbr  =   0x60;
    // byte    out     =   0xB8;
    // byte    rcall   =   0xD0;
    // byte    rjmp    =   0xC0;
    // byte    sbc     =   0x8;
    // byte    sbci    =   0x40;
    // byte    sbi     =   0x9A;
    // byte    sbic    =   0x99;
    // byte    sbis    =   0x9B;
    // byte    sbiw    =   0x97;
    // byte    sts16   =   0xA8;
    // byte    sub     =   0x18;
    // byte    subi    =   0x50;
    // byte    tstand  =   0x20;

    /* fixed instruction word */

    byte    fixedInstructionsCode[30]     = {
                                                0x9598, 0x9488, 0x94D8, 0x94F8, 0x94A8, 0x94C8, 0x94E8, 0x94B8,
                                                0x9498, 0x9519, 0x9419, 0x95D8, 0x9509, 0x9409, 0x95C8, 0x0,
                                                0x9508, 0x9518, 0x9408, 0x9458, 0x9478, 0x9428, 0x9448, 0x9468,
                                                0x9438, 0x9418, 0x9588, 0x95E8, 0x95F8, 0x95A8
                                            };
    
    // String  fixedInstructionsStrings[30]  = {
    //                                             "BREAK", "CLC", "CLH", "CLI", "CLN", "CLS", "CLT", "CLV",
    //                                             "CLZ", "EICALL", "EIJMP", "ELPM1", "ICALL", "IJMP", "LPM1", "NOP",
    //                                             "RET", "RETI", "SEC", "SEH", "SEI", "SEN", "SES", "SET",
    //                                             "SEV", "SEZ", "SLEEP", "SPM", "SPM2", "WDR"
    //                                         };

    // word    break_  =   0x9598;
    // word    clc     =   0x9488;
    // word    clh     =   0x94D8;
    // word    cli     =   0x94F8;
    // word    cln     =   0x94A8;
    // word    cls     =   0x94C8;
    // word    clt     =   0x94E8;
    // word    clv     =   0x94B8;
    // word    clz     =   0x9498;
    // word    eicall  =   0x9519;
    // word    eijmp   =   0x9419;
    // word    elpm1   =   0x95D8;
    // word    icall   =   0x9509;
    // word    ijmp    =   0x9409;
    // word    lpm1    =   0x95C8;
    // word    nop     =   0x0;
    // word    ret     =   0x9508;
    // word    reti    =   0x9518;
    // word    sec     =   0x9408;
    // word    seh     =   0x9458;
    // word    sei     =   0x9478;
    // word    sen     =   0x9428;
    // word    ses     =   0x9448;
    // word    set     =   0x9468;
    // word    sev     =   0x9438;
    // word    sez     =   0x9418;
    // word    sleep   =   0x9588;
    // word    spm     =   0x95E8;
    // word    spm2    =   0x95F8;
    // word    wdr     =   0x95A8;

    /* double word instructions */

    unsigned    long    doubleWordInstructionCode[3]    =   {0x940E0000, 0x90000000, 0x92000000};
                // String  doubleWordStrings[3]            =   {"CALLJMP", "LDS", "STS"};

    // unsigned    long    calljmp =   0x940E0000;
    // unsigned    long    lds     =   0x90000000;
    // unsigned    long    sts     =   0x92000000;

    /* dynamic single word instructions */

    word    singleWordInstructionCode[60]   =   {
                                                    0xF400, 0xF000, 0xF001, 0xF404, 0xF405, 0xF005, 0xF407, 0xF007,
                                                    0xF004, 0xF002, 0xF401, 0xF402, 0xF406, 0xF006, 0xF403, 0xF003,
                                                    0x9408, 0xFA00, 0x9400, 0x940A, 0x940B, 0x9006, 0x9007, 0x308,
                                                    0x380, 0x388, 0x9403, 0x9206, 0x9205, 0x9207, 0x900C, 0x900D,
                                                    0x900E, 0x8008, 0x9009, 0x900A, 0x8000, 0x9001, 0x9002, 0x9004,
                                                    0x9005, 0x9406, 0x300, 0x9401, 0x900F, 0x920F, 0xD407, 0xFC00,
                                                    0xFE00, 0x920C, 0x920D, 0x920E, 0x8208, 0x9209, 0x920A, 0x8200,
                                                    0x9201, 0x9202, 0x9402, 0x9204
                                                };

    // String  singleWordInstructionString[60] =   {
    //                                                 "BRCC", "BRCS", "BREQ", "BRGE", "BRGC", "BRHS", "BRID", "BRIE",
    //                                                 "BRLT", "BRMI", "BRNE", "BRPL", "BRTC", "BRTS", "BRVC", "BRVS",
    //                                                 "BSET", "BST", "COMP", "DEC", "DES", "ELPM2", "ELPM3", "FMUL",
    //                                                 "FMULS", "FMULSU", "INC", "LAC", "LAS", "LAT", "LD1", "LD2",
    //                                                 "LD3", "LDD1", "LDD2", "LDD3", "LDD4", "LDD5", "LDD6", "LPM2",
    //                                                 "LPM3", "LSR", "MULSU", "NEG", "POP", "PUSH", "ROR", "SBRC",
    //                                                 "SBRS", "ST1", "ST2", "ST3", "STD1", "STD2", "STD3", "STD4",
    //                                                 "STD5", "STD6", "SWAP", "XCH"
    //                                             };

    // word    brcc    =   0xF400;
    // word    brcs    =   0xF000;
    // word    breq    =   0xF001;
    // word    brge    =   0xF404;
    // word    brgc    =   0xF405;
    // word    brhs    =   0xF005;
    // word    brid    =   0xF407;
    // word    brie    =   0xF007;
    // word    brlt    =   0xF004;
    // word    brmi    =   0xF002;
    // word    brne    =   0xF401;
    // word    brpl    =   0xF402;
    // word    brtc    =   0xF406;
    // word    brts    =   0xF006;
    // word    brvc    =   0xF403;
    // word    brvs    =   0xF003;
    // word    bset    =   0x9408;
    // word    bst     =   0xFA00;
    // word    comp    =   0x9400;
    // word    dec     =   0x940A;
    // word    des     =   0x940B;
    // word    elpm2   =   0x9006;
    // word    elpm3   =   0x9007;
    // word    fmul    =   0x308;
    // word    fmuls   =   0x380;
    // word    fmulsu  =   0x388;
    // word    inc     =   0x9403;
    // word    lac     =   0x9206;
    // word    las     =   0x9205;
    // word    lat     =   0x9207;
    // word    ld1     =   0x900C;
    // word    ld2     =   0x900D;
    // word    ld3     =   0x900E;
    // word    ldd1    =   0x8008;
    // word    ldd2    =   0x9009;
    // word    ldd3    =   0x900A;
    // word    ldd4    =   0x8000;
    // word    ldd5    =   0x9001;
    // word    ldd6    =   0x9002;
    // word    lpm2    =   0x9004;
    // word    lpm3    =   0x9005;
    // word    lsr     =   0x9406;
    // word    mulsu   =   0x300;
    // word    neg     =   0x9401;
    // word    pop     =   0x900F;
    // word    push    =   0x920F;
    // word    ror     =   0xD407;
    // word    sbrc    =   0xFC00;
    // word    sbrs    =   0xFE00;
    // word    st1     =   0x920C;
    // word    st2     =   0x920D;
    // word    st3     =   0x920E;
    // word    std1    =   0x8208;
    // word    std2    =   0x9209;
    // word    std3    =   0x920A;
    // word    std4    =   0x8200;
    // word    std5    =   0x9201;
    // word    std6    =   0x9202;
    // word    swap    =   0x9402;
    // word    xch     =   0x9204;
}

#endif
;