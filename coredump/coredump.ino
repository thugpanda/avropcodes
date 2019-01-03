/*
*   trying to dump the flash core of the atmega328p via serial, byte by byte. If this works I should be able to
*   read the flash in runtime. Might offer some possibilites.
*/

#include <avr/pgmspace.h>
#include <Arduino.h>
#include <avr/io.h>

#define pgm_read_word_near(address_short) __LPM((uint16_t)(address_short))
#define LED 5
#define BUZZER 6

word    pFlash;
byte    pgm_word    =   0;

void setup () {
    Serial.begin(9600);
    while(!Serial);
    Serial.println("Hi, I am here and ready to communicate.");
    pinMode(LED,OUTPUT);
    pinMode(BUZZER,OUTPUT);

    Serial.print("Address\tValue\n");
    for(pFlash=0x0; pFlash<=0x9E8; pFlash++) {
        Serial.print(pFlash,HEX);
        Serial.print("\t");
        pgm_word    =   pgm_read_word_near(pFlash);
        Serial.print(pgm_word,HEX);
        analogWrite(LED,pgm_word);
        analogWrite(BUZZER, pgm_word);
        Serial.print("\n");
        delay(250);
    }
    Serial.print("\n----------\n\n");
}

void loop() {
}
