// Initialize the LCD
const int rs = 0, en = 1, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Initializes the LCD
void initializeLCD() {
  lcd.createChar(0, goalLeft);
  lcd.createChar(1, goalRight);
  lcd.begin(16,2); 
}

// Displays a calibration screen for the LCD (code stolen from Lab 5)
void calibrate() {
  int i = 0;
  bool left = true;
  lcd.setCursor(0,0);
  lcd.print("CALIBRATING...");
  int scrollLen = ((String)"CALIBRATING...").length();
  delay(400);
  while(true) {
    if (i == scrollLen) {
      i = 0;
      lcd.clear();
      if (left) {
        lcd.setCursor(16-scrollLen, 1);
        lcd.print("CALIBRATING...");
      } else {
        lcd.setCursor(0, 0);
        lcd.print("CALIBRATING...");
      }
      left = !left;
    } else {
      if (left) {
        lcd.scrollDisplayLeft();
      } else {
        lcd.scrollDisplayRight();
      }
    }
    i += 1;
    delay(300);
  }
}

// The display function for the Metronome tool. Call it once per frame.
// Call it whenever the screen updates 
// (DO NOT call it every frame - the screen will flicker.)
// playing: whether the metronome is playing or not.
// bpm: the current BPM of the metronome
void displayMetronome(bool playing, int bpm) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("METRONOME");

  if (bpm < 100) {
    lcd.setCursor(14,0);
    lcd.print(bpm);
  } else {
    lcd.setCursor(13,0);
    lcd.print(bpm);
  }

  lcd.setCursor(6,1);
  if (playing) {
    lcd.print("ON");
  } else {
    lcd.print("OFF");
  }
}

// The display function for the Note Player tool. 
// Call it whenever the screen updates 
// (DO NOT call it every frame - the screen will flicker.)
// playing: whether the metronome is playing or not.
// note: the note that the player is set to (as a 2 or 3-char string)
void displayNotePlayer(bool playing, char* note) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("NOTE PLAYER");

  size_t noteLength = strlen(note);
  int notePos = 16 - noteLength;
  lcd.setCursor(notePos,0);
  lcd.print(note);

  lcd.setCursor(6,1);
  if (playing) {
    lcd.print("ON");
  } else {
    lcd.print("OFF");
  }
}

// The display function for the Tuner tool. 
// Call it whenever the screen updates 
// (DO NOT call it every frame - the screen will flicker.)
// note: the note that the tuner is set to (as a two-char string)
// accuracy: a number between 0 and 15 determining how accurate the 
//       heard note is, where 7 and 8 is most accurate
void displayTuner(bool displayAccuracy, int accuracy, char* note) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TUNER");

  lcd.setCursor(14,0);
  lcd.print(note);

  lcd.setCursor(7,1);
  lcd.write(byte(0)); // write the custom "goal" characters
  lcd.write(byte(1)); 

  if (displayAccuracy) {
    lcd.setCursor(accuracy, 1);
    lcd.write(byte(255));
  }
}

// When you change the instrument, you want to display what instrument
// is currently being rendered
// 
// instrument: string of the current instrument
// notesList: array of strings that the current instrument tunes for (can render up to )
void displayTunerInstrument(char* instrument, char* notesList[]) {
  int totalNotesLen = 0;
  int potentialNotesLen = 0;
  int numNotesDisplayed = 0; 

  for (int i = 0; i < sizeof(notesList); i++) {
    potentialNotesLen += sizeof(notesList[i]);
    if ((potentialNotesLen + i) > 16) {
      break;
    } else {
      totalNotesLen = potentialNotesLen;
      numNotesDisplayed = i + 1;
    }
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SET TO: ");
  lcd.print(instrument); // instruments should be no longer than 8 chars

  // ok, note listing handling time
  int numCharsPrinted = totalNotesLen + (numNotesDisplayed - 1);

  int printStart = 8 - (numCharsPrinted / 2) - (num CharsPrinted % 2);
  // n.b. c int division truncates towards zero
  // so we have to nudge it a little further sometimes

  lcd.setCursor(printStart,1);
  
  for (int j = 0; j < numNotesDisplayed; j++) {
    lcd.print(notesList[j]);
    lcd.print(" ");
  }
}