
/*
 * A struct to keep state inputs
 */

typedef struct {
  bool mock_upButtonPressed;
  bool mock_downButtonPressed;

} state_inputs;


bool testTransition(fsm_state startState, fsm_state endState, state_inputs testStateInputs, state_vars startStateVars, state_vars endStateVars, bool verbos);
/*
 * Given a start state, inputs, and starting values for state variables, tests that
 * updateFSM returns the correct end state and updates the state variables correctly
 * returns true if this is the case (test passed) and false otherwise (test failed)
 */

 /*        
 * Helper function for printing states
 */
char* s2str(fsm_state s) {
  switch(s) {
    case TUNER_ON:
    return "(1) TUNER_ON";
    case INSTRUMENT_CHANGE:
    return "(2) INSTRUMENT_CHANGE";
    case METRONOME_ON:
    return "(3) METRONOME_ON";
    case METRONOME_OFF:
    return "(4) METRONOME_OFF";
    case NOTE_PLAYER_ON:
    return "(5) NOTE_PLAYER_ON";
    case NOTE_PLAYER_OFF:
    return "(6) NOTE_PLAYER_OFF";
    default:
    return "???";
  }
}


bool testTransition(fsm_state startState, fsm_state endState, state_inputs testStateInputs, state_vars startStateVars, state_vars endStateVars, bool verbos) {
  int test_bpm = startStateVars.test_bpm;
  int test_currNote = startStateVars.test_currNote;
  int test_currTunerNote = startStateVars.test_currTunerNote;
  int test_currInstrument = startStateVars.test_currInstrument;

  // test_instruments = startStateVars.instruments these should remain as their global variables
  // test_allNotes = startStateVars.allNotes
  // test_tunerNotes = startStateVars.tunerNotes
  bool test_toolButtonPressed = startStateVars.test_toolButtonPressed;
  bool test_onOffButtonPressed = startStateVars.test_onOffButtonPressed;

  fsm_state resultState = mock_fsm(startState, startStateVars);
  bool passedTest = (endState == resultState and 
                    test_bpm == endStateVars.test_bpm and
                    test_currNote == endStateVars.test_currNote and
                    test_currTunerNote == endStateVars.test_currTunerNote and
                    test_currInstrument == endStateVars.test_currInstrument and
                    test_toolButtonPressed == endStateVars.test_toolButtonPressed and
                    test_onOffButtonPressed == endStateVars.test_onOffButtonPressed);
  if (! verbos) {
    return passedTest;
  } else if (passedTest) {
    char sToPrint[200];
    sprintf(sToPrint, "Test from %s to %s PASSED", s2str(startState), s2str(endState));
    Serial.println(sToPrint);
    return true;
  } else {
    char sToPrint[200];
    Serial.println(s2str(startState));
    sprintf(sToPrint, "Test from %s to %s FAILED", s2str(startState), s2str(endState));
    Serial.println(sToPrint);
    sprintf(sToPrint, "End state expected: %s | actual: %s", s2str(endState), s2str(resultState));
    Serial.println(sToPrint);
    sprintf(sToPrint, "Inputs: upButtonPressed %d | downButtonPressed %d", 
            testStateInputs.mock_upButtonPressed, testStateInputs.mock_downButtonPressed);
    Serial.println(sToPrint);

    sprintf(sToPrint, "expected: bpm: %d | currNote: %d | currTunerNote: %d | currInstrument: %d | toolButtonPressed: %d | onOffButtonPressed: %d", 
            endStateVars.test_bpm, endStateVars.test_currNote, endStateVars.test_currTunerNote, 
            endStateVars.test_currInstrument, endStateVars.test_toolButtonPressed, endStateVars.test_onOffButtonPressed);
    Serial.println(sToPrint);

    sprintf(sToPrint, "actual:   bpm: %d | currNote: %d | currTunerNote: %d | currInstrument: %d | toolButtonPressed: %d | onOffButtonPressed: %d", 
            test_bpm, test_currNote, test_currTunerNote, test_currInstrument, test_toolButtonPressed, test_onOffButtonPressed);
    Serial.println(sToPrint);

    return false;
  }
}





fsm_state mock_fsm(fsm_state startState, state_vars startStateVars) {
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
  fsm_state endState;
  switch (startState) {
    case TUNER_ON: // tuner on, change note 'downward'
      if (startStateVars.test_toolButtonPressed) {   // TRANSITION 1-3; Can't switch out of the tuner state
        startStateVars.test_toolButtonPressed = false;
        interrupts();
        endState = METRONOME_OFF;

        //displayMetronome(false, test_bpm);
      } else if (startStateVars.test_onOffButtonPressed) {  // TRANSITION 1-2; FIXME: Screen doesn't change to displayTunerInstrument() until note is read in after pressing ON/OFF button
        startStateVars.test_onOffButtonPressed = false;
        interrupts();
        endState = INSTRUMENT_CHANGE;

        //displayTunerInstrument(instruments[test_currInstrument], tunerNotes[test_currInstrument]);
      } else {  // TRANSITION 1-1; FIXME: Changing the reference note in tuner = ON mode doesn't work
        interrupts();
        delay(100);
        tunerLoop();
      }
      break;
    case INSTRUMENT_CHANGE: // tuner 'off', instrument change setting
      if (startStateVars.test_toolButtonPressed) {  // TRANSITION 2-3
        startStateVars.test_toolButtonPressed = false;
        interrupts();
        // currState = 3;
        endState = METRONOME_OFF;
        //displayMetronome(false, test_bpm);
      } else if (startStateVars.test_onOffButtonPressed) {  // TRANSITION 2-1
        startStateVars.test_onOffButtonPressed = false;
        interrupts();
        endState = TUNER_ON;

        //displayTuner(false, 0, tunerNotes[test_currInstrument][test_currTunerNote]); // NOTE: why is displayAccuracy important?
      } else {  // TRANSITION 2-2
        interrupts();
        // nothing to do here; just wait for an input 
        // (the inputs will call a display func directly if needed)

        // Pet WDT
        petWDT();
      }
      break;
    case METRONOME_ON: // metronome on
      if (startStateVars.test_toolButtonPressed) {  // TRANSITION 3-5
        startStateVars.test_toolButtonPressed = false;
        interrupts();
        endState = NOTE_PLAYER_OFF;

        //displayNotePlayer(false, allNotes[test_currNote].name);
      } else if (startStateVars.test_onOffButtonPressed) {  // TRANSITION 3-4
        startStateVars.test_onOffButtonPressed = false;
        interrupts();
        endState = METRONOME_OFF;

        //displayMetronome(false, test_bpm);
      } else {  // TRANSITION 3-3
        interrupts();
        metronomeLoop();
      }
      break;
    case METRONOME_OFF: // metronome off
      if (startStateVars.test_toolButtonPressed) {  // TRANSITION 4-6; FIXME: sometimes takes this transition non-deterministically (hardware?)
        startStateVars.test_toolButtonPressed = false;
        interrupts();

        Serial.println("METRONOME_OFF TO NOTE_PLAYER_OFF");
        endState = NOTE_PLAYER_OFF;

        //displayNotePlayer(false, allNotes[test_currNote].name);
      } else if (startStateVars.test_onOffButtonPressed) {  // TRANSITION 4-3
        startStateVars.test_onOffButtonPressed = false;
        interrupts();
        endState = METRONOME_ON;

        //displayMetronome(true, test_bpm);
      } else {  // TRANSITION 4-4
        interrupts();
        // nothing to do here; just wait for an input 
        // (the inputs will call a display func directly if needed)

        // Pet WDT
        petWDT();
      }
      break;
    case NOTE_PLAYER_ON:// note playing on
      if (startStateVars.test_toolButtonPressed) {  // TRANSITION 5-1
        startStateVars.test_toolButtonPressed = false;
        interrupts();

        endState = TUNER_ON;

        noTone(buzzerPin);
       // displayTuner(false, 0, tunerNotes[test_currInstrument][test_currTunerNote]);
      } else if (startStateVars.test_onOffButtonPressed) {  // TRANSITION 5-6
        startStateVars.test_onOffButtonPressed = false;
        interrupts();

        endState = NOTE_PLAYER_OFF;
        
        noTone(buzzerPin);
        //displayNotePlayer(false, allNotes[test_currNote].name);
      } else {  // TRANSITION 5-5
        interrupts();

        notePlayingLoop();
      }
      break;
    case NOTE_PLAYER_OFF:// note playing off

      if (startStateVars.test_toolButtonPressed) {  // TRANSITION 6-1
        startStateVars.test_toolButtonPressed = false;
        interrupts();
        
        Serial.println("NOTE_PLAYER_OFF TO TUNER_ON");
        endState = TUNER_ON;

        //displayTuner(false, 0, tunerNotes[test_currInstrument][test_currTunerNote]);
      } else if (startStateVars.test_onOffButtonPressed) {  // TRANSITION 6-5
        startStateVars.test_onOffButtonPressed = false;
        interrupts();

        endState = NOTE_PLAYER_ON;

        //displayNotePlayer(true, allNotes[test_currNote].name);
      } else {  // TRANSITION 6-6
        interrupts();

        // nothing to do here; just wait for an input 
        // (the inputs will call a display func directly if needed)

        // Pet WDT
        petWDT();
      }
      break;
  }
  return endState;
}



/*
 * Runs through all the test cases defined above
 */
bool testAllTests() {
  for (int i = 0; i < numTests; i++) {
    Serial.print("Running test ");
    Serial.println(i);
    if (!testTransition(testStatesIn[i], testStatesOut[i], testInputs[i], testVarsIn[i], testVarsOut[i], true)) {
      return false;
    }
    Serial.println();
  }
  Serial.println("All tests passed!");
  return true;
}


const state testStatesIn[3] = { (fsm_state) METRONOME_OFF
};

const state testStatesOut[3] = {
  (fsm_state) NOTE_PLAYER_OFF
};

const state_inputs testInputs[3] = {
}

const state_vars testVarsIn[3] = {

}

const state_vars testVarsOut[3] = {
}

const int numTests = 3;





// void test_tuner_on_transitions() {
//     //transition 2-3
//     // artificially set variables
//     currState = TUNER_ON;
//     toolChangeButtonPressed = true;

//     // run fsm
//     fsm();

//     // Assert
//     assert(currState == METRONOME_OFF);
//     //can verify display here
    
//     //transition 2-1
//     currState = TUNER_ON;
//     toolChangeButtonPressed = false;
//     onOffButtonPressed = true;

//     // run fsm
//     fsm();

//     // Assert
//     assert(currState == INSTRUMENT_CHANGE);

//     //transition 2-2
//     currState = TUNER_ON;
//     toolChangeButtonPressed = false;
//     onOffButtonPressed = false;

//     // run fsm
//     fsm();

//     // Assert
//     assert(currState == TUNER_ON);

// }

// void test_tuner_off_transitions() {
//     //transition 1-3
//     // artificially set variables
//     currState = INSTRUMENT_CHANGE;
//     toolChangeButtonPressed = true;

//     // run fsm
//     fsm();

//     // Assert
//     assert(currState == METRONOME_OFF);
//     //can verify display here
    
//     //transition 1-2
//     currState = INSTRUMENT_CHANGE;
//     toolChangeButtonPressed = false;
//     onOffButtonPressed = true;

//     // run fsm
//     fsm();

//     // Assert
//     assert(currState == TUNER_ON);

//     //transition 1-1
//     currState = INSTRUMENT_CHANGE;
//     toolChangeButtonPressed = false;
//     onOffButtonPressed = false;

//     // run fsm
//     fsm();

//     // Assert
//     assert(currState == INSTRUMENT_CHANGE);

// }



// void test_tuner_off_transitions() {
//     //transition 1-3
//     // artificially set variables
//     currState = INSTRUMENT_CHANGE;
//     toolChangeButtonPressed = true;

//     // run fsm
//     fsm();

//     // Assert
//     assert(currState == METRONOME_OFF);
//     //can verify display here
    
//     //transition 1-2
//     currState = INSTRUMENT_CHANGE;
//     toolChangeButtonPressed = false;
//     onOffButtonPressed = true;

//     // run fsm
//     fsm();

//     // Assert
//     assert(currState == TUNER_ON);

//     //transition 1-1
//     currState = INSTRUMENT_CHANGE;
//     toolChangeButtonPressed = false;
//     onOffButtonPressed = false;

//     // run fsm
//     fsm();

//     // Assert
//     assert(currState == INSTRUMENT_CHANGE);

// }



// void test_metronome_on_to_note_player_off() {
//     // artificially set variables
//     currState = METRONOME_ON;
//     toolChangeButtonPressed = true;

//     // run fsm
//     fsm();

//     // Assert
//     assert(currState == NOTE_PLAYER_OFF);
    
// }
