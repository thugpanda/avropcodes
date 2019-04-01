#define AUDIO_OUT 13
#define OUTPUT_REG OCR1A

uint8_t audioBuffer[2];
uint8_t write       =   0;

void setup() {
    Serial.begin(115200);
    while(!Serial);

    DDRD    =   0x20;
    // PORTD   =   0x20;

    cli();
    TCCR1A  =   0;
    TCCR1B  =   0;
    TCCR1C  =   0;

    TCCR1A  |=  (1<<COM1A1);
    TCCR1A  |=  (1<<WGM10) | (1<<WGM11);
    // TCCR1A  |=  (1<<WGM10);
    TCCR1B  |=  (1<<WGM12) | (1<<CS10);

    sei();
}

void loop() {
    if((millis() % 200) <= 1) {
        Serial.print(millis());
        Serial.print(": writing audioBuffer[");
        Serial.print(write%2);
        Serial.print("] :: ");
        Serial.println(audioBuffer[write%2]);
        // Serial.println(OCR1A);
        OCR1A   =   audioBuffer[write%2];
        // OCR1A   =   3+write;
        write++;
    }
    if((millis() % 500) <= 1) {
        audioBuffer[0]  =   random(2,255);
        Serial.print(millis());
        Serial.print(": Setting audioBuffer[0] and [1] to: ");
        Serial.print(audioBuffer[0]);
        Serial.print(" -- ");
        audioBuffer[1]  =   random(2,255);
        Serial.println(audioBuffer[1]);
    }
}