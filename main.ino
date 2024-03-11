// clears the screen and sets cursor to 0,0
void clearScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
}

void printTimer() {
  long time = timer.remaining(); // time left in ms

  // if less then a minute
  if (time < 60000) {
    lcd.print(time / 1000);
    lcd.print(" s");
  }
  else if (time < 3600000) { // if less then a hour
    lcd.print(time / 60000);
    lcd.print(" m");
  }
  else {
    lcd.print(time / 3600000);
    lcd.print(" h");
  }
}

void printInterface() {
  // output msg "L: {last differance} \n T: {time left to timer or "off"} "
  clearScreen();
  lcd.print("L: ");
  lcd.print(difference);
  lcd.print(" ml");
  lcd.setCursor(0, 1);
  lcd.print("T: ");
  if (timer.isRunning()) {
    printTimer();
  } else {
    lcd.print("off");
  }
  delay(40);
}

void timeToDrink() {
  // output msg "Time to drink water!"
  clearScreen();
  lcd.print("Time to drink");
  lcd.setCursor(0, 1);
  lcd.print("water!");

  if (buzzerState) {  // play song if on until bottle is lifted
      //playSong();
  }      
  else {  // wait until bottle is lifted with no song
    while (scale.get_units() >= lastMeasure) { 
    }
  }

  measureAfter(); // ask for red btn to record measure

  timer.start(timerTime); // start timer again
}

void getNewMeasure() {
  newMeasure = scale.get_units(); // get new value
    if (newMeasure < lastMeasure) {
      difference = lastMeasure - newMeasure; // get difference
      lastMeasure = newMeasure; // set new value as last for futher usage

      measures[++measureIndex] = difference; // add how much was drunk into history

      // output msg "You have drunk {differance} ml"
      clearScreen();
      lcd.print("You have drunk:");
      lcd.setCursor(0, 1);
      lcd.print(difference);
      lcd.print(" ml");

      delay(2000);
    }
    else if (newMeasure > lastMeasure) {
      lastMeasure = newMeasure; // only set new measure

      // output message "Volume updated successfully"
      clearScreen();
      lcd.print("Volume updated");
      lcd.setCursor(0, 1);
      lcd.print("successfully!!!");
      delay(2000);
    }
}

void sleepMode() {
  delay(100);
  clearScreen();
  while (digitalRead(RED_BTN) == HIGH && 
        digitalRead(BLUE_BTN) == HIGH && 
        scale.get_units() == lastMeasure) {}
  
  if (scale.get_units() != lastMeasure) measureAfter(); // ask for red btn to record measure if woke on lift
}

void measureAfter() {
  // output msg "Press red btn when done"
  clearScreen();
  lcd.print("Press red btn");
  lcd.setCursor(0, 1);
  lcd.print("when done!");

  while (digitalRead(RED_BTN) == HIGH) {} // dont do anyanything until red btn pressed

  getNewMeasure(); // record new measure
}