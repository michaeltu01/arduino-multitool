#include "arduino_multitool.h"

/* 

  arduino_multitool.ino

  Central file that runs the Arduino Multitool.

*/

void setup() {
  // put your setup code here, to run once:
  initializeLCD();

  notePlayerSetup();
  
  //calibrate();
}

void loop() {
  // put your main code here, to run repeatedly:
  displayTuner(0, "A4");
  notePlayingLoop();
  delay(100);
}
