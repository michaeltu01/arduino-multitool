// NEW FSM STATE MAPPINGS TO ALIGN WITH FSM DIAGRAM:
// 1 is tuner state 
// 2 is instrument changing for tuner state
// 3 is metronome on state
// 4 metronome off
// 5 is note playing on state
// 6 is note playing off state

/*
  Function to handle the FSM! State is tracked using the global variable
    currState (it's a global variable so that the ISR functions can view it, 
    since ISRs can't take inputs).
  The function will alter toolChangeButtonPressed and onOffButtonPressed after a 
    state transition.
  Inputs: None
  Output: None
*/
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
      if (toolChangeButtonPressed) {   // TRANSITION 1-3; Can't switch out of the tuner state
        toolChangeButtonPressed = false;
        interrupts();
        currState = METRONOME_OFF;

        displayMetronome(false, bpm);
      } else if (onOffButtonPressed) {  // TRANSITION 1-2; FIXME: Screen doesn't change to displayTunerInstrument() until note is read in after pressing ON/OFF button
        onOffButtonPressed = false;
        interrupts();
        currState = INSTRUMENT_CHANGE;

        displayTunerInstrument(instruments[currInstrument], tunerNotes[currInstrument]);
      } else {  // TRANSITION 1-1; FIXME: Changing the reference note in tuner = ON mode doesn't work
        interrupts();
        delay(100);
        tunerLoop();
      }
      break;
    case INSTRUMENT_CHANGE: // tuner 'off', instrument change setting
      if (toolChangeButtonPressed) {  // TRANSITION 2-3
        toolChangeButtonPressed = false;
        interrupts();
        // currState = 3;
        currState = METRONOME_OFF;
        displayMetronome(false, bpm);
      } else if (onOffButtonPressed) {  // TRANSITION 2-1
        onOffButtonPressed = false;
        interrupts();
        currState = TUNER_ON;

        displayTuner(false, 0, tunerNotes[currInstrument][currTunerNote]); // NOTE: why is displayAccuracy important?
      } else {  // TRANSITION 2-2
        interrupts();
        // nothing to do here; just wait for an input 
        // (the inputs will call a display func directly if needed)

        // Pet WDT
        petWDT();
      }
      break;
    case METRONOME_ON: // metronome on
      if (toolChangeButtonPressed) {  // TRANSITION 3-5
        toolChangeButtonPressed = false;
        interrupts();
        currState = NOTE_PLAYER_OFF;

        displayNotePlayer(false, allNotes[currNote].name);
      } else if (onOffButtonPressed) {  // TRANSITION 3-4
        onOffButtonPressed = false;
        interrupts();
        currState = METRONOME_OFF;

        displayMetronome(false, bpm);
      } else {  // TRANSITION 3-3
        interrupts();
        metronomeLoop();
      }
      break;
    case METRONOME_OFF: // metronome off
      if (toolChangeButtonPressed) {  // TRANSITION 4-6; FIXME: sometimes takes this transition non-deterministically (hardware?)
        toolChangeButtonPressed = false;
        interrupts();

        Serial.println("METRONOME_OFF TO NOTE_PLAYER_OFF");
        currState = NOTE_PLAYER_OFF;

        displayNotePlayer(false, allNotes[currNote].name);
      } else if (onOffButtonPressed) {  // TRANSITION 4-3
        onOffButtonPressed = false;
        interrupts();
        currState = METRONOME_ON;

        displayMetronome(true, bpm);
      } else {  // TRANSITION 4-4
        interrupts();
        // nothing to do here; just wait for an input 
        // (the inputs will call a display func directly if needed)

        // Pet WDT
        petWDT();
      }
      break;
    case NOTE_PLAYER_ON:// note playing on
      if (toolChangeButtonPressed) {  // TRANSITION 5-1
        toolChangeButtonPressed = false;
        interrupts();

        currState = TUNER_ON;

        noTone(buzzerPin);
        displayTuner(false, 0, tunerNotes[currInstrument][currTunerNote]);
      } else if (onOffButtonPressed) {  // TRANSITION 5-6
        onOffButtonPressed = false;
        interrupts();

        currState = NOTE_PLAYER_OFF;
        
        noTone(buzzerPin);
        displayNotePlayer(false, allNotes[currNote].name);
      } else {  // TRANSITION 5-5
        interrupts();

        notePlayingLoop();
      }
      break;
    case NOTE_PLAYER_OFF:// note playing off

      if (toolChangeButtonPressed) {  // TRANSITION 6-1
        toolChangeButtonPressed = false;
        interrupts();
        
        Serial.println("NOTE_PLAYER_OFF TO TUNER_ON");
        currState = TUNER_ON;

        displayTuner(false, 0, tunerNotes[currInstrument][currTunerNote]);
      } else if (onOffButtonPressed) {  // TRANSITION 6-5
        onOffButtonPressed = false;
        interrupts();

        currState = NOTE_PLAYER_ON;

        displayNotePlayer(true, allNotes[currNote].name);
      } else {  // TRANSITION 6-6
        interrupts();

        // nothing to do here; just wait for an input 
        // (the inputs will call a display func directly if needed)

        // Pet WDT
        petWDT();
      }
      break;
  }
}


