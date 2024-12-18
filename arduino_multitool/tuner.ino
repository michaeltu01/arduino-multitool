/* 

  tuner.ino

  Main file for tuner mode.

*/

/*
  Initialization of anything the tuner needs (the Serial port).
  Input: None
  Output: None
*/
void tunerSetup() {
  Serial.begin(9600);
  Serial.setTimeout(1000);
}

/*
  Function to get the pitch being fed into the Serial port by the Python script
  Input: 
    freq: a number representing the current heard frequency
    pitchName: a pointer to a string representing the name of the heard pitch
  Output: None
*/
void getPitch(double* freq, String* pitchName) {
  // while(!Serial.available());

  // Read in the input line
  String input = Serial.readStringUntil('\n');

  // Parse the input
  int commaIdx = input.indexOf(',');
  String freqStr = input.substring(0, commaIdx);
  String pitchStr = input.substring(commaIdx + 1, input.length() - 1);

  // Copy to input parameters
  *freq = freqStr.toDouble();
  *pitchName = pitchStr;

  // Echo back the received values
  // Serial.print(freqStr);
  // Serial.print(",");
  // Serial.println(*pitchName);
}

/*
  Function to compute where to render the accuracy bar for the tuner display.
  Inputs:
    curNote: the note currently being heard
    targetNote: the note that the user is trying to 'hit'
  Output: a number between 0 and 15 representing the accuracy
*/
int computeAccuracy(struct Note curNote, struct Note targetNote) {
  int acc = max(0, min(15, round(7 + ((curNote.freq - targetNote.freq) / targetNote.freq) * 15)));
  return acc;
}

/*
  The loop for main tuner functionality.
  Inputs: None
  Output: None
*/
void tunerLoop() {
  double freq;
  String pitchName;

  if (Serial.available()) {
    // Read the pitch from Serial
    getPitch(&freq, &pitchName);

    // Create the current Note object
    struct Note inputNote;
    inputNote.name = pitchName;
    inputNote.freq = freq;

    // Compare the current Note with the target Note
    // struct Note targetNote = curNote;  // whatever the current Note is
    struct Note targetNote = tunerNotes[currInstrument][currTunerNote];

    int acc = computeAccuracy(inputNote, targetNote);
    // Serial.println(acc);

    // Display on the tuner
    displayTuner(true, acc, tunerNotes[currInstrument][currTunerNote]);
  }

  // Pet WDT
  petWDT();
}