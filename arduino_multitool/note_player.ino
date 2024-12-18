/*
  Initialization of anything the note player needs.
  Input: None
  Output: None
*/
void notePlayerSetup() {

}

/*
  The loop for main note player functionality.
  Inputs: None
  Output: None
*/
void notePlayingLoop() { 
  //always play the tone of the current index. Index may change due to external input in buttons.ino
  tone(buzzerPin, (int) allNotes[currNote].freq);

  // Pet WDT
  petWDT();
}