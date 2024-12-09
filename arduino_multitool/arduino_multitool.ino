#include "arduino_multitool.h"

/* 

  arduino_multitool.ino

  Central file that runs the Arduino Multitool.

*/

void setup() {
  // put your setup code here, to run once:
  
  initializeLCD();
  //calibrate();

  notePlayerSetup();
  metronomeSetup();
  tunerSetup();

  // Set up button pins with internal pull-up resistors
  pinMode(instrumentButtonPin, INPUT);
  pinMode(noteButtonPin, INPUT);
  pinMode(onOffButtonPin, INPUT);
  pinMode(toolChangeButtonPressed, INPUT);
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
