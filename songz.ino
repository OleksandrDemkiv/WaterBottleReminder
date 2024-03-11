void playSong() {
  switch (songIndexes[0]) {

    // Games
    case 0:

      switch (songIndexes[1]) {

        // Doom
        case 0:
          play(doom_melody, doom_durations);
          break;

        // Mario bros
        case 1:
          play(mario_melody, mario_durations);
          break;

        // Pacman
        case 2:
          play(pacman_melody, pacman_durations);
          break;

        // Tetris
        case 3:
          play(tetris_melody, tetris_durations);
          break;
      }
    
      break;

    // Movies 1
    case 1:

      switch (songIndexes[1]) {

        // Game of Thrones
        case 0:
          play(thrones_melody, thrones_durations);
          break;
        
        // Harry Potter
        case 1:
          play(potter_melody, potter_durations);
          break;
        
        // Home Alone
        case 2:
          play(home_melody, home_durations);
          break;
        
        // Pink Panther
        case 3:
          play(panther_melody, panther_durations);
          break;
      }
      
      break;

    // Movies 2
    case 2:

      switch (songIndexes[1]) {

        // Pirates Caribbean
        case 0:
          play(pirates_melody, pirates_durations);
          break;

        // Star Wars
        case 1:
          play(star_wars_melody, star_wars_durations);
          break;

        // The Godfather
        case 2:
          play(godfather_melody, godfather_durations);
          break;
        
        // The Simpsons
        case 3:
          play(simpsons_melody, simpsons_durations);
          break;
      }
      
      break;

    // Songs
    case 3:

      switch (songIndexes[1]) {
        
        // Chevelle the Red
        case 0:
          play(chevelle_melody, chevelle_durations);
          break;
        
        // Shape of You
        case 1:
          play(shape_of_you_melody, shape_of_you_durations);
          break;
        
        // Maroon5 Memories
        case 2:
          play(memories_melody, memories_durations);
          break;
        
        // ID Enemy
        case 3:
          play(enemy_melody, enemy_durations);
          break;

      }
      
      break;

    // Other
    case 4:

      switch (songIndexes[1]) {

        // Happy Birthday
        case 0:
          play(hb_melody, hb_durations);
          break;

        // Nokia
        case 1:
          play(nokia_melody, nokia_durations);
          break;

        // Xmas
        case 2:
          play(xmas_melody, xmas_durations);
          break;
        
        // Its a Small World
        case 3:
          play(small_world_melody, small_world_durations);
          break;
      }
      
      break;
  }
}

void play(int melody[], int durations[])
{
  int size = sizeof(durations) / sizeof(int);
  double measure = lastMeasure;

  for (int note = 0; note < size; note++) {
    if (scale.get_units() < measure) break;
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