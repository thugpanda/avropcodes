#include <avr/pgmspace.h>
#include <Arduino.h>

word    const   *   p;
word                i;
long    nonSense        =   12874;

void setup() {
    Serial.begin(115200);
    while(!Serial);
    Serial.println("Dumping SRAM");
}

void loop() {
    calculateStuff();
    Serial.print("Calculated ");
    Serial.println(nonSense);
    delay(500);
    dumpSRAM();
    delay(2500);
}

void dumpSRAM() {
    i   =   0;
    p   =   0;
    do {
        Serial.print("0x");
        Serial.println(*p,HEX);
        i++;
        p++;
    } while (i<=0x800);
}

void calculateStuff() {
    byte    rnd     =   random(0,10);
    if(rnd == 0) {
        nonSense    /=  2;
    } else if(rnd == 1) {
        nonSense++;
    } else if(rnd == 2) {
        nonSense    *=  2;
    } else if(rnd == 3) {
        nonSense    += 135;
    } else if(rnd == 4) {
        nonSense    -=  294;
    } else if(rnd == 5) {
        int wtf     =   nonSense>>8;
    } else if(rnd == 6) {
        nonSense>>1;
    } else if(rnd == 7) {
        nonSense<<1;
    } else if(rnd == 8) {
        nonSense    += 2994;
    } else if(rnd == 8) {
        nonSense    += (nonSense>>4);
    } else if(rnd == 9) {
        nonSense    /=  (nonSense>>16);
    }
}