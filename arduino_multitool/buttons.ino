
void buttonSetup() {
  attachInterrupt(digitalPinToInterrupt(upButtonPin), upButtonISR, RISING);
  attachInterrupt(digitalPinToInterrupt(downButtonPin), downButtonISR, RISING);
  attachInterrupt(digitalPinToInterrupt(onOffButtonPin), onOffButtonISR, RISING);
  attachInterrupt(digitalPinToInterrupt(toolChangeButtonPin), toolChangeButtonISR, RISING);
}

//tuner toggles between an instrument changing state and an actual tuning state 
//1 is tuner state 
//0 is instrument changing
//2 is metronome state
//3 metronome off
//4 is note playing state
//5 is note playing off state

void upButtonISR(){
  switch(currentState) {
    case 0: //tuner 'off', change instrument 'upward'
      changeCurrInstrumentUpward();
      break;
    case 1: //tuner on, change note 'upward'
      changeCurrNoteUpward();
      break;
    case 2: //metronome on
      if(bpm + 5 <= maxBPM){
        bpm += 5;
      }
      displayMetronome(true, bpm);
      break;
    case 3: //metronome off
      
      break;
    case 4://is note playing state
      changeCurrNoteUpward();
      break;
    case 5://is note playing state off
      break;
  }
}

void downButtonISR(){
  switch(currentState) {
    case 0: //tuner 'off', change instrument 'downward'
      changeCurrInstrumentDownward();
      break;
    case 1: //tuner on, change note 'downward'
      changeCurrNoteDownward();
      break;
    case 2: //metronome on
      if(bpm - 5 >= minBPM){
        bpm -= 5;
      }
      displayMetronome(true, bpm);
      break;
    case 3: //metronome off
      
      break;
    case 4://is note playing state
      changeCurrNoteDownward();
      break;
    case 5://is note playing state off
      break;
    
  }
}

void onOffButtonISR(){
  // switch(currentState) {
  //   case 0: //tuner 'off', change to tuner on
  //     currentState = 1;
  //     break;
  //   case 1: //tuner on, change to off
  //     currentState = 0;
  //     break;
  //   case 2: //metronome on
  //     currentState = 3;
  //     break;
  //   case 3: //metronome off
  //     currentState = 2;
  //     break;
  //   case 4://is note playing state
  //     currentState = 5;
  //     break;
  //   case 5://is note playing state off
  //     currentState = 4;
  //     break;
  // }
}

void toolChangeButtonISR(){
  // switch(currentState) {
  //   case 0: //tuner 'off', change to NP
  //     currentState = 5;
  //     break;
  //   case 1: //tuner on, change to off
  //     currentState = 5;
  //     break;
  //   case 2: //metronome on change to tuner off
  //     currentState = 0;
  //     break;
  //   case 3: //metronome off
  //     currentState = 0;
  //     break;
  //   case 4://is note playing state change to metro
  //     currentState = 3;
  //     break;
  //   case 5://is note playing state off
  //     currentState = 3;
  //     break;
  // }
}

