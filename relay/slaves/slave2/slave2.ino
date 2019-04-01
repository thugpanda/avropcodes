#include <avr/pgmspace.h>
#include <Wire.h>

#define MASTERSPI 32
#define SLAVESPI 2
#define STATUSLED 2
#define LEDONTIME 20

int     ledPin  =   9;
word    pFlash  =   0x0;

long    tStart  =   0;
boolean ledOn   =   false;

void setup() {
//    Serial.begin(115200);
//    while(!Serial);
    Wire.begin(SLAVESPI);
    Wire.onRequest(requestHandler);
    Wire.onReceive(receiveHandler);
    pinMode(STATUSLED, OUTPUT);
    digitalWrite(STATUSLED, LOW);
}

void loop() {
    for(int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {
        analogWrite(ledPin,fadeValue);
    }

    for(int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {
        analogWrite(ledPin, fadeValue);
    }
    if(ledOn && millis() - tStart >= LEDONTIME) {
        digitalWrite(STATUSLED, LOW);
        ledOn   =   false;
    }
}

void requestHandler() {
    word    pgmRead =   pgm_read_word_near(pFlash);
    Wire.write(pgmRead);
    pFlash++;
    digitalWrite(STATUSLED, HIGH);
    tStart  =   millis();
    ledOn   =   true;
}

void receiveHandler() {
    while(Wire.available() > 0) {
        byte dump   =   Wire.read();
    }
    pFlash  =   0x0;
    digitalWrite(STATUSLED, HIGH);
    tStart  =   millis();
    ledOn   =   true;
}
