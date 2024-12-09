void buttonSetup() {
  pinMode(upButtonPin, INPUT);
  pinMode(downButtonPin, INPUT);
  pinMode(onOffButtonPin, INPUT);
  pinMode(toolChangeButtonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(upButtonPin), upButtonISR, RISING);
  attachInterrupt(digitalPinToInterrupt(downButtonPin), downButtonISR, RISING);
  attachInterrupt(digitalPinToInterrupt(onOffButtonPin), onOffButtonISR,RISING);
  attachInterrupt(digitalPinToInterrupt(toolChangeButtonPin),toolChangeButtonISR, RISING);
}

void changeCurrNoteUpward() {
  if(index >= 35){
    index = 0;
  }else{
    index++;
  }
}

void changeCurrNoteDownward() {
  if (index <= 0) {
    index = 35;
  } else {
    index--;
  }
}

void changeCurrInstrumentUpward() {
 // Serial.println("instruments changed up");
  currInstrument += 1;
  currInstrument = currInstrument % (lengthofInstrumentArray);
  // return instruments[currInstrument];
}

void changeCurrInstrumentDownward() {
  //Serial.println("instruments changed down");
  currInstrument -= 1;
  currInstrument = currInstrument % (lengthofInstrumentArray);
  // return instruments[currInstrument];
}

//tuner toggles between an instrument changing state and an actual tuning state 
//0 is instrument changing for tuner state
//1 is tuner state 
//2 is metronome on state
//3 metronome off
//4 is note playing on state
//5 is note playing off state

void upButtonISR(){
  switch (currState) {
    case 0: //tuner 'off', change instrument 'upward'
      changeCurrInstrumentUpward();
      displayTunerInstrument(instruments[currInstrument], notes);
      break;
    case 1: //tuner on, change note 'upward'
      changeCurrNoteUpward();
      displayTuner(false, 0, notes[currNote]);
      break;
    case 2: // metronome on
      if(bpm + 5 <= maxBPM){
        bpm += 5;
      }
      displayMetronome(true, bpm);
      break;
    case 3: // metronome off
      if(bpm + 5 <= maxBPM){
        bpm += 5;
      }
      displayMetronome(false, bpm);
      break;
    case 4: // note playing on
      changeCurrNoteUpward();
      displayNotePlayer(true, allNotes[index].name);
      //displayNotePlayer(true, notes[currNote]);
      break;
    case 5: // note playing off
      changeCurrNoteUpward();
      displayNotePlayer(true, allNotes[index].name);
      //displayNotePlayer(false, notes[currNote]);
      break;
  }
}

void downButtonISR(){
  switch (currState) {
    case 0: // tuner 'off', change instrument 'downward'
      changeCurrInstrumentDownward();
      displayTunerInstrument(instruments[currInstrument], notes);
      break;
    case 1: // tuner on, change note 'downward'
      changeCurrNoteDownward();
      displayTuner(false, 0, notes[currNote]);
      break;
    case 2: // metronome on
      if (bpm - 5 >= minBPM) {
        bpm -= 5;
      }
      displayMetronome(true, bpm);
      break;
    case 3: // metronome off
      if (bpm - 5 >= minBPM) {
        bpm -= 5;
      }
      displayMetronome(false, bpm);
      break;
    case 4:// note playing on
      changeCurrNoteDownward();
      displayNotePlayer(true, allNotes[index].name);
      //displayNotePlayer(true, notes[currNote]);
      break;
    case 5:// note playing off
      changeCurrNoteDownward();
      displayNotePlayer(true, allNotes[index].name);
      //displayNotePlayer(false, notes[currNote]);
      break;
  }
}

// we only want to track whether the button has been pressed
// the fsm handles changing state; so we only have to do this:

void onOffButtonISR(){
  onOffButtonPressed = true;
}

void toolChangeButtonISR(){
  toolChangeButtonPressed = true;
}

