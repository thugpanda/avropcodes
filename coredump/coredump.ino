#include <avr/pgmspace.h>
#include <Arduino.h>
#include <avr/io.h>

#define pgm_read_word_near(address_short) __LPM_word((uint16_t)(address_short))
#define pgm_read_byte_near(address_short) __LPM((unt16_t)(address_short))
#define GREEN 5
#define RED 6
#define BLUE 9
#define YELLOW 10

word    pFlash;
word    pgm_word    =   0;


void setup () {
    Serial.begin(115200);
    while(!Serial);
    Serial.println("Hi, I am here and ready to communicate.");
    pinMode(GREEN,OUTPUT);
    pinMode(RED,OUTPUT);
    pinMode(BLUE,OUTPUT);
    pinMode(YELLOW,OUTPUT);
    pinMode(LED_BUILTIN,OUTPUT);

    for(pFlash=0x0; pFlash<=0x976; pFlash++) {
        digitalWrite(GREEN,LOW);
        digitalWrite(RED,LOW);
        digitalWrite(BLUE,LOW);
        digitalWrite(YELLOW,LOW);
        digitalWrite(LED_BUILTIN,LOW);
        switch(loadNextWord(pFlash)) {
            case(0):
                pgm_word    =   pgm_read_word_near(pFlash);
                Serial.print("\nWord at ");
                Serial.print(pFlash,HEX);
                Serial.print(" is a MOV Instruction: ");
                Serial.print(pgm_word>>10,BIN);
                Serial.print(" with payload ");
                Serial.print((pgm_word&(~64512)),BIN);
                digitalWrite(GREEN,HIGH);
                break;
            case(1):
                pgm_word    =   pgm_read_word_near(pFlash);
                Serial.print("\nWord at ");
                Serial.print(pFlash,HEX);
                Serial.print(" is an ADD Instruction: ");
                Serial.print(pgm_word>>10,BIN);
                Serial.print(" with payload ");
                Serial.print((pgm_word&(~64512)),BIN);
                digitalWrite(RED,HIGH);
                break;
            case(2):
                pgm_word    =   pgm_read_word_near(pFlash);
                Serial.print("\nWord at ");
                Serial.print(pFlash,HEX);
                Serial.print(" is a SUB Instruction: ");
                Serial.print(pgm_word>>10,BIN);
                Serial.print(" with payload ");
                Serial.print((pgm_word&(~64512)),BIN);
                digitalWrite(BLUE,HIGH);
                break;
            case(3):
                pgm_word    =   pgm_read_word_near(pFlash);
                Serial.print("\nWord at ");
                Serial.print(pFlash,HEX);
                Serial.print(" is a EOR Instruction: ");
                Serial.print(pgm_word>>10,BIN);
                Serial.print(" with payload ");
                Serial.print((pgm_word&(~64512)),BIN);
                digitalWrite(YELLOW,HIGH);
                break;
            default:
                digitalWrite(LED_BUILTIN,HIGH);
                break;
        }
        delay(20);
    }
    Serial.println("\nFinished Crawling");
}

void loop() {
}
