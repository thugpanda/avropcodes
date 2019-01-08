void settings() {
    size(800,760,P2D);
}

void setup() {

    noStroke();
    colorMode(HSB,360,255,255);

    String[]    lines   =   loadStrings("instructions.txt");
    long[]      opcodes =   new long[lines.length];

    for(int i=0; i<lines.length; i++) {
        opcodes[i]      =   int(lines[i]);
        println(opcodes[i]);
    }
        for(int j=0; j<38; j++) {
            for(int k=0; k<40; k++) {
                fill(0,0,255);
                if(opcodes[j*k] == 0x0) {
                    //NOP
                    fill(0);
                } else if(opcodes[j*k] == 0x2C | opcodes[j*k] == 0x1) {
                    //MOV
                    fill(0,255,255);
                } else if(opcodes[j*k] == 0x1C | opcodes[j*k] == 0xC || opcodes[j*k] == 0x96) {
                    //ADC, ADD, ADIW
                    fill(30,255,255);
                } else if(opcodes[j*k] == 8 | opcodes[j*k] == 64 | opcodes[j*k] == 151 | opcodes[j*k] == 24 | opcodes[j*k] == 80) {
                    //SBC,SBCI,SBIW,SUB,SUBI
                    fill(30,150,255);
                } else if(opcodes[j*k] == 776 | opcodes[j*k] == 896 | opcodes[j*k] == 904 | opcodes[j*k] == 156 | opcodes[j*k] == 2 | opcodes[j*k] == 768) {
                    //FMUL,FMULS,FMULSU,MUL,MULS,MULSU
                    fill(30,255,200);
                } else if(opcodes[j*k] == 32 | opcodes[j*k] == 112 | opcodes[j*k] == 40 | opcodes[j*k] == 96 | opcodes[j*k] == 36) {
                    if(opcodes[j*k] == 32 | opcodes[j*k] == 112) {
                        //AND,ANDI
                        fill(60,255,255);
                    } else if(opcodes[j*k] == 36) {
                        //EOR
                        fill(60,150,255);
                    } else if(opcodes[j*k] == 40 | opcodes[j*k] == 96) {
                        //OR,ORI
                        fill(60,255,200);
                    }
                } else if(opcodes[j*k] == 36876 | opcodes[j*k] == 36877 | opcodes[j*k] == 36878) {
                    //LD1,LD2,LD3
                    fill(90,255,200);
                } else if(opcodes[j*k] == 0x8008 | opcodes[j*k] == 0x9009 | opcodes[j*k] == 0x900A | opcodes[j*k] == 0x8000 | opcodes[j*k] == 0x9001 | opcodes[j*k] == 0x9002) {
                    //LDD1,LDD2,LDD3,LDD4,LDD5,LDD6,LDD7,LDD8
                    fill(90,150,200);
                } else if(opcodes[j*k] == 224 | opcodes[j*k] == 160 | opcodes[j*k] == 36864) {
                    //LDI,LDS,LDS16
                    fill(90,150,120);
                } else if(opcodes[j*k] == )
                rect(k*20, j*20, 20, 20);
            }
        }
}

void draw() {

}