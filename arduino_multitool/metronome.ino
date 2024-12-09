const int buzzerPin = 13;
const int upButtonPin = 12;
const int downButtonPin = 11;

int bpm = 60;
const int buzzerLength = 50;
const int minBPM = 40;
const int maxBPM = 250;

void metronomeSetup() {
  Serial.begin(9600);
  //inputs are done in setup
  // pinMode(upButtonPin, INPUT);
  // pinMode(downButtonPin, INPUT);
  pinMode(buzzerPin, OUTPUT); //pin 4 is output
  // displayMetronome(true, bpm);
  Serial.print("Current BPM: " + String(bpm));
}

void metronomeLoop() {
  tone(buzzerPin, 440);
  delay(buzzerLength);
  noTone(buzzerPin);
  delay(60000/bpm - buzzerLength); //buzz at a certain bpm
  Serial.println("Current BPM: " + String(bpm));
}

