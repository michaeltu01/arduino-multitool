// // Enum for defining states
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

// // Global variables for state management
// MetronomeState currentState = IDLE;
// int bpm = 0;
// String[] instruments = ["GUITAR", "VIOLIN"];
// String[][] notes = [["C3", "D3", "E3", "F3", "G3"], ["C3", "D3"]]

// // Button state tracking
// bool downButtonPressed = false;
// bool upButtonPressed = false;
// bool onOffButtonPressed = false;
// bool toolChangeButtonPressed = false;

// const int instrumentButtonPin = 4;
// const int noteButtonPin = 2;
// const int onOffButtonPin = 3;
// const int toolChangeButtonPin = 5;

// // Debounce variables
// unsigned long lastDebounceTime = 0;
// unsigned long debounceDelay = 50; // 50ms debounce time

// void checkButtons() {
//   unsigned long currentTime = millis();
  
//   // Reset button pressed states
//   downButtonPressed = false;
//   upButtonPressed = false;
//   onOffButtonPressed = false;
//   toolChangeButtonPressed = false;
  
//   // Instrument Button
//   if (digitalRead(instrumentButtonPin) == LOW) {
//     if ((currentTime - lastDebounceTime) > debounceDelay) {
//       instrumentButtonPressed = true;
//       lastDebounceTime = currentTime;
//     }
//   }
  
//   // Note Button
//   if (digitalRead(noteButtonPin) == LOW) {
//     if ((currentTime - lastDebounceTime) > debounceDelay) {
//       noteButtonPressed = true;
//       lastDebounceTime = currentTime;
//     }
//   }
  
//   // On/Off Button
//   if (digitalRead(onOffButtonPin) == LOW) {
//     if ((currentTime - lastDebounceTime) > debounceDelay) {
//       onOffButtonPressed = true;
//       lastDebounceTime = currentTime;
//     }
//   }
// }

// void setup() {
//   // Set up button pins with internal pull-up resistors
//   pinMode(instrumentButtonPin, INPUT);
//   pinMode(noteButtonPin, INPUT);
//   pinMode(onOffButtonPin, INPUT);
// }



// void handleInstrumentButton() {
//   switch(currentTool) {
//     case NOTE_PLAYER:
//       // Change instrument
//       break;
//     case TUNER:
//       // Potentially different behavior
//       break;
//   }
// }

// void handleNoteButton() {
//   switch(currentTool) {
//     case NOTE_PLAYER:
//       // Change note or mode
//       break;
//     case TUNER:
//       // Potentially different behavior
//       break;
//   }
// }

// void handleOnOffButton() {
//   // Toggle power or switch between tools
//   switch(currentTool) {
//     case METRONOME:
//       // Turn metronome on/off
//       break;
//     case NOTE_PLAYER:
//       // Turn note player on/off
//       break;
//     case TUNER:
//       // Turn tuner on/off
//       break;
//   }
// }

// String cyclePitch() {
//   volatile pitchIdx = 0;
//   return notes[++pitchIdx]; // return the pitch at pitchIdx + increment the index
// }

// String cycleInstrument() {
//   volatile instrumentIdx = 0;
//   return notes[++instrumentIdx];  // return the instrument at instrumentIdx + increment the index
// }

// void fsm() {
//   checkButtons();

//   switch(currentState) {
//     case OFF_STATE:
//       if (onOffButtonPressed) {  // Transition 0-1
//         currentState = PLAYING;
//         upButtonPressed = false;
//       }
//       break;
    
//     case NOTE_PLAYER:
//       if (upButtonPressed) {  // Transition 5-5(a)
//         cyclePitch();
//         upButtonPressed = false;
//       }
//       if (downButtonPressed) {  // Transition 5-5(b)
//         cycleInstrument();
//         downButtonPressed = false;
//       }

//     case METRONOME:
//       // While playing, you can adjust tempo
//       if (upButtonPressed) {  // Transition 3-3(a) -- shouldn't this transition just be the upButtonISR?
//         bpm = min(bpm + 5, maxBPM);
//         upButtonPressed = false;
//       }
//       if (downButtonPressed) {  // Transition 3-3(b) -- shouldn't this transition just be the downButtonISR?
//         bpm = max(bpm - 5, minBPM);
//         downButtonPressed = false;
//       }
//       break;

//     case TUNER:
//       // Dedicated tempo adjustment state (optional)
//       if (upButtonPressed) {  // Transition 1-1(a)
//         cyclePitch();
//         upButtonPressed = false;
//       }
//       if (downButtonPressed) {  // Transition 1-1(b)
//         cycleInstrument();
//         downButtonPressed = false;
//       }
//       break;
//   }
// }

// void setup() {
//   pinMode(upButtonPin, INPUT_PULLUP);
//   pinMode(downButtonPin, INPUT_PULLUP);
//   pinMode(buzzerPin, OUTPUT);
// }

// void loop() {
//   fsm();
//   // Other metronome logic like beat generation would go here
// }