#include "pitches.h"

#define speakerPin 4

// family mart jingle
int melody[] = {
  NOTE_E4, NOTE_C4, NOTE_G3, NOTE_C4, NOTE_D4, NOTE_G4,   
  NOTE_D3, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G3, NOTE_C4
};

// 8 = eighth note
// 4 = quarter note
int noteDurations[] = {
  8, 8, 8, 8, 8, 4,   
  8, 8, 8, 8, 8, 4
};

void setup() {
  for (int i = 0; i < sizeof(melody); i++) {
    int duration = 1000 / noteDurations[i];
    tone(speakerPin, melody[i], duration, 0);

    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    noTone(speakerPin, 0);
  }
}

void loop() {
}

// below are for ESP32
void tone(uint8_t pin, unsigned int frequency, unsigned long duration, uint8_t channel)
{
    if (ledcRead(channel)) {
        log_e("Tone channel %d is already in use", ledcRead(channel));
        return;
    }
    ledcAttachPin(pin, channel);
    ledcWriteTone(channel, frequency);
    if (duration) {
        delay(duration);
        noTone(pin, channel);
    }    
}

void noTone(uint8_t pin, uint8_t channel)
{
    ledcDetachPin(pin);
    ledcWrite(channel, 0);
}
