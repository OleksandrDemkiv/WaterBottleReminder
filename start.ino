// sets up all pins
void pining() {
  Serial.begin(57600); // serial
  lcd.begin(16, 2); // LCD

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); // load cell

  pinMode(RED_BTN, INPUT_PULLUP); // red button
  pinMode(BLUE_BTN, INPUT_PULLUP); // blue button

  pinMode(BUZZER_PIN, OUTPUT); // speaker
}

// printing messages
void printSetUpMessage(String name) {
  if (name == "startUpTare") {
    // print "Please clear the platfotm!"
    clearScreen();
    lcd.print("Please clear");
    lcd.setCursor(0, 1);
    lcd.print("the platform!");
    delay(2000);
    
    // print "Red - Done \n Blue- Repeat msg"
    clearScreen();
    lcd.print("Red - Done");
    lcd.setCursor(0, 1);
    lcd.print("Blue- Repeat msg");
  }
  else if (name == "startUpDone") {
    // print "Startup finised!!!"
    clearScreen();
    lcd.print("Startup");
    lcd.setCursor(0, 1);
    lcd.print("finished!!!");
    delay(2000);

    // print "Place the bottle to start"
    clearScreen();
    lcd.print("Place the bottle");
    lcd.setCursor(0, 1);
    lcd.print("to start!");
    delay(2000);
    
    // print "Red - Start \n Blue- Repeat msg"
    clearScreen();
    lcd.print("Red - Start");
    lcd.setCursor(0, 1);
    lcd.print("Blue- Repeat msg");
  }
}

// startup messages and taring
void startUp() {
  printSetUpMessage("startUpTare"); // print msg to clear the platform

  bool isBtnPressed = false;

  // loop to wait for button press
  while (!isBtnPressed) {
    if (digitalRead(RED_BTN) == LOW) {
      isBtnPressed = true;
    }
    if (digitalRead(BLUE_BTN) == LOW) {
      printSetUpMessage("startUpTare"); // same msg
    }
  }

  // tare the scale after the btn pressed
  scale.set_scale(CALIBRATION_FACTOR);
  scale.tare();

  isBtnPressed = false;

  // say to put the bottle to start 
  printSetUpMessage("startUpDone");

  // wait for button press
  while (!isBtnPressed) {
    if (digitalRead(RED_BTN) == LOW) {
      isBtnPressed = true;
    }
    if (digitalRead(BLUE_BTN) == LOW) {
      printSetUpMessage("startUpTare"); // same msg
    }
  }

  // get weight of the bottle
  lastMeasure = scale.get_units();
}