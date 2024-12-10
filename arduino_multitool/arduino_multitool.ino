#include "arduino_multitool.h"
/* 

  arduino_multitool.ino

  Central file that runs the Arduino Multitool.

*/

const int upButtonPin = 12;
const int downButtonPin = 11;
const int onOffButtonPin = 3;
const int toolChangeButtonPin = 2;

//Global variables for note player
int index = 0;

// Global variables for state management
// int currState = 3; //curr state
fsm_state currState = METRONOME_OFF;
bool toolChangeButtonPressed = false;
bool onOffButtonPressed = false;

// Metronome vars
const int buzzerPin = 13;
const int buzzerLength = 50;
const int minBPM = 40;
const int maxBPM = 250;

int bpm = 60;

// Tuner vars
const struct Note tunerNotes[2][6] = {
  {{"E2", 82.41}, {"A2", 110.00}, {"D3", 146.83}, {"G3", 196.00}, {"B3", 246.94}, {"E4", 329.63}}, 
  {{"G3", 196.00}, {"D4", 293.66}, {"A4", 440.00}, {"E5", 659.26}}};
const String instruments[2] = {"GUITAR", "VIOLIN"};
const int numOfNotes[2] = {6, 4};
int currNote = 0; //index of the note in array
int currTunerNote = 0;
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

  // Initial setup
  displayMetronome(false, bpm);

  // Initialize WDT
  initWDT();
  petWDT();
}

void loop() {
  // put your main code here, to run repeatedly:
  fsm();
}
