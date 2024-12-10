void notePlayerSetup() {
  displayNotePlayer(true, allNotes[index].name);
}

void notePlayingLoop() { 
  tone(buzzerPin, (int) allNotes[index].freq);

  // Pet WDT
  petWDT();
}