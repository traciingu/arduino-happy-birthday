//www.elegoo.com
//2016.12.08

#include "pitches.h"

// ---- For RGB LED ----
#define RED 10
#define GREEN 9
#define BLUE 6

// ---- Music Output ----
// notes in the melody:
int melody[] = {
  NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_F5, NOTE_E5,
  NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_G5, NOTE_F5,
  NOTE_C5, NOTE_C5, NOTE_C6, NOTE_A5, NOTE_F5, NOTE_E5, NOTE_D5,
  NOTE_AS5, NOTE_AS5, NOTE_A5, NOTE_F5, NOTE_G5, NOTE_F5
};

int noteDurations[] = {
  3, 8, 3, 3, 3, 1,
  3, 8, 3, 3, 3, 1,
  3, 8, 3, 3, 3, 2, 1,
  3, 8, 3, 3, 3, 1
};

//int noteDurations[] = {
//  3, 16, 4, 4, 4, 1,
//  3, 16, 4, 4, 4, 1,
//  3, 16, 4, 4, 4, 3, 3,
//  3, 16, 4, 4, 4, 1
//};

unsigned long audioPrevious;
unsigned long audioBreakPrevious;
unsigned long ledPrevious;
unsigned long ledPeriod = 5;
unsigned long audioPeriod = 1000 / noteDurations[0];
unsigned long audioBreakPeriod = audioPeriod * 1.30;



void setup() {
  // LED settings
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  audioPrevious = millis();
  audioBreakPrevious = millis();
  ledPrevious = millis();
}


void loop() {
  unsigned long timeCurrent = millis();

  if (timeCurrent - audioPrevious >= audioPeriod) {
    happyBirthday();
    audioPrevious = timeCurrent;
  }

  
  if (timeCurrent - ledPrevious >= ledPeriod) {
    colourFade();
    ledPrevious = timeCurrent;
  }
}



int thisNote = 0;

void happyBirthday() {
  audioBreakPrevious = millis();


  int noteDuration = 1000 / noteDurations[thisNote];
  tone(8, melody[thisNote], noteDuration);

  audioBreakPeriod = noteDuration * 1.30;
  audioPeriod = noteDuration;


  while (millis() - audioBreakPrevious < audioBreakPeriod) {
    if (millis() - ledPrevious >= ledPeriod) {
      colourFade();
      ledPrevious = millis();
    }
  }

  noTone(8);

  thisNote++;

  if (thisNote == 25) {
    thisNote = 0;
  }
}


// Changing LED Colours ------
int LEDColour1 = 255;
int LEDColour2 = 0;
int colour = 0;
int LEDColours[] = {RED, GREEN, BLUE};

void colourFade() { // Delay for 5 ms

  LEDColour1--;
  LEDColour2++;

  if (LEDColour2 == 255) {
    LEDColour1 = 255;
    LEDColour2 = 0;
    colour++;

    if (colour == 3) {
      colour = 0;
    }
  }

  analogWrite(LEDColours[colour], LEDColour1);
  colour == 2 ? analogWrite(LEDColours[0], LEDColour2) : analogWrite(LEDColours[colour + 1], LEDColour2);

}
