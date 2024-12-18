/*
  Setup all of the relevant pins for the four buttons.
   We use INPUT and RISING to avoid debouncing. 
  Inputs: None
  Output: None
*/
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

/*
  Increment the index of allNotes that noteplayer is using. 
    If at the end of list, loop to the beginning. 
  Inputs: None
  Output: None
  Alters the global variable currNote
*/
void changeCurrNoteUpward() {
  if (currNote >= 35 || currNote < 0) {
    currNote = 0;
  } else {
    currNote++;
  }
}

/*
  Decrement the index of allNotes that noteplayer is using. 
    If at the beginning of list, loop to the end
  Inputs: None
  Output: None
  Alters the global variable currNote
*/
void changeCurrNoteDownward() {
  if (currNote <= 0 || currNote > 35) {
    currNote = 35;
  } else {
    currNote--;
  }
}

/*
  Increment the current BPM by 5 unless it has hit maxBPM.
  Inputs: None
  Output: None
  Alters the global variable bpm
*/
//Increase bpm by 5 until it reaches maxBPM.
void changeBPMUpward(){
  //out of bounds check
  if(bpm < minBPM){
    bpm = minBPM;
  }else if (bpm > maxBPM){
    bpm = maxBPM;
  }

  if(bpm + 5 <= maxBPM){
      bpm += 5;
  }
}

/*
  Decrement the current BPM by 5 unless it has hit minBPM.
  Inputs: None
  Output: None
  Alters the global variable bpm
*/
void changeBPMDownward(){
  //out of bounds check
  if(bpm < minBPM){
    bpm = minBPM;
  }else if (bpm > maxBPM){
    bpm = maxBPM;
  }

  if(bpm - 5 >= minBPM){
      bpm -= 5;
  }
}

/*
  Increment the index of the tuner note. 
    If at the end of the list, wrap around to the beginning.
  Inputs: None
  Output: None
  Alters the global variable currTunerNote
*/
void changeCurrTunerNoteUpward() {
  if (currTunerNote < (numOfNotes[currInstrument] - 1)) {
    currTunerNote += 1;
  } else {
    currTunerNote = 0;
  }
}

/*
  Decrement the index of the tuner note. 
    If at the beginning of the list, wrap around to the end.
  Inputs: None
  Output: None
  Alters the global variable currTunerNote
*/
void changeCurrTunerNoteDownward() {
  if (currTunerNote > 0) {
    currTunerNote -= 1;
  } else {
    currTunerNote = (numOfNotes[currInstrument] - 1);
  }
}

/*
  Increment the index of the instrument. 
    If at the end of the list, wrap around to the beginning.
  Inputs: None
  Output: None
  Alters the global variable currInstrument
*/
void changeCurrInstrumentUpward() {
  if (currInstrument < (lengthofInstrumentArray - 1)) {
    currInstrument += 1;
  } else {
    currInstrument = 0;
  }
}

/*
  Decrement the index of the instrument. 
    If at the beginning of the list, wrap around to the end.
  Inputs: None
  Output: None
  Alters the global variable currInstrument
*/
void changeCurrInstrumentDownward() {
    if (currInstrument > 0) {
    currInstrument -= 1;
  } else {
    currInstrument = (lengthofInstrumentArray - 1);
  }
}

/*
  Function to handle behavior when the up button is pressed.
    (This is hooked up to the ISR)
  Inputs: None
  Output: None
  Depends on the state of the FSM (which is stored as a global variable)
*/
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
      changeBPMUpward();
      displayMetronome(true, bpm);
      break;
    case METRONOME_OFF: // metronome off
      changeBPMDownward();
      displayMetronome(false, bpm);
      break;
    case NOTE_PLAYER_ON: // note playing on
      changeCurrNoteUpward();
      displayNotePlayer(true, allNotes[currNote].name);
      break;
    case NOTE_PLAYER_OFF: // note playing off
      changeCurrNoteUpward();
      displayNotePlayer(false, allNotes[currNote].name);
      break;
  }
}

/*
  Function to handle behavior when the down button is pressed.
    (This is hooked up to the ISR)
  Inputs: None
  Output: None
  Depends on the state of the FSM (which is stored as a global variable)
*/
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
      displayNotePlayer(true, allNotes[currNote].name);
      break;
    case NOTE_PLAYER_OFF:// note playing off
      changeCurrNoteDownward();
      displayNotePlayer(false, allNotes[currNote].name);
      break;
  }
}

// we only want to track whether the button has been pressed
// the fsm handles changing state; so we only have to do this:

/*
  Function to handle behavior when the on/off button is pressed.
  Inputs: None
  Output: None
*/
void onOffButtonISR(){
  onOffButtonPressed = true;
}

/*
  Function to handle behavior when the tool change button is pressed.
  Inputs: None
  Output: None
*/
void toolChangeButtonISR(){
  toolChangeButtonPressed = true;
}

