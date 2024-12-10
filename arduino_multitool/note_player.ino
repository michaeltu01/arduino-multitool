// const int buzzerPin = 13;
// const int upButtonPin = 12;
// const int downButtonPin = 11;
// const int noteArray[] = {196, 293, 440, 659};
// char* noteStringArray[] = {"G", "D", "A", "E"};
// int index = 0;

void notePlayerSetup() {
  /*pinMode(upButtonPin, INPUT);
  pinMode(downButtonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(upButtonPin), nextButtonISR, RISING);
  attachInterrupt(digitalPinToInterrupt(downButtonPin), prevButtonISR, RISING);
  displayNotePlayer(true, noteStringArray[index]);*/
  displayNotePlayer(true, allNotes[index].name);
}

void notePlayingLoop() { 
  tone(buzzerPin, (int) allNotes[index].freq);

  // Pet WDT
  petWDT();
}

// void nextButtonISR(){
//   if(index == 3){
//     index = 0;
//   }else{
//     index++;
//   }
//   displayNotePlayer(true, noteStringArray[index]);
// }

// void prevButtonISR(){
//   if (index == 0) {
//     index = 3;
//   } else {
//     index--;
//   }
//   displayNotePlayer(true, noteStringArray[index]);
// }