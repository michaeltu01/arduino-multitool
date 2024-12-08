// Enum for defining states
// enum TOOL_STATE {
//   METRONOME,
//   TUNER,
//   NOTE_PLAYER,
//   OFF_STATE
// };

// // Enum for defining instruments
// enum INSTRUMENTS {
//   GUITAR,
//   VIOLIN,
// }

// enum NOTE {
//   C3,
//   D3,
//   E3,
//   F3,
//   G3,
//   A3,
//   B3,
//   C4,
// }

String[] notes = {'C3', 'D3', 'E3', 'F3', 'G3', 'A3', 'B3', 'C4'};
String[] instruments = {'GUITAR', 'VIOLIN');
// String[] tools = {'METRONOME','TUNER','NOTE_PLAYER'};
//'METRONOME_OFF','NOTE_PLAYER_OFF','TUNER_OFF'
int currNote = 0; //index of the note in array
int currInstrument = 0; //index of the instrument in array
// int curr = 0; //index of the tool in array
int lengthofNoteArray = sizeof(notesArray) / sizeof(notesArray[0]);
int lengthofInstrumentArray = sizeof(instrumentsArray) / sizeof(instrumentsArray[0]);
// int lengthofToolArray = sizeof(toolArray) / sizeof(toolArray[0]);


// Global variables for state management
int currentState = 1; //curr state
int bpm = 0;

// Button state tracking
bool downButtonPressed = false;
bool upButtonPressed = false;
bool onOffButtonPressed = false;
bool toolChangeButtonPressed = false;

const int instrumentButtonPin = 4;
const int noteButtonPin = 2;
const int onOffButtonPin = 3;
const int toolChangeButtonPin = 5;

// Debounce variables
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // 50ms debounce time

void checkButtons() {
  unsigned long currentTime = millis();
  
  // Reset button pressed states
  downButtonPressed = false; 
  upButtonPressed = false;
  onOffButtonPressed = false;
  toolChangeButtonPressed = false;
  
  // Instrument Button
  if (digitalRead(downButtonPressed) == LOW) {
    if ((currentTime - lastDebounceTime) > debounceDelay) {
      downButtonPressed = true;
      lastDebounceTime = currentTime;
    }
  }
  
  // Note Button
  if (digitalRead(upButtonPressed) == LOW) {
    if ((currentTime - lastDebounceTime) > debounceDelay) {
      upButtonPressed = true;
      lastDebounceTime = currentTime;
    }
  }
  
  // On/Off Button
  if (digitalRead(onOffButtonPin) == LOW) {
    if ((currentTime - lastDebounceTime) > debounceDelay) {
      onOffButtonPressed = true;
      lastDebounceTime = currentTime;
    }
  }

  // toolChangeButton pressed
  if (digitalRead(toolChangeButtonPressed) == LOW) {
    if ((currentTime - lastDebounceTime) > debounceDelay) {
      toolChangeButtonPressed = true;
      lastDebounceTime = currentTime;
    }
  }
}

void setup() {
  // Set up button pins with internal pull-up resistors
  pinMode(instrumentButtonPin, INPUT);
  pinMode(noteButtonPin, INPUT);
  pinMode(onOffButtonPin, INPUT);
  pinMode(toolChangeButtonPressed, INPUT);
  buttonSetup();
}


void changeCurrNoteUpward() {
  currNote += 1;
  currNote = currNote % (lengthofNoteArray);
  // return notes[currNote];
}

void changeCurrNoteDownward() {
  currNote -= 1;
  currNote = currNote % (lengthofNoteArray);
  // return notes[currNote];
}

void changeCurrInstrumentUpward() {
  currInstrument += 1;
  currInstrument = currInstrument % (lengthofInstrumentArray);
  // return instruments[currInstrument];
}

void changeCurrInstrumentDownward() {
  currInstrument -= 1;
  currInstrument = currInstrument % (lengthofInstrumentArray);
  // return instruments[currInstrument];
}



void fsm() {
  checkButtons();

  switch() {
    
    case 4:
      if (upButtonPressed) {  // Transition 5-5(a)
        cyclePitch(); //TODO CAHNGE
        upButtonPressed = false;
      }
      if (downButtonPressed) {  // Transition 5-5(b)
        cycleInstrument();
        downButtonPressed = false;
      }

    case 2:
      // While playing, you can adjust tempo
      if (upButtonPressed) {  // Transition 3-3(a) -- shouldn't this transition just be the upButtonISR?
        bpm = min(bpm + 5, maxBPM);
        upButtonPressed = false;
      }
      if (downButtonPressed) {  // Transition 3-3(b) -- shouldn't this transition just be the downButtonISR?
        bpm = max(bpm - 5, minBPM);
        downButtonPressed = false;
      }
      break;

    case 1:
      // Dedicated tempo adjustment state (optional)
      if (upButtonPressed) {  // Transition 1-1(a)
        cyclePitch();
        upButtonPressed = false;
      }
      if (downButtonPressed) {  // Transition 1-1(b)
        cycleInstrument();
        downButtonPressed = false;
      }
      break;
  }
}


void loop() {
  fsm();
  // Other metronome logic like beat generation would go here
}