#include "arduino_multitool.h" // Replace with the actual header file name


/*
 * A struct to keep state inputs
 */

typedef struct {
  bool mock_upButtonPressed;
  bool mock_downButtonPressed;

} state_inputs;

/*
 * A struct to keep all 9 state variables in one place
 */
typedef struct {
  int test_bpm;
  int test_currNote;
  int test_currTunerNote;
  int test_currInstrument;
  bool test_toolButtonPressed;
  bool test_onOffButtonPressed;
} state_vars;

bool testTransition(fsm_state startState, fsm_state endState, state_inputs testStateInputs, state_vars startStateVars, state_vars endStateVars, bool verbos);
/*
 * Given a start state, inputs, and starting values for state variables, tests that
 * updateFSM returns the correct end state and updates the state variables correctly
 * returns true if this is the case (test passed) and false otherwise (test failed)
 */

bool testTransition(fsm_state startState, fsm_state endState, state_inputs testStateInputs, state_vars startStateVars, state_vars endStateVars, bool verbos) {
  test_bpm = startStateVars.bpm;
  test_currNote = startStateVars.currNote;
  test_currTunerNote = startStateVars.currTunerNote;
  test_currInstrument = startStateVars.currInstrument;
  // test_instruments = startStateVars.instruments these should remain as their global variables
  // test_allNotes = startStateVars.allNotes
  // test_tunerNotes = startStateVars.tunerNotes
  test_toolButtonPressed = startStateVars.toolChangeButtonPressed;
  test_onOffButtonPressed = startStateVars.onOffButtonPressed;
  fsm_state resultState = test_fsm(startState, )
  bool passedTest = (endState == resultState and 
                    test_bpm == endStateVars.bpm and
                    test_currNote = endStateVars.currNote
                    test_currTunerNote = endStateVars.currTunerNote
                    test_currInstrument = endStateVars.currInstrument
                    test_toolButtonPressed = endStateVars.toolChangeButtonPressed
                    test_onOffButtonPressed = endStateVars.onOffButtonPressed);

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





// const state testStatesIn[3] = {
//   (state) 3, (state) 6, (state) 1
// };

// const state testStatesOut[3] = {
//   (state) 3, (state) 6, (state) 1 // No change due to invalid input
// };

// const state_inputs testInputs[3] = {
// }

// const state_vars testVarsIn[3] = {

// }

// const state_vars testVarsOut[3] = {
// }

// const int numTests = 3;





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
