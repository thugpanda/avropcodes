#include <avr/pgmspace.h>
#include <Arduino.h>
#include <avr/io.h>
#include <AccelStepper.h>

#define pgm_read_word_near(address_short) __LPM_word((uint16_t)(address_short))
#define pgm_read_byte_near(address_short) __LPM((uint16_t)(address_short))
#define GREEN 11
#define RED 6
#define BLUE 9
#define YELLOW 10

word    pFlash;
word    pgm_word    =   0;

int     movCount    =   0;
int     addCount    =   0;
int     subCount    =   0;
int     eorCount    =   0;
int     andCount    =   0;
int     adcCount    =   0;

long    millisStart =   0;
long    millisEnd   =   0;

AccelStepper    stepper;
AccelStepper    stepper2(4,7,8,12,13);

void setup () {
    Serial.begin(115200);
    while(!Serial);
    Serial.println("Hi, I am here and ready to communicate.");
    pinMode(GREEN,OUTPUT);
    pinMode(RED,OUTPUT);
    pinMode(BLUE,OUTPUT);
    pinMode(YELLOW,OUTPUT);
    pinMode(LED_BUILTIN,OUTPUT);

    stepper.setMaxSpeed(500);
    stepper.setAcceleration(250);
    stepper2.setMaxSpeed(500);
    stepper2.setAcceleration(250);

    millisStart =   millis();
    for(pFlash=0x0; pFlash<=0x224C; pFlash++) {
        digitalWrite(GREEN,LOW);
        digitalWrite(RED,LOW);
        digitalWrite(BLUE,LOW);
        digitalWrite(YELLOW,LOW);
        digitalWrite(LED_BUILTIN,LOW);
        switch(loadNextWord(pFlash)) {
            case(0):
                pgm_word    =   pgm_read_word_near(pFlash);
                Serial.print("\nWord at 0x");
                Serial.print(pFlash,HEX);
                Serial.print(" is a MOV Instruction: 0x");
                Serial.print(pgm_word>>10,HEX);
                Serial.print(" with payload 0x");
                Serial.print((pgm_word&(~64512)),HEX);
                // moveStepper();
                movCount++;
                // digitalWrite(GREEN,HIGH);
                break;
            case(1):
                pgm_word    =   pgm_read_word_near(pFlash);
                Serial.print("\nWord at 0x");
                Serial.print(pFlash,HEX);
                Serial.print(" is an ADD Instruction: 0x");
                Serial.print(pgm_word>>10,HEX);
                Serial.print(" with payload 0x");
                Serial.print((pgm_word&(~64512)),HEX);
                addCount++;
                // digitalWrite(RED,HIGH);
                break;
            case(2):
                pgm_word    =   pgm_read_word_near(pFlash);
                Serial.print("\nWord at 0x");
                Serial.print(pFlash,HEX);
                Serial.print(" is a SUB Instruction: 0x");
                Serial.print(pgm_word>>10,HEX);
                Serial.print(" with payload 0x");
                Serial.print((pgm_word&(~64512)),HEX);
                subCount++;
                // digitalWrite(BLUE,HIGH);
                break;
            case(3):
                pgm_word    =   pgm_read_word_near(pFlash);
                Serial.print("\nWord at 0x");
                Serial.print(pFlash,HEX);
                Serial.print(" is an EOR Instruction: 0x");
                Serial.print(pgm_word>>10,HEX);
                Serial.print(" with payload 0x");
                Serial.print((pgm_word&(~64512)),HEX);
                eorCount++;
                // digitalWrite(YELLOW,HIGH);
                break;
            case(4):
                pgm_word    =   pgm_read_word_near(pFlash);
                Serial.print("\nWord at 0x");
                Serial.print(pFlash,HEX);
                Serial.print(" is an AND Instruction: 0x");
                Serial.print(pgm_word>>10,HEX);
                Serial.print(" with payload 0x");
                Serial.print((pgm_word&(~64512)),HEX);
                andCount++;
                break;
            case(5):
                pgm_word    =   pgm_read_word_near(pFlash);
                Serial.print("\nWord at 0x");
                Serial.print(pFlash,HEX);
                Serial.print(" is an ADC Instruction: 0x");
                Serial.print(pgm_word>>10,HEX);
                Serial.print(" with payload 0x");
                Serial.print((pgm_word&(~64512)),HEX);

                Serial.print("\nMoving Stepper ADC from 0x");
                Serial.print(stepper2.currentPosition(),HEX);
                Serial.print(" to 0x");
                Serial.print((pgm_word&(~64512)),HEX);
                // stepper2.runToNewPosition((pgm_word&(~64512)));
                delay(100);

                adcCount++;
                break;
            default:
                digitalWrite(LED_BUILTIN,HIGH);
                break;
        }
        delay(2);
    }
    millisEnd   =   millis();
    Serial.println("\nFinished Crawling");
    Serial.print("Finished with ");
    Serial.print(movCount);
    Serial.print(" mov, ");
    Serial.print(addCount);
    Serial.print(" add, ");
    Serial.print(subCount);
    Serial.print(" sub, ");
    Serial.print(eorCount);
    Serial.print(" eor ");
    Serial.print(andCount);
    Serial.print(" and, and ");
    Serial.print(adcCount);
    Serial.print(" adc instructions\n");
    convertMillis((millisEnd-millisStart));
}

void loop() {
}

void moveStepper() {
    Serial.print("\nMoving Stepper MOV from 0x");
    Serial.print(stepper.currentPosition(),HEX);
    Serial.print(" to 0x");
    Serial.print((pgm_word&(~64512)),HEX);
    stepper.runToNewPosition((pgm_word&(~64512)));
    delay(100);
}

void convertMillis(long __millis) {
    long    __secs  =   __millis/1000;
    int     __min   =   __secs/60;
    __secs          %=  60;

    Serial.print("It took me ");
    Serial.print(__min);
    Serial.print(" minutes and ");
    Serial.print(__secs);
    Serial.print(" seconds to complete\n");
}