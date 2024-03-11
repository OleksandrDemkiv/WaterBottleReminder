#include <Wire.h>

// lcd setup
#include "rgb_lcd.h"
rgb_lcd lcd;

// HX711 circuit wiring
#include "HX711.h"
#define LOADCELL_DOUT_PIN   5
#define LOADCELL_SCK_PIN    6
#define CALIBRATION_FACTOR  0.42
HX711 scale;

// two buttons pins
#define RED_BTN   2
#define BLUE_BTN  3

// speaker pin and variables
#include "pitches.h"
#define BUZZER_PIN 9
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
int songIndexes[2];

void setup() {
  clearScreen();
  pining(); // set up pining
  lcd.print("Starting up ...");
  delay(2000);
  startUp(); // starting up messages (tare & 1st measure)
  clearScreen();
  delay(1000);
  songIndexes[0] = 0;
  songIndexes[1] = 0;
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
  }

  // when two buttons are pressed
  if (digitalRead(RED_BTN) == LOW && digitalRead(BLUE_BTN) == LOW) {
    delay(100);
    menu();
  }
}
