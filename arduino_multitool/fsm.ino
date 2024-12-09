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
      //Serial.println("In case 0");
      if (toolChangeButtonPressed) {
       // Serial.println("tool change button is pressed");
        toolChangeButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        currState = 3;

        displayMetronome(false, bpm);
      } else if (onOffButtonPressed) {
       // Serial.println("onoff button pressed");
        onOffButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        currState = 1;

        // don't display tuner, tunerLoop currently handles
      } else {
       // Serial.println("no buttons pressed");
        interrupts();
       // Serial.println("interrupts called");
        // nothing to do here; just wait for an input 
        // (the inputs will call a display func directly if needed)
      }
      break;
    case 1: // tuner on, change note 'downward'
      //Serial.println("In case 1");
      if (toolChangeButtonPressed) {
        toolChangeButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        currState = 3;

        displayMetronome(false, bpm);
      } else if (onOffButtonPressed) {
        onOffButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        currState = 0;

        displayTunerInstrument(instruments[currInstrument], notes);
      } else {
        interrupts();
       // Serial.println("interrupts called");
        tunerLoop();
      }
      break;
    case 2: // metronome on
     // Serial.println("In case 2");
      if (toolChangeButtonPressed) {
        toolChangeButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        currState = 5;

        displayNotePlayer(false, notes[currNote]);
      } else if (onOffButtonPressed) {
        onOffButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        currState = 3;

        displayMetronome(false, bpm);
      } else {
        interrupts();
       // Serial.println("interrupts called");
        metronomeLoop();
      }
      break;
    case 3: // metronome off
     // Serial.println("In case 3");
      if (toolChangeButtonPressed) {
        toolChangeButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        currState = 5;

        displayNotePlayer(false, notes[currNote]);
      } else if (onOffButtonPressed) {
        onOffButtonPressed = false;
        interrupts();
        //Serial.println("interrupts called");
        currState = 2;

        displayMetronome(true, bpm);
      } else {
        interrupts();
        //Serial.println("interrupts called");
        // nothing to do here; just wait for an input 
        // (the inputs will call a display func directly if needed)
      }
      break;
    case 4:// note playing on
      //Serial.println("In case 4");
      if (toolChangeButtonPressed) {
        toolChangeButtonPressed = false;
        interrupts();
        //Serial.println("interrupts called");
        currState = 1;

        // don't display tuner, tunerLoop currently handles
      } else if (onOffButtonPressed) {
        onOffButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        currState = 5;

        displayNotePlayer(false, notes[currNote]);
      } else {
        interrupts();
       // Serial.println("interrupts called");
        notePlayingLoop();
      }
      break;
    case 5:// note playing off
     // Serial.println("In case 5");
      if (toolChangeButtonPressed) {
        toolChangeButtonPressed = false;
        interrupts();
      //  Serial.println("interrupts called");
        currState = 1;

        // don't display tuner, tunerLoop currently handles
      } else if (onOffButtonPressed) {
        onOffButtonPressed = false;
        interrupts();
       // Serial.println("interrupts called");
        currState = 4;

        displayNotePlayer(true, notes[currNote]);
      } else {
        interrupts();
      //  Serial.println("interrupts called");
        // nothing to do here; just wait for an input 
        // (the inputs will call a display func directly if needed)
      }
      break;
  }
}
