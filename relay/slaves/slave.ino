#include <avr/pgmspace.h>
#include <Wire.h>

#define MASTERSPI 32
#define SLAVESPI 9

int     ledPin  =   9;
word    pFlash  =   0x0;

void setup() {
    Serial.begin(115200);
    while(!Serial);
    Wire.begin(SLAVESPI);
    Wire.onRequest(requestHandler);
    Wire.onReceive(receiveHandler);
}

void loop() {
    for(int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {
        analogWrite(ledPin,fadeValue);
    }

    for(int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {
        analogWrite(ledPin, fadeValue);
    }
}

void requestHandler() {
    word    pgmRead =   pgm_read_word_near(pFlash);
    Wire.write(pgmRead);
    pFlash++;
}

void receiveHandler() {
    while(Wire.available() > 0) {
        byte dump   =   Wire.read();
    }
    pFlash  =   0x0;
}