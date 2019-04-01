void settings () {
    size(792, 792);
}

int[]   opcodes;

    int globalcount =   0;
void setup() {
    noStroke();
    rectMode(CENTER);
    fill(0);
    background(0);

    String[]    lines   =   loadStrings("instructions.txt");
    opcodes =   new int[lines.length];

    for(int i=0; i<lines.length; i++) {
        opcodes[i]  =   int(lines[i]);
    }
    // println(opcodes.length);
    
    // for(int i=0; i<39; i++) {
    //     for(int j=0; j<39; j++) {
    //         // background(0);
    //         // delay(100);
    //         int localcount  =   0;
    //         println(globalcount);
    //         println(hex(globalcount));
    //         for(int k=0; k<4; k++) {
    //             for(int l=0; l<4; l++) {
    //                 if((opcodes[globalcount] & (1<<(localcount))) > 0) {
    //                     fill(255);
    //                 } else {
    //                     // if(opcodes[globalcount] == 0x2C || opcodes[globalcount] == 0x1) {
    //                     //     fill(43, 155, 255);
    //                     // } else if(opcodes[globalcount] == 0x1C || opcodes[globalcount] == 0xC || opcodes[globalcount] == 0x96) {
    //                     //     fill(255, 38, 108);
    //                     // } else  if(opcodes[globalcount] == 32 || opcodes[globalcount] == 112 || opcodes[globalcount] == 40 || opcodes[globalcount] == 96 || opcodes[globalcount] == 36) {
    //                     //     fill(55, 255, 160);
    //                     // } else if(opcodes[globalcount] == 36876 || opcodes[globalcount] == 36877 || opcodes[globalcount] == 36878 || opcodes[globalcount] == 0x8008 || opcodes[globalcount] == 0x9009 || opcodes[globalcount] == 0x900A || opcodes[globalcount] == 0x8000 || opcodes[globalcount] == 0x9001 || opcodes[globalcount] == 0x9002 || opcodes[globalcount] == 224 || opcodes[globalcount] == 160 || opcodes[globalcount] == 36863) {
    //                     //     fill(255, 239, 0);
    //                     // } else {
    //                         fill(0);
    //                     // }
    //                 }
    //                 rect(k*4+2+(j*18), l*4+2+(i*18), 2, 2);
                    
    //                 localcount++;
    //             }
    //         }
    //         globalcount++;
    //     }
    // }
   
}

void draw() {
    int localcount  =   0;
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            if((opcodes[globalcount] & (1<<localcount)) > 0) {
                fill(255);
            } else {
                fill(0);
            }
            rect(i*200+96, j*200+96, 192, 192);

            localcount++;
        }
    }
    globalcount++;
    // println(globalcount);
    // saveFrame("punch-####.png");
    if(globalcount > opcodes.length) {
        exit();
    }
}