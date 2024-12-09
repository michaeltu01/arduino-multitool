//0 is instrument changing for tuner state
//1 is tuner state 
//2 is metronome on state
//3 metronome off
//4 is note playing on state
//5 is note playing off state


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
    case 0: // tuner 'off', instrument change setting
      if (toolChangeButtonPressed) {
        toolChangeButtonPressed = false;
        interrupts();
        currState = 3;

        displayMetronome(false, bpm);
      } else if (onOffButtonPressed) {
        onOffButtonPressed = false;
        interrupts();
        currState = 1;

        // don't display tuner, tunerLoop currently handles
      } else {
        interrupts();
        // nothing to do here; just wait for an input 
        // (the inputs will call a display func directly if needed)
      }
      break;
    case 1: // tuner on, change note 'downward'
      if (toolChangeButtonPressed) {
        toolChangeButtonPressed = false;
        interrupts();
        currState = 3;

        displayMetronome(false, bpm);
      } else if (onOffButtonPressed) {
        onOffButtonPressed = false;
        interrupts();
        currState = 0;

        displayTunerInstrument(instruments[currInstrument], notes);
      } else {
        interrupts();
        tunerLoop();
      }
      break;
    case 2: // metronome on
      if (toolChangeButtonPressed) {
        toolChangeButtonPressed = false;
        interrupts();
        currState = 5;

        displayNotePlayer(false, notes[currNote]);
      } else if (onOffButtonPressed) {
        onOffButtonPressed = false;
        interrupts();
        currState = 3;

        displayMetronome(false, bpm);
      } else {
        interrupts();
        metronomeLoop();
      }
      break;
    case 3: // metronome off
      if (toolChangeButtonPressed) {
        toolChangeButtonPressed = false;
        interrupts();
        currState = 5;

        displayNotePlayer(false, notes[currNote]);
      } else if (onOffButtonPressed) {
        onOffButtonPressed = false;
        interrupts();
        currState = 2;

        displayMetronome(true, bpm);
      } else {
        interrupts();
        // nothing to do here; just wait for an input 
        // (the inputs will call a display func directly if needed)
      }
      break;
    case 4:// note playing on
      if (toolChangeButtonPressed) {
        toolChangeButtonPressed = false;
        interrupts();
        currState = 1;

        // don't display tuner, tunerLoop currently handles
      } else if (onOffButtonPressed) {
        onOffButtonPressed = false;
        interrupts();
        currState = 5;

        displayNotePlayer(false, notes[currNote]);
      } else {
        interrupts();
        notePlayingLoop();
      }
      break;
    case 5:// note playing off
      if (toolChangeButtonPressed) {
        toolChangeButtonPressed = false;
        interrupts();
        currState = 1;

        // don't display tuner, tunerLoop currently handles
      } else if (onOffButtonPressed) {
        onOffButtonPressed = false;
        interrupts();
        currState = 4;

        displayNotePlayer(true, notes[currNote]);
      } else {
        interrupts();
        // nothing to do here; just wait for an input 
        // (the inputs will call a display func directly if needed)
      }
      break;
  }
}
