template< typename T, size_t N > size_t ArraySize (T (&) [N]){ return N; }

String songSections[] = {"Games", "Movies 1", "Movies 2", "Songs", "Other"};

String songsGamesNames[] = {"Doom", "Mario bros", "Pacman", "Tetris"};
String songsMovies1Names[] = {"Game of Thrones", "Harry Potter", "Home Alone", "Pink Panther"};
String songsMovies2Names[] = {"Pirates Caribbean", "Star Wars", "The Godfather", "The Simpsons"};
String songsSongsNames[] = {"Chevelle the Red", "Shape of You", "Maroon5 Memories", "ID Enemy"};
String songsOtherNames[] = {"Happy Birthday", "Nokia", "Xmas", "Itsa Small World"};


void menu() {
  String menuOptions[] = {"Timer setup", "Do not disturb", "Change song", "Change color"};

  int lenght = ArraySize(menuOptions);
  int pos = 0;
  int option = 0;

  while (digitalRead(RED_BTN) == HIGH || digitalRead(BLUE_BTN) == HIGH) {
    clearScreen();// clear screen
    
    // output "Menu" and all the main menu options
    lcd.print("Menu:");
    lcd.setCursor(0, 1);
    lcd.print(menuOptions[pos]);

    if (digitalRead(RED_BTN) == LOW) {
      delay(100); // avoid missclicking
      switch(pos) {
        case 0:
          timerSetup();
          break;
        case 1:
          doNotDisturb();
          break;
        case 2:
          changeSong();
          break;
        case 3:
          changeColor();
          break;
      }
    }

    if (digitalRead(BLUE_BTN) == LOW) {
      delay(100); // avoid missclicking
      if (pos < lenght-1){
        pos++;
      }
      else {
        pos = 0;
      }
    }

    delay(100); // smooth update
  }
}

void timerSetup() {
  timer.stop();
  long newTime = 0;
  
  while(digitalRead(RED_BTN) == HIGH || digitalRead(BLUE_BTN) == HIGH || newTime == 0) {
    clearScreen();

    // print current time and new
    lcd.print("Cur: ");
    lcd.print(timerTime / 60000);
    lcd.print(" m");
    lcd.setCursor(0, 1);
    lcd.print("New: ");
    lcd.print(newTime);
    lcd.print(" m");

    if (digitalRead(RED_BTN) == LOW) {
      delay(100); // avoid missclicking
      if (newTime > 0) {
        newTime -= 30;
      }
    }

    if (digitalRead(BLUE_BTN) == LOW) {
      delay(100); // avoid missclicking
      newTime += 30;
    }

    delay(100); // smooth update
  }

  timerTime = newTime * 60000; // new timer time is mins but in ms
  timer.start(timerTime); // start the timer on the time
}

void doNotDisturb() {
  int pos = 0; // to calculate if odd/even and choose is in/off
  
  while(digitalRead(RED_BTN) == HIGH) {
    clearScreen();

    // output message is mode on
    lcd.print("Do not disturb: ");
    lcd.setCursor(0, 1);
    lcd.print("       ");
    if (pos % 2 == 0) {
      lcd.print("off");
    }
    else {
      lcd.print("on");
    }

    // blue btn to change mode (cycle)
    if (digitalRead(BLUE_BTN) == LOW) {
      delay(100); // avoid missclicking
      pos++;
    }

    delay(100); // smooth update
  }

  if (pos % 2 == 0) {
    buzzerState = true; // turn on the speaker
  }
  else {
    buzzerState = false; // turn off the speaker
  }
}

void changeColor() {
  String colors[] = {"Red", "Green", "Blue"};
  int pos = 0;

  while(digitalRead(RED_BTN) == HIGH) {
    clearScreen();

    // output message is mode on
    lcd.print("Set color: ");
    lcd.setCursor(0, 1);
    lcd.print("      ");
    lcd.print(colors[pos]);
                    // switch (pos) {
                    //   case 0:
                    //     lcd.setRGB(255, 0, 0);
                    //     break;
                    //   case 1:
                    //     lcd.setRGB(0, 255, 0);
                    //     break;
                    //   case 2:
                    //     lcd.setRGB(0, 0, 255);
                    //     break;
                    // }

    // blue btn to change color (cycle)
    if (digitalRead(BLUE_BTN) == LOW) {
      delay(100); // avoid missclicking
      if (pos < 2){
        pos++;
      }
      else {
        pos = 0;
      }
    }

    delay(100); // smooth update
  }

}

void changeSong() {
  int secPos = 0; int inSecPos = 0;

  while(digitalRead(RED_BTN) == HIGH || digitalRead(BLUE_BTN) == HIGH) {
    delay(100);
    clearScreen();

    lcd.print("Song topic:");
    lcd.setCursor(0, 1);
    lcd.print(songSections[secPos]);
  
    // blue btn to change section
    if (digitalRead(BLUE_BTN) == LOW) {
      delay(100); // avoid missclicking
      if (secPos < 4){
        secPos++;
      }
      else {
        secPos = 0;
      }
    }

    // red btn to choose section
    if (digitalRead(RED_BTN) == LOW) {
      delay(100); // avoid missclicking
      String secSongs[4];
      switch (secPos) {
        case 0:
          memcpy(secSongs, songsGamesNames, sizeof(songsGamesNames[0])*4);
          break;
        case 1:
          memcpy(secSongs, songsMovies1Names, sizeof(songsMovies1Names[0])*4);
          break;
        case 2:
          memcpy(secSongs, songsMovies2Names, sizeof(songsMovies2Names[0])*4);
          break;
        case 3:
          memcpy(secSongs, songsSongsNames, sizeof(songsSongsNames[0])*4);
          break;
        case 4:
          memcpy(secSongs, songsOtherNames, sizeof(songsOtherNames[0])*4);
          break;
      }

      inSecPos = 0;
      
      while (digitalRead(RED_BTN) == HIGH) {
        delay(100);
        
        clearScreen();
        lcd.print(songSections[secPos]);
        lcd.print(":");
        lcd.setCursor(0, 1);
        lcd.print(secSongs[inSecPos]);

        if (digitalRead(BLUE_BTN) == LOW) {
          delay(100); // avoid missclicking
          if (inSecPos < 3){
            inSecPos++;
          }
          else {
            inSecPos = 0;
          }
        }

        delay(100); // smooth update
      }
    }
  
    songIndexes[0] = secPos;
    songIndexes[1] = inSecPos;

    delay(100); // smooth update
  }
}
