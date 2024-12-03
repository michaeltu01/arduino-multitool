#include <LiquidCrystal.h>

byte goalLeft[8] = {
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001
};

byte goalRight[8] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
};

// Setup functions for the LCD
void calibrate();


// Display functions
void displayNotePlayer(bool playing, char* note);
void displayTuner(int accuracy, char* note);
void displayMetronome(bool playing, int bpm);
