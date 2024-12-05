/* 

  arduino_multitool.ino

  Central file that runs the Arduino Multitool.

*/


void setup() {
  // put your setup code here, to run once:
  // notePlayerSetup();
  // metronomeSetup();
  // tunerSetup();
  micReceiverSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  // notePlayingLoop();
  // metronomeLoop();
  // tunerLoop();
  micReceiverLoop();
}
