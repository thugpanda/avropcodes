#include <avr/pgmspace.h>
#include <avr/io.h>
#include <Arduino.h>
#include <Wire.h>

#define pgm_read_word_near(address_short) __LPM_word((uint16_t)(address_short))

word        pFlash;
word        pgmRead;
word        pgmAddress  =   0;

void setup() {
    Wire.begin();

    Serial.begin(115200);
    while(!Serial);
    Serial.println("Ready.");
}

void requestNextWord() {
    Wire.requestFrom(9,2);

    while(Wire.available()) {
        byte    a,b;
        a       =   Wire.read();
        pgmRead =   (a<<8) | Wire.read();
    }

    Serial.print("0x");
    Serial.print(pgmAddress,HEX);
    Serial.print("::0x");
    Serial.println(pgmRead,HEX);

    delay(20);
}

void loop() {
    while(pgmAddress <= 0x4000) {
        requestNextWord();
        pgmAddress++;
    }
}