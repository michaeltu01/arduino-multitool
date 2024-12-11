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

//Increase the index of allNotes that noteplayer is using. If at the end of list, loop to the beginning. 
void changeCurrNoteUpward() {
  if (index >= 35) {
    index = 0;
  } else {
    index++;
  }
}

//Decrease the index of allNotes that noteplayer is using. If at the beginning of list, loop to the end
void changeCurrNoteDownward() {
  if (index <= 0) {
    index = 35;
  } else {
    index--;
  }
}

void changeCurrTunerNoteUpward() {
  if (currTunerNote < (numOfNotes[currInstrument] - 1)) {
    currTunerNote += 1;
  } else {
    currTunerNote = 0;
  }
}

void changeCurrTunerNoteDownward() {
  if (currTunerNote > 0) {
    currTunerNote -= 1;
  } else {
    currTunerNote = (numOfNotes[currInstrument] - 1);
  }
}

void changeCurrInstrumentUpward() {
  // Serial.println("instruments changed up");
  if (currInstrument < (lengthofInstrumentArray - 1)) {
    currInstrument += 1;
  } else {
    currInstrument = 0;
  }
}

void changeCurrInstrumentDownward() {
    if (currInstrument > 0) {
    currInstrument -= 1;
  } else {
    currInstrument = (lengthofInstrumentArray - 1);
  }
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
    case INSTRUMENT_CHANGE: //tuner 'off', change instrument 'upward'
      changeCurrInstrumentUpward();
      displayTunerInstrument(instruments[currInstrument], tunerNotes[currInstrument]);
      break;
    case TUNER_ON: //tuner on, change note 'upward'
      changeCurrTunerNoteUpward();
      displayTuner(false, 0, tunerNotes[currInstrument][currTunerNote]);
      break;
    case METRONOME_ON: // metronome on
      //Increase bpm by 5 until it reaches maxBPM.
      if(bpm + 5 <= maxBPM){
        bpm += 5;
      }
      displayMetronome(true, bpm);
      break;
    case METRONOME_OFF: // metronome off
      if(bpm + 5 <= maxBPM){
        bpm += 5;
      }
      displayMetronome(false, bpm);
      break;
    case NOTE_PLAYER_ON: // note playing on
      changeCurrNoteUpward();
      displayNotePlayer(true, allNotes[index].name);
      break;
    case NOTE_PLAYER_OFF: // note playing off
      changeCurrNoteUpward();
      displayNotePlayer(false, allNotes[index].name);
      break;
  }
}

void downButtonISR(){
  switch (currState) {
    case INSTRUMENT_CHANGE: // tuner 'off', change instrument 'downward'
      changeCurrInstrumentDownward();
      displayTunerInstrument(instruments[currInstrument], tunerNotes[currInstrument]);
      break;
    case TUNER_ON: // tuner on, change note 'downward'
      changeCurrTunerNoteDownward();
      displayTuner(false, 0, tunerNotes[currInstrument][currTunerNote]);
      break;
    case METRONOME_ON: // metronome on
    //Decrease bpm by 5 until it reaches minBPM.
      if (bpm - 5 >= minBPM) {
        bpm -= 5;
      }
      displayMetronome(true, bpm);
      break;
    case METRONOME_OFF: // metronome off
      if (bpm - 5 >= minBPM) {
        bpm -= 5;
      }
      displayMetronome(false, bpm);
      break;
    case NOTE_PLAYER_ON:// note playing on
      changeCurrNoteDownward();
      displayNotePlayer(true, allNotes[index].name);
      break;
    case NOTE_PLAYER_OFF:// note playing off
      changeCurrNoteDownward();
      displayNotePlayer(false, allNotes[index].name);
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

