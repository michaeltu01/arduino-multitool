//Tests the changeCurrNoteupward function. Tests normal operation, that it wraps around at the end of the array, and checks edge cases where currNote index would be out of bounds.
void test_changeCurrNoteUpward(){
  //normal operation
  currNote = 0;
  changeCurrNoteUpward();
  assert(currNote == 1);

  //wraparound condition
  currNote = 35;
  changeCurrNoteUpward();
  assert(currNote == 0);

  //case where somehow currNote index gets incremented above max limit
  currNote = 36;
  changeCurrNoteUpward();
  assert(currNote == 0);

  //case where somehow currNote index gets thrown out of bounds
  currNote = -5;
  changeCurrNoteUpward();
  assert(currNote == 0);

  Serial.println("changeCurrNoteUpward tests passed!");
}

//Tests the changeCurrNoteDownward function. Tests normal operation, that it wraps around at the beginning of the array, and checks edge cases where currNote index would be out of bounds.
void test_changeCurrNoteDownward(){
  //normal operation
  currNote = 25;
  changeCurrNoteDownward();
  assert(currNote == 24);

  //wraparound condition
  currNote = 0;
  changeCurrNoteDownward();
  assert(currNote == 35);

  //case where somehow currNote index gets incremented below min limit
  currNote = -1;
  changeCurrNoteDownward();
  assert(currNote == 35);

  //case where somehow currNote index gets thrown out of bounds
  currNote = 100;
  changeCurrNoteDownward();
  assert(currNote == 35);

  Serial.println("changeCurrNoteDownward tests passed!");
}

//Tests the changeBPMUpward method. Tests normal operation, that it stops at the max BPM, and checks edge cases where the bpm is out of bounds. 
void test_changeBPMUpward(){
  //normal operation
  bpm = 60;
  changeBPMUpward();
  assert(bpm == 65);

  //max condition
  bpm = 250;
  changeBPMUpward();
  assert(bpm == 250);

  //out of bounds conditions
  bpm = 300;
  changeBPMUpward();
  assert(bpm == 250);

  bpm = 10;
  changeBPMUpward();
  assert(bpm == 45);

  Serial.println("changeBPMUpward tests passed!");
}

//Tests the changeBPMDownward method. Tests normal operation, that it stops at the min BPM, and checks edge cases where the bpm is out of bounds. 
void test_changeBPMDownward(){
  //normal operation
  bpm = 60;
  changeBPMDownward();
  assert(bpm == 55);

  //min condition
  bpm = 40;
  changeBPMDownward();
  assert(bpm == 40);

  //out of bounds conditions
  bpm = 300;
  changeBPMDownward();
  assert(bpm == 245);

  bpm = 10;
  changeBPMDownward();
  assert(bpm == 40);

  Serial.println("changeBPMDownward tests passed!");
}

//Tests the changeCurrTunerNoteUpward method. Tests normal operation and ensures the array wraps around at the end. Tested both for Guitar and Violin modes. 
void test_changeCurrTunerNoteUpward(){
  //normal operation, Guitar
  currInstrument = 0;
  currTunerNote = 0;
  changeCurrTunerNoteUpward();
  assert(currTunerNote == 1);

  //wraparound condition
  currTunerNote = 5;
  changeCurrTunerNoteUpward();
  assert(currTunerNote == 0);

  //normal operation, Violin
  currInstrument = 1;
  currTunerNote = 0;
  changeCurrTunerNoteUpward();
  assert(currTunerNote == 1);

  //wraparound condition
  currTunerNote = 3;
  changeCurrTunerNoteUpward();
  assert(currTunerNote == 0);

  Serial.println("changeCurrTunerNoteUpward tests passed!");
}

//Tests the changeCurrTunerNoteDownward method. Tests normal operation and ensures the array wraps around at the beginning. Tested both for Guitar and Violin modes. 
void test_changeCurrTunerNoteDownward(){
  //normal operation, Guitar
  currInstrument = 0;
  currNote = 5;
  changeCurrTunerNoteDownward();
  assert(currNote == 4);

  //wraparound condition
  currNote = 0;
  changeCurrTunerNoteDownward();
  assert(currNote == 5);

  //normal operation, Violin
  currInstrument = 1;
  currNote = 3;
  changeCurrTunerNoteDownward();
  assert(currNote == 2);

  //wraparound condition
  currNote = 0;
  changeCurrTunerNoteDownward();
  assert(currNote == 3);

  Serial.println("changeCurrTunerNoteDownward tests passed!");
}

//Tests the changeCurrInstrumentUpward method. Tests normal operation and that the instrument index wraps around at the end.
void test_changeCurrInstrumentUpward(){
  //normal operation
  currInstrument = 0;
  changeCurrInstrumentUpward();
  assert(currInstrument == 1);

  //wraparound
  currInstrument = 1;
  changeCurrInstrumentUpward();
  assert(currInstrument == 0);

  Serial.println("changeCurrInstrumentUpward tests passed!");
}

//Tests the changeCurrInstrumentDownward method. Tests normal operation and that the instrument index wraps around at the beginning.
void test_changeCurrInstrumentDownward(){
  //normal operation
  currInstrument = 1;
  changeCurrInstrumentDownward();
  assert(currInstrument == 0);

  //wraparound
  currInstrument = 0;
  changeCurrInstrumentDownward();
  assert(currInstrument == 1);

  Serial.println("changeCurrInstrumentDownward tests passed!");
}

//Tests the onOffButtonISR method. This method should change the onOffButtonPressed variable to true. 
void test_onOffButtonISR(){
  onOffButtonPressed = false;
  onOffButtonISR();
  assert(onOffButtonPressed = true);

  Serial.println("onOffButtonISR test passed!");
}

//Tests the toolChangeButtonISR method. This method should change the toolChangeButtonPressed variable to true. 
void test_toolChangeButtonISR(){
  toolChangeButtonPressed = false;
  toolChangeButtonISR();
  assert(toolChangeButtonPressed = true);

  Serial.println("toolChangeButtonPressed test passed!");
}

//runs all tests in the unit test suite
void all_tests(){
  test_changeCurrNoteUpward();
  test_changeCurrNoteDownward();
  test_changeBPMUpward();
  test_changeBPMDownward();
  test_changeCurrTunerNoteUpward();
  test_changeCurrInstrumentUpward();
  test_changeCurrInstrumentDownward();
  test_onOffButtonISR();
  test_toolChangeButtonISR();
  Serial.println("All Tests Passed!");
}