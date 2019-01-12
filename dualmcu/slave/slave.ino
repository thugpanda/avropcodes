#include <avr/pgmspace.h>
#include <avr/io.h>
#include <Arduino.h>
#include <Wire.h>

#define pgm_read_word_near(address_short) __LPM_word((uint16_t)(address_short))

word    pFlash          =   0x0;
word    pgmRead;
bool    flashFlag       =   false;
byte    flashCounter    =   0;
long    nonSense        =   12874;

void setup() {
    Wire.begin(9);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

void receiveEvent() {
    byte    msg     =   Wire.read();
}

void requestEvent() {
    pgmRead     =   pgm_read_word_near(pFlash);
    // Wire.write(pgmRead>>8);
    byte    pgmBytes[2];
    pgmBytes[0] =   (pgmRead>>8) & 0xFF;
    pgmBytes[1] =   (pgmRead) & 0xFF;
    Wire.write(pgmBytes,2);
    pFlash++;
}


void loop() {
    calculateStuff();
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
