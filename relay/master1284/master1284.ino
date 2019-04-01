#include <InstructionSniffer.h>
#include <Wire.h>

#define MASTERSPI 32
// #define SLAVESPI 9
#define NO_OF_SLAVES 16
#define SPI true

InstructionSniffer sniffer(SPI);

byte    currentSlave    =   0;
byte    lastSlave       =   0;
word    pFlash          =   0;
word    slavePGM        =   0x0;
word    instruction     =   0x0;

long    tStart          =   0;
long    tStartSound     =   0;
long    tNow            =   0;
boolean flash           =   false;

byte    tick            =   0;

#define tFlash 7
#define tWait 76
#define tSound 41

#define AUDIO_OUT 13    //PD5/19 as PWM out for sound
#define OUTPUT_REG OCR1A

uint8_t audioBuffer[24];
uint8_t write           =   0;

/* AUDIO OUTPUT
 * TIMER1 - SAMPLERATE
 *      CTC, OCR = 13019, 64 Prescaler
 * TIMER2 - PWM
 *      ASK FELIX
 */


void setup() {
    randomSeed(A0);
    Wire.begin();
    // while(!Wire);
    Serial.begin(115200);
    while(!Serial);
    Serial.print(millis());
    Serial.println(": Resetting Bus...");
    for(byte i=0; i<NO_OF_SLAVES; i++) {
        resetBus(i);
    }
    Serial.print(millis());
    Serial.println(": Bus reset");
    DDRA    =   0xFF;
    DDRD    =   0xFC;
    // PORTD   =   0x20;
    DDRB    =   0xFF;
    DDRC    =   0xF;

    setupTimerSampling();
    setupTimerPWM();

    tStart      =   millis();
    tStartSound =   millis();
    sei();
}

void loop() {
    // if((millis()-tStartSound) >= tSound) {
    //     Serial.print(millis());
    //     Serial.print(": Writing OCR1A to audioBuffer[");
    //     Serial.print(write%2);
    //     Serial.print("]::");
    //     Serial.println(audioBuffer[write%2]);
    //     OCR1A       =   audioBuffer[write%2];
    //     write++;
    //     tStartSound =   millis();
    // }
    if((millis()-tStart) >= tWait && !flash) {
        // Serial.print(millis());
        // Serial.println(": Request routine triggered");
        // cli();
        // Serial.print(millis());
        // Serial.println(": cli");
        slavePGM    =   0;
        // Serial.print(millis());
        // Serial.print(": SlavePGM = ");
        // Serial.println(slavePGM);
        // Serial.print(millis());
        // Serial.print(": Requesting from ");
        // Serial.println(currentSlave);
        Wire.requestFrom(currentSlave, 2);
        while(Wire.available() == 2) {
            slavePGM    =   (Wire.read())<<0x8;
        }
        while(Wire.available() == 1) {
            slavePGM    |=  Wire.read();
        }

        // sei();

        instruction     =   sniffer.OTFfindInstruction(slavePGM);
        // audioBuffer[0]  =   instruction;
        // audioBuffer[1]  =   (instruction>>8);
        shiftBuffer(byte(instruction), byte(instruction>>8));

        // Serial.print(millis());
        // Serial.print(": Received from ");
        // Serial.print(currentSlave);
        // Serial.print(":: ");
        // Serial.print(byte(instruction));
        // Serial.print(" and ");
        // Serial.println(byte(instruction>>8));

        // Immediate output without compare and serial
        PORTA   =   instruction;        //MSB
        PORTB   =   (instruction>>8);   //LSB
        
        // Serial.print("0x");
        // Serial.print(pFlash,HEX);
        // Serial.print("::");
        /* DEBUG OUTPUT VIA SERIAL*/
        // for(int i=0; i<8; i++) {
        //     if(instruction & (1<<i)) {
        //         PORTA   |=  (1<<i);
        //         Serial.print(1);
        //     } else {
        //         Serial.print(0);
        //     }
        //     if(((instruction>>8) & (1<<i))) {
        //         PORTB   |=  (1<<i);
        //         Serial.print(1);
        //     } else {
        //         Serial.print(0);
        //     }
        // }
        // Serial.print(" -- ");
        // Serial.print(byte(instruction));
        // Serial.print("::");
        // Serial.print(byte(instruction>>8));
        // Serial.print("\n");

        // Serial.print("Buffer::[\t");
        Serial.print("[");
        for(int i=0; i<24; i++) {
            Serial.print(audioBuffer[i]);
            Serial.print("\t");
        }
        Serial.println("]");

        pFlash++;
        flash   =   true;
        tStart  =   millis();
    }
    if(pFlash > 0x400) {
        pFlash  =   0;
        // currentSlave++;
        // currentSlave    %=  NO_OF_SLAVES;
        currentSlave        =   random(17);
        while(currentSlave  ==  lastSlave) {
            currentSlave    =   random(17);
        }
        lastSlave           =   currentSlave;
        // cli();
        resetBus(NO_OF_SLAVES);
        // sei();
    }
    if(millis()-tStart >= tFlash && flash) {
        PORTA   =   0;
        PORTB   =   0;
        flash   =   false;
        tStart  =   millis();
    }
}

void setupTimerSampling() {
    cli();

    TCCR3A  =   0;
    TCCR3B  =   0;
    TCNT3   =   0;

    OCR3A   =   41665;

    TCCR3B  |=  (1 << WGM12);
    TCCR3B  |=  (0 << CS12) | (1 << CS11) | (0 << CS10);
    TIMSK3  |=  (1 << OCIE3A);
    

    Serial.print(millis());
    Serial.println(": Set Timer3 as 24Hz Sampling");
    sei();
}

void setupTimerPWM() {
    cli();

    TCCR1A  =   0;
    TCCR1B  =   0;
    TCCR1C  =   0;

    TCCR1A  |=  (1 << COM1A1);
    TCCR1A  |=  (1 << WGM10) | (1 << WGM11);
    TCCR1B  |=  (1 << WGM12) | (0 << CS12) | (1 << CS11) | (1 << CS10);

    Serial.print(millis());
    Serial.println(": Set Timer1 as Fast PWM, output to OCR1A (PD4)");

    sei();
}

ISR(TIMER3_COMPA_vect) {
    // cli();
    // Serial.print(millis());
    // Serial.println(": Interrupt ");
    //Interrupt for sampling
    OUTPUT_REG  =   audioBuffer[write%24] | (tick>>4);
    // OUTPUT_REG  %=  128;
    // OUTPUT_REG  +=  128;
    // Serial.println(OUTPUT_REG);
    write++;
    tick++;
    // sei();
}

void resetBus(byte _n) {
    for(int i=0; i<_n; i++) {
        Wire.beginTransmission(_n);
        Wire.write(0x0);
        Wire.endTransmission();
    }
}

void shiftBuffer(byte msb, byte lsb) {
    for(int i=0; i<22; i += 2) {
        audioBuffer[i]      =   audioBuffer[i+2];
        audioBuffer[i+1]    =   audioBuffer[i+3];
    }
    audioBuffer[22]         =   msb;
    audioBuffer[23]         =   lsb;
}