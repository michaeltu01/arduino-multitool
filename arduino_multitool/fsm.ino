//0 is instrument changing for tuner state
//1 is tuner state 
//2 is metronome on state
//3 metronome off
//4 is note playing on state
//5 is note playing off state


// NEW FSM STATE MAPPINGS TO ALIGN WITH FSM DIAGRAM:
// 1 is tuner state 
// 2 is instrument changing for tuner state
// 3 is metronome on state
// 4 metronome off
// 5 is note playing on state
// 6 is note playing off state


void fsm() {
  // To avoid race conditions w/ state switching, pause interrupts:
  noInterrupts();

  /* 
    Here's how the FSM works:
    If a button has been pressed since we last looped, we do a switch.
    If we are *entering* into a state, we call its display function
    (to start rendering that screen). Otherwise, we call the loop
    for the current state.

    Exceptions:
    - tunerLoop() calls the display function every tick 
      (this will cause flickering and needs to be fixed!)
    - off states don't have any code to be run
      and that's all handled via interrupts
  */
  switch (currState) {
    case TUNER_ON: // tuner on, change note 'downward'
      //Serial.println("In case 1");
      if (toolChangeButtonPressed) {   // TRANSITION 1-3; Can't switch out of the tuner state
        toolChangeButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        currState = METRONOME_OFF;

        displayMetronome(false, bpm);
      } else if (onOffButtonPressed) {  // TRANSITION 1-2; FIXME: Screen doesn't change to displayTunerInstrument() until note is read in after pressing ON/OFF button
        onOffButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        currState = INSTRUMENT_CHANGE;

        displayTunerInstrument(instruments[currInstrument], tunerNotes[currInstrument]);
      } else {  // TRANSITION 1-1; FIXME: Changing the reference note in tuner = ON mode doesn't work
        interrupts();
       // Serial.println("interrupts called");
        delay(100);
        tunerLoop();
      }
      break;
    case INSTRUMENT_CHANGE: // tuner 'off', instrument change setting
      //Serial.println("In case 2");
      if (toolChangeButtonPressed) {  // TRANSITION 2-3
       // Serial.println("tool change button is pressed");
        toolChangeButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        // currState = 3;
        currState = METRONOME_OFF;
        displayMetronome(false, bpm);
      } else if (onOffButtonPressed) {  // TRANSITION 2-1
       // Serial.println("onoff button pressed");
        onOffButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        currState = TUNER_ON;

        displayTuner(false, 0, tunerNotes[currInstrument][currTunerNote]); // NOTE: why is displayAccuracy important?
      } else {  // TRANSITION 2-2
       // Serial.println("no buttons pressed");
        interrupts();
       // Serial.println("interrupts called");
        // nothing to do here; just wait for an input 
        // (the inputs will call a display func directly if needed)

        // Pet WDT
        petWDT();
      }
      break;
    case METRONOME_ON: // metronome on
     // Serial.println("In case 3");
      if (toolChangeButtonPressed) {  // TRANSITION 3-5
        toolChangeButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        currState = NOTE_PLAYER_OFF;

        displayNotePlayer(false, allNotes[index].name);
      } else if (onOffButtonPressed) {  // TRANSITION 3-4
        onOffButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        currState = METRONOME_OFF;

        displayMetronome(false, bpm);
      } else {  // TRANSITION 3-3
        interrupts();
       // Serial.println("interrupts called");
        metronomeLoop();
      }
      break;
    case METRONOME_OFF: // metronome off
     // Serial.println("In case 4");
      if (toolChangeButtonPressed) {  // TRANSITION 4-6; FIXME: sometimes takes this transition non-deterministically (hardware?)
        toolChangeButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");

        Serial.println("METRONOME_OFF TO NOTE_PLAYER_OFF");
        currState = NOTE_PLAYER_OFF;

        displayNotePlayer(false, allNotes[index].name);
      } else if (onOffButtonPressed) {  // TRANSITION 4-3
        onOffButtonPressed = false;
        interrupts();
        //Serial.println("interrupts called");
        currState = METRONOME_ON;

        displayMetronome(true, bpm);
      } else {  // TRANSITION 4-4
        interrupts();
        //Serial.println("interrupts called");
        // nothing to do here; just wait for an input 
        // (the inputs will call a display func directly if needed)

        // Pet WDT
        petWDT();
      }
      break;
    case NOTE_PLAYER_ON:// note playing on
      //Serial.println("In case 5");
      if (toolChangeButtonPressed) {  // TRANSITION 5-1
        toolChangeButtonPressed = false;
        interrupts();
        //Serial.println("interrupts called");
        currState = TUNER_ON;

        noTone(buzzerPin);
        displayTuner(false, 0, tunerNotes[currInstrument][currTunerNote]);
      } else if (onOffButtonPressed) {  // TRANSITION 5-6
        onOffButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        currState = NOTE_PLAYER_OFF;
        
        noTone(buzzerPin);
        displayNotePlayer(false, allNotes[index].name);
      } else {  // TRANSITION 5-5
        interrupts();
       // Serial.println("interrupts called");
        notePlayingLoop();
      }
      break;
    case NOTE_PLAYER_OFF:// note playing off
     // Serial.println("In case 6");
      if (toolChangeButtonPressed) {  // TRANSITION 6-1
        toolChangeButtonPressed = false;
        interrupts();
        
        Serial.println("NOTE_PLAYER_OFF TO TUNER_ON");
        currState = TUNER_ON;

        displayTuner(false, 0, tunerNotes[currInstrument][currTunerNote]);
      } else if (onOffButtonPressed) {  // TRANSITION 6-5
        onOffButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        currState = NOTE_PLAYER_ON;

        displayNotePlayer(true, allNotes[index].name);
      } else {  // TRANSITION 6-6
        interrupts();
        //  Serial.println("interrupts called");
        // nothing to do here; just wait for an input 
        // (the inputs will call a display func directly if needed)

        // Pet WDT
        petWDT();
      }
      break;
  }
}
