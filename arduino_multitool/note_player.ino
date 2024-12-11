void notePlayerSetup() {

}

void notePlayingLoop() { 
  //always play the tone of the current index. Index may change due to external input in buttons.ino
  tone(buzzerPin, (int) allNotes[index].freq);

  // Pet WDT
  petWDT();
}