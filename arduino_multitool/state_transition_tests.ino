/* Function that takes in a fsm_state enum and prints a more informative and 
  accurate message about the state it is affiliated with
* Input: fsm state that you want to print
* Need this because enums don't print a string
*/
void checkState(fsm_state s) {
  switch(s) {
    case TUNER_ON:
      Serial.println("(1) TUNER_ON");
      break;
    case INSTRUMENT_CHANGE:
      Serial.println("(2) INSTRUMENT_CHANGE");
      break;
    case METRONOME_ON:
      Serial.println("(3) METRONOME_ON");
      break;
    case METRONOME_OFF:
      Serial.println("(4) METRONOME_OFF");
      break;
    case NOTE_PLAYER_ON:
      Serial.println("(5) METRONOME_OFF");
      break;
    case NOTE_PLAYER_OFF:
      Serial.println("(6) NOTE_PLAYER_OFF");
      break;
    default:
      Serial.println("??");
      break;
  }
}

/* Function with tests for testing all FSM state transitions excluding self-transitions
*
* Calls updateGlobalVariablesForTesting() and checkGlobalVariablesForTesting() helper methods
*/
void test_fsm() { //COMMENT OUT fsm() in loop in arduino_multitool
    //transition 1-2

    // artificially set variables using updateGlobalVariablesForTesting()
    updateGlobalVariablesForTesting(TUNER_ON, 0, 0, 0, 100, false, true);
    // run fsm
    fsm();
    // Assert
    checkGlobalVariablesForTesting(INSTRUMENT_CHANGE,0, 0, 0, 100, false, false);
    
    
    //transition 1-3
    updateGlobalVariablesForTesting(TUNER_ON, 0, 0, 0, 100, true, false);
    // run fsm
    fsm();
    // Assert
    checkGlobalVariablesForTesting(METRONOME_OFF,0, 0, 0, 100, false, false);

    //transition 2-3

    updateGlobalVariablesForTesting(INSTRUMENT_CHANGE, 0, 0, 0, 100, true, false);
    // run fsm
    fsm();
    // Assert
    checkGlobalVariablesForTesting(METRONOME_OFF,0, 0, 0, 100, false, false);

    //transition 2-1

    updateGlobalVariablesForTesting(INSTRUMENT_CHANGE, 0, 0, 0, 100, false, true);
    // run fsm
    fsm();
    // Assert
    checkGlobalVariablesForTesting(TUNER_ON,0, 0, 0, 100, false, false);

    //transition 3-4

    updateGlobalVariablesForTesting(METRONOME_OFF, 0, 0, 0, 100, false, true);
    // run fsm
    fsm();
    // Assert
    checkGlobalVariablesForTesting(METRONOME_ON,0, 0, 0, 100, false, false);

    //transition 3-5

    updateGlobalVariablesForTesting(METRONOME_OFF, 0, 0, 0, 100, true, false);
    // run fsm
    fsm();
    // Assert
    checkGlobalVariablesForTesting(NOTE_PLAYER_OFF,0, 0, 0, 100, false, false);

    //transition 4-3

    updateGlobalVariablesForTesting(METRONOME_ON, 0, 0, 0, 100, false, true);
    // run fsm
    fsm();
    // Assert
    checkGlobalVariablesForTesting(METRONOME_OFF,0, 0, 0, 100, false, false);

    //transition 4-5

    updateGlobalVariablesForTesting(METRONOME_ON, 0, 0, 0, 100, true, false);
    // run fsm
    fsm();
    // Assert
    checkGlobalVariablesForTesting(NOTE_PLAYER_OFF,0, 0, 0, 100, false, false);

    //transition 5-1

    updateGlobalVariablesForTesting(NOTE_PLAYER_OFF, 0, 0, 0, 100, true, false);
    // run fsm
    fsm();
    // Assert
    checkGlobalVariablesForTesting(TUNER_ON,0, 0, 0, 100, false, false);

    //transition 5-6

    updateGlobalVariablesForTesting(NOTE_PLAYER_OFF, 0, 0, 0, 100, false, true);
    // run fsm
    fsm();
    // Assert
    checkGlobalVariablesForTesting(NOTE_PLAYER_ON,0, 0, 0, 100, false, false);

    //transition 6-1

    updateGlobalVariablesForTesting(NOTE_PLAYER_ON, 0, 0, 0, 100, true, false);
    // run fsm
    fsm();
    // Assert
    checkGlobalVariablesForTesting(TUNER_ON,0, 0, 0, 100, false, false);

    //transition 6-5

    updateGlobalVariablesForTesting(NOTE_PLAYER_ON, 0, 0, 0, 100, false, true);
    // run fsm
    fsm();
    // Assert
    checkGlobalVariablesForTesting(NOTE_PLAYER_OFF,0, 0, 0, 100, false, false);

    Serial.println("FSM Transition Tests Passed!");
}

/* 
* Helper method that updates all global variables to desired starting state values
* Input: current state, current note, tuner note, current instrument, bpm, bool for if 
tool button is pressed, bool for if on/off button is pressed
* Output: updates all respective global variables to the input values
*/
void updateGlobalVariablesForTesting(
    fsm_state test_currState, 
    int test_currNote, int test_currTunerNote, 
    int test_currInstrument, 
    int test_bpm, 
    bool test_toolButtonPressed, 
    bool test_onOffButtonPressed) {
  currState = test_currState;
  currNote = test_currNote;
  currTunerNote = test_currTunerNote;
  currInstrument = test_currInstrument;
  bpm = test_bpm;
  toolChangeButtonPressed = test_toolButtonPressed;
  onOffButtonPressed = test_onOffButtonPressed;
  
}

/* 
* Helper method that checks if all global variables 
  are as expected after the fsm function is called
* Input: current state, current note, tuner note, 
  current instrument, bpm, bool for if tool button 
  is pressed, bool for if on/off button is pressed
* Output: checks/asserts if the fsm state transition 
  updated the state and variables as expected. If 
  not, the function prints informatively
*/
void checkGlobalVariablesForTesting(
    fsm_state test_currState, 
    int test_currNote, 
    int test_currTunerNote, 
    int test_currInstrument, 
    int test_bpm, 
    bool test_toolButtonPressed, 
    bool test_onOffButtonPressed) {
  
  // Check currState
  if (currState != test_currState) {
    Serial.print("ERROR: currState mismatch! Expected: ");
    checkState(test_currState);
    Serial.print(", Found: ");
    checkState(currState);
  }

  // Check currNote
  if (currNote != test_currNote) {
    Serial.print("ERROR: currNote mismatch! Expected: ");
    Serial.print(test_currNote);
    Serial.print(", Found: ");
    Serial.println(currNote);
  }

  // Check currTunerNote
  if (currTunerNote != test_currTunerNote) {
    Serial.print("ERROR: currTunerNote mismatch! Expected: ");
    Serial.print(test_currTunerNote);
    Serial.print(", Found: ");
    Serial.println(currTunerNote);
  }

  // Check currInstrument
  if (currInstrument != test_currInstrument) {
    Serial.print("ERROR: currInstrument mismatch! Expected: ");
    Serial.print(test_currInstrument);
    Serial.print(", Found: ");
    Serial.println(currInstrument);
  }

  // Check bpm
  if (bpm != test_bpm) {
    Serial.print("ERROR: bpm mismatch! Expected: ");
    Serial.print(test_bpm);
    Serial.print(", Found: ");
    Serial.println(bpm);
  }

  // Check toolChangeButtonPressed
  if (toolChangeButtonPressed != test_toolButtonPressed) {
    Serial.print("ERROR: toolChangeButtonPressed mismatch! Expected: ");
    Serial.print(test_toolButtonPressed);
    Serial.print(", Found: ");
    Serial.println(toolChangeButtonPressed);
  }

  // Check onOffButtonPressed
  if (onOffButtonPressed != test_onOffButtonPressed) {
    Serial.print("ERROR: onOffButtonPressed mismatch! Expected: ");
    Serial.print(test_onOffButtonPressed);
    Serial.print(", Found: ");
    Serial.println(onOffButtonPressed);
  }

  // assert statements for further checking rigor
  assert(currState == test_currState);
  assert(currNote == test_currNote);
  assert(currTunerNote == test_currTunerNote);
  assert(currInstrument == test_currInstrument);
  assert(bpm == test_bpm);
  assert(toolChangeButtonPressed == test_toolButtonPressed);
  assert(onOffButtonPressed == test_onOffButtonPressed);


}


