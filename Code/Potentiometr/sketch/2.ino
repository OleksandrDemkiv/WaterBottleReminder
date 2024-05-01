void getNewMeasure() {
  newMeasure = analogRead(POT); // get new value

  if (newMeasure < lastMeasure) {
    difference = lastMeasure - newMeasure; // get difference
    lastMeasure = newMeasure; // set new value as last for futher usage

    sendData(difference); // add how much was drunk into history

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

void measureAfter() {
  // output msg "Press red btn when done"
  clearScreen();
  lcd.print("Press red btn");
  lcd.setCursor(0, 1);
  lcd.print("when done!");

  delay(500);
  while (digitalRead(RED_BTN) == HIGH); // dont do anything until red btn pressed

  getNewMeasure(); // record new measure
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
  // output msg "L: {last differance} \n T: {time left to timer or "off"}  S: {sound state}"
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

  lcd.setCursor(11, 1);
  lcd.print("S:");
  if (buzzerState) {
    lcd.print("on"); 
  }
  else {
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

  if (buzzerState == true) {  // play song once if on
    playSong();
  }      
  
  // wait until bottle is lifted
  while (analogRead(POT) >= lastMeasure);

  measureAfter(); // ask for red btn to record measure

  timer.start(timerTime); // start timer again
}

void sleepMode() {
  delay(500);
  clearScreen();
  while (digitalRead(RED_BTN) == HIGH && digitalRead(BLUE_BTN) == HIGH && !timer.justFinished());

  if (analogRead(POT) != lastMeasure) measureAfter(); // ask for red btn to record measure if woke on lift
}

void playSong() {
  double measure = lastMeasure;

  for (int note = 0; note < songLenght; note++) {
    //if (analogRead(POT) < measure) break;
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    
    //stop the tone playing:
    noTone(BUZZER_PIN);
  }
}

void sendData(int litres) {
  String host = "http://192.168.77.174:80";
  client.get(host + "/add_data?litres=" + litres);
}
