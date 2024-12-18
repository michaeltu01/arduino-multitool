/*
  Initialization of anything the metronome needs.
  Input: None
  Output: None
*/
void metronomeSetup() {

}

/*
  The loop for main metronome functionality.
  Inputs: None
  Output: None
*/
void metronomeLoop() {
  //Play a beep for [buzzerLength] time at a rate of bpm. 
  tone(buzzerPin, 440);
  delay(buzzerLength);
  noTone(buzzerPin);
  delay(60000/bpm - buzzerLength); //buzz at a certain bpm

  // Pet WDT
  petWDT();
}

