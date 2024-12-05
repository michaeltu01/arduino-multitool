/* 

  tuner.ino

  Main file for tuner mode.

*/

void tunerSetup() {
  micTestSetup();
}

/*

  binarySearch()

  Returns the index of the closest frequency in NOTE_FREQUENCIES

*/
// int binarySearch(double freq, int left, int right) {
//   middle = (left + right) / 2;

//   if 
// }

// void tunerToLCD(double peakFreq) {

// }

void tunerLoop() {
  micTestLoop();
  // double peakFrequency = testMicFrequency();
  // double peakFrequency = micToFreq();

  // LCD display output based on the peak frequency
  // tunerToLCD(peakFrequency);

  // delay(500);
}