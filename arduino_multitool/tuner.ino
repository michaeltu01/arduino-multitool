/* 

  tuner.ino

  Main file for tuner mode.

*/


void tunerSetup() {
  Serial.begin(9600);
  Serial.setTimeout(1000);
}

// Get the pitch from Serial port
void getPitch(double* freq, String* pitchName) {
  while(!Serial.available());

  // Read in the input line
  String input = Serial.readStringUntil('\n');

  // Parse the input
  int commaIdx = input.indexOf(',');
  String freqStr = input.substring(0, commaIdx);
  String pitchStr = input.substring(commaIdx + 1, input.length() - 1);

  // Copy to input parameters
  *freq = freqStr.toDouble();
  *pitchName = pitchStr;
  //strcpy(pitchName, pitchStr.c_str());

  // Echo back the received values
  // Serial.print(freqStr);
  // Serial.print(",");
  // Serial.println(*pitchName);
}

int computeAccuracy(struct Note curNote, struct Note targetNote) {
  // int acc = max(0, min(15, 7 + (int)(freqDiff / max(abs(freqDiff), 1) * 7.5)));
  int acc = max(0, min(15, 7 + (int)((curNote.freq - targetNote.freq) / targetNote.freq) * 40));
  return acc;
}

void tunerLoop() {
  double freq;
  String pitchName;

  // Read the pitch from Serial
  getPitch(&freq, &pitchName);

  // Create the current Note object
  struct Note inputNote;
  //strncpy(curNote.name, pitchName, sizeof(curNote.name) - 1);
  inputNote.name = pitchName;
  inputNote.freq = freq;

  // Compare the current Note with the target Note
  // struct Note targetNote = curNote;  // whatever the current Note is
  struct Note targetNote = tunerNotes[currInstrument][currNote];

  int acc = computeAccuracy(inputNote, targetNote);
  //Serial.println(acc);

  // Display on the tuner
  displayTuner(true, acc, tunerNotes[currInstrument][currNote]);

  // Pet WDT
  petWDT();
}