#include "arduino_multitool.h"

/* 

  arduino_multitool.ino

  Central file that runs the Arduino Multitool.

*/

const int upButtonPin = 12;
const int downButtonPin = 11;
const int onOffButtonPin = 3;
const int toolChangeButtonPin = 2;


// Global variables for state management
int currState = 2; //curr state
bool toolChangeButtonPressed = false;
bool onOffButtonPressed = false;

// Metronome vars
const int buzzerPin = 13;
const int buzzerLength = 50;
const int minBPM = 40;
const int maxBPM = 250;

int bpm = 60;

// Tuner vars
const String notes[8] = {"C3", "D3", "E3", "F3", "G3", "A3", "B3", "C4"};
const String instruments[2] = {"GUITAR", "VIOLIN"};
int currNote = 0; //index of the note in array
int currInstrument = 0; //index of the instrument in array
int lengthofNoteArray = 8;
int lengthofInstrumentArray = 2;


void setup() {
  // put your setup code here, to run once:
  
  initializeLCD();
  //calibrate();

  notePlayerSetup();
  metronomeSetup();
  tunerSetup();

  // Set up button pins with internal pull-up resistors
  buttonSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  //displayTuner(0, "A4");
  //notePlayingLoop();
  // metronomeLoop();
  //delay(100);
  fsm();
}
