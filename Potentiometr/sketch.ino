#include <Wire.h>

// lcd setup
#include "rgb_lcd.h"
rgb_lcd lcd;

#define POT A1 // potentiometr pin

// two buttons pins
#define RED_BTN   5
#define BLUE_BTN  6
#define HIGH 0x0
#define LOW  0x1

// speaker pin and variables
#include "pitches.h"
#define BUZZER_PIN 8
bool buzzerState = true;

// timer setup
#include "millisDelay.h"
millisDelay timer;

////// CONFIG //////

// variables for data of water consuconsumption
double measures[100];
int measureIndex = 0;
double lastMeasure, newMeasure, difference;

// timer vars
long timerTime = 60000;

// timer song
int songLenght = 25;

int melody[] = {
  NOTE_C4, NOTE_C4, 
  NOTE_D4, NOTE_C4, NOTE_F4,
  NOTE_E4, NOTE_C4, NOTE_C4, 
  NOTE_D4, NOTE_C4, NOTE_G4,
  NOTE_F4, NOTE_C4, NOTE_C4,
  
  NOTE_C5, NOTE_A4, NOTE_F4, 
  NOTE_E4, NOTE_D4, NOTE_AS4, NOTE_AS4,
  NOTE_A4, NOTE_F4, NOTE_G4,
  NOTE_F4
};

int durations[] = {
  4, 8, 
  4, 4, 4,
  2, 4, 8, 
  4, 4, 4,
  2, 4, 8,
  
  4, 4, 4, 
  4, 4, 4, 8,
  4, 4, 4,
  2
};


void setup() {
  pining(); // set up pining
  clearScreen();
  lcd.print("Starting up ...");
  delay(2000);
  startUp(); // starting up messages (tare & 1st measure)
  clearScreen();
  delay(1000);
  timer.start(timerTime);
}

void loop() {
    printInterface();

  // if timer is out
  if (timer.justFinished()) {
    timeToDrink();
  }

  // when red button is pressed
  if (digitalRead(RED_BTN) == LOW) {
    getNewMeasure();
  }

  // when blue ltn is pressed
  if (digitalRead(BLUE_BTN) == LOW) {
    sleepMode();
    delay(500);
  }

  // when two buttons are pressed
  if (digitalRead(RED_BTN) == LOW && digitalRead(BLUE_BTN) == LOW) {
    delay(100);
    menu();
  }
}
