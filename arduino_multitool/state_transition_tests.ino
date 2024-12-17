void test_tuner_on_transitions() {
    //transition 2-3
    // artificially set variables
    currState = TUNER_ON;
    toolChangeButtonPressed = true;

    // run fsm
    fsm();

    // Assert
    assert(currState == METRONOME_OFF);
    //can verify display here
    
    //transition 2-1
    currState = TUNER_ON;
    toolChangeButtonPressed = false;
    onOffButtonPressed = true;

    // run fsm
    fsm();

    // Assert
    assert(currState == INSTRUMENT_CHANGE);

    //transition 2-2
    currState = TUNER_ON;
    toolChangeButtonPressed = false;
    onOffButtonPressed = false;

    // run fsm
    fsm();

    // Assert
    assert(currState == TUNER_ON);

}

void test_tuner_off_transitions() {
    //transition 1-3
    // artificially set variables
    currState = INSTRUMENT_CHANGE;
    toolChangeButtonPressed = true;

    // run fsm
    fsm();

    // Assert
    assert(currState == METRONOME_OFF);
    //can verify display here
    
    //transition 1-2
    currState = INSTRUMENT_CHANGE;
    toolChangeButtonPressed = false;
    onOffButtonPressed = true;

    // run fsm
    fsm();

    // Assert
    assert(currState == TUNER_ON);

    //transition 1-1
    currState = INSTRUMENT_CHANGE;
    toolChangeButtonPressed = false;
    onOffButtonPressed = false;

    // run fsm
    fsm();

    // Assert
    assert(currState == INSTRUMENT_CHANGE);

}



void test_tuner_off_transitions() {
    //transition 1-3
    // artificially set variables
    currState = INSTRUMENT_CHANGE;
    toolChangeButtonPressed = true;

    // run fsm
    fsm();

    // Assert
    assert(currState == METRONOME_OFF);
    //can verify display here
    
    //transition 1-2
    currState = INSTRUMENT_CHANGE;
    toolChangeButtonPressed = false;
    onOffButtonPressed = true;

    // run fsm
    fsm();

    // Assert
    assert(currState == TUNER_ON);

    //transition 1-1
    currState = INSTRUMENT_CHANGE;
    toolChangeButtonPressed = false;
    onOffButtonPressed = false;

    // run fsm
    fsm();

    // Assert
    assert(currState == INSTRUMENT_CHANGE);

}



void test_metronome_on_to_note_player_off() {
    // artificially set variables
    currState = METRONOME_ON;
    toolChangeButtonPressed = true;

    // run fsm
    fsm();

    // Assert
    assert(currState == NOTE_PLAYER_OFF);
    
}
