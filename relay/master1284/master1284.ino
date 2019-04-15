#include <InstructionSniffer.h>
#include <Wire.h>

#define MASTERSPI 32
#define NO_OF_SLAVES 16
#define SPI true
// #define DEBUG

#ifdef DEBUG
 #define DEBUG_BEGIN(x) Serial.begin(x)
 #define DEBUG_PRINT(x) Serial.print(x)
 #define DEBUG_PRINTLN(x)  Serial.println (x)
 #define DEBUG_PRINTHEX(x) Serial.print(x, HEX)
 #define DEBUG_FOR(x,y,z) for(int i=x; i<y; i+=z)
#else
 #define DEBUG_BEGIN(x)
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINTLN(x)
 #define DEBUG_PRINTHEX(x)
 #define DEBUG_FOR(x,y,z)
#endif

InstructionSniffer sniffer(SPI);

byte    currentSlave    =   0;
byte    lastSlave       =   0;
word    pFlash          =   0;
word    slavePGM        =   0x0;
word    instruction     =   0x0;

long    tStart          =   0;
long    tNow            =   0;
boolean flash           =   false;

byte    tick            =   0;

#define tFlash 7
#define tWait 76

#define AUDIO_OUT 13    //PD5/19 as PWM out for sound
#define OUTPUT_REG OCR1A

uint8_t audioBuffer[24];
uint8_t write           =   0;

void setup() {
    randomSeed(A0);
    Wire.begin();
    // while(!Wire);
    DEBUG_BEGIN(115200);
    // while(!Serial);
    DEBUG_PRINT(millis());
    DEBUG_PRINTLN(": Resetting Bus...");
    for(byte i=0; i<NO_OF_SLAVES; i++) {
        resetBus(i);
    }
    DEBUG_PRINT(millis());
    DEBUG_PRINTLN(": Bus reset");
    DDRA    =   0xFF;
    DDRD    =   0xFC;
    DDRB    =   0xFF;
    DDRC    =   0xF;

    setupTimerSampling();
    setupTimerPWM();

    tStart      =   millis();
    sei();
}

void loop() {
    if((millis()-tStart) >= tWait && !flash) {
        slavePGM    =   0;
        Wire.requestFrom(currentSlave, 2);
        while(Wire.available() == 2) {
            slavePGM    =   (Wire.read())<<0x8;
        }
        while(Wire.available() == 1) {
            slavePGM    |=  Wire.read();
        }

        instruction     =   sniffer.OTFfindInstruction(slavePGM);
        // audioBuffer[0]  =   instruction;
        // audioBuffer[1]  =   (instruction>>8);
        shiftBuffer(byte(instruction), byte(instruction>>8));

        DEBUG_PRINT(millis());
        DEBUG_PRINT(": Received from ");
        DEBUG_PRINT(currentSlave);
        DEBUG_PRINT(":: ");
        DEBUG_PRINT(byte(instruction));
        DEBUG_PRINT(" and ");
        DEBUG_PRINTLN(byte(instruction>>8));

        // Immediate output without compare and serial
        PORTA   =   instruction;        //MSB
        PORTB   =   (instruction>>8);   //LSB
        

        DEBUG_PRINT("Buffer::[\t");
        DEBUG_PRINT("[");
        DEBUG_FOR(0,24,1) {
            DEBUG_PRINT(audioBuffer[i]);
            DEBUG_PRINT("\t");
        }
        DEBUG_PRINT("]");

        pFlash++;
        flash   =   true;
        tStart  =   millis();
    }
    if(pFlash > 0x400) {
        pFlash  =   0;

        /*
        //Uncomment to use follow up querying
        currentSlave++;
        currentSlave    %=  NO_OF_SLAVES;
        */

        //Uncomment to use random access querying
        currentSlave        =   random(17);
        while(currentSlave  ==  lastSlave) {
            currentSlave    =   random(17);
        }
        lastSlave           =   currentSlave;
        resetBus(NO_OF_SLAVES);
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
    

    DEBUG_PRINT(millis());
    DEBUG_PRINTLN(": Set Timer3 as 24Hz Sampling");
    sei();
}

void setupTimerPWM() {
    cli();

    TCCR1A  =   0;
    TCCR1B  =   0;
    TCCR1C  =   0;

    TCCR1A  |=  (1 << COM1A1);
    TCCR1A  |=  (1 << WGM10) | (1 << WGM11);
    TCCR1B  |=  (1 << WGM12) | (0 << CS12) | (1 << CS11) | (1 << CS10); //TODO - find best settings for sound

    DEBUG_PRINT(millis());
    DEBUG_PRINTLN(": Set Timer1 as Fast PWM, output to OCR1A (PD4)");

    sei();
}

ISR(TIMER3_COMPA_vect) {
    //Interrupt for sampling
    OUTPUT_REG  =   audioBuffer[write%24] | (tick>>4);  //TODO - modify formular for cool sound
    write++;
    tick++;
}

void resetBus(byte _n) {
    //reset all slaves
    for(int i=0; i<_n; i++) {
        Wire.beginTransmission(_n);
        Wire.write(0x0);
        Wire.endTransmission();
    }
}

void shiftBuffer(byte msb, byte lsb) {
    //linear buffer shifter for audioBuffer
    for(int i=0; i<22; i += 2) {
        audioBuffer[i]      =   audioBuffer[i+2];
        audioBuffer[i+1]    =   audioBuffer[i+3];
    }
    audioBuffer[22]         =   msb;
    audioBuffer[23]         =   lsb;
}