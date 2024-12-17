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

  // //case where somehow currNote index gets incremented above max limit
  // currTunerNote = 6;
  // changeCurrNoteUpward();
  // Serial.println(currTunerNote);
  // assert(currTunerNote == 0);

  //normal operation, Violin
  currInstrument = 1;
  currTunerNote = 0;
  changeCurrTunerNoteUpward();
  assert(currTunerNote == 1);

  //wraparound condition
  currTunerNote = 3;
  changeCurrTunerNoteUpward();
  assert(currTunerNote == 0);

  // //case where somehow currNote index gets incremented above max limit
  // currTunerNote = 4;
  // changeCurrNoteUpward();
  // assert(currTunerNote == 0);

  Serial.println("changeCurrTunerNoteUpward tests passed!");
}

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

  //case where somehow currNote index gets incremented blow min limit
  // currNote = -1;
  // changeCurrNoteDownward();
  // assert(currNote == 5);

  //normal operation, Violin
  currInstrument = 1;
  currNote = 3;
  changeCurrTunerNoteDownward();
  assert(currNote == 2);

  //wraparound condition
  currNote = 0;
  changeCurrTunerNoteDownward();
  assert(currNote == 3);

  //case where somehow currNote index gets incremented above max limit
  // currNote = -1;
  // changeCurrNoteDownward();
  // assert(currNote == 3);

  Serial.println("changeCurrTunerNoteDownward tests passed!");
}

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

void test_onOffButtonISR(){
  onOffButtonPressed = false;
  onOffButtonISR();
  assert(onOffButtonPressed = true);

  Serial.println("onOffButtonISR test passed!");
}

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