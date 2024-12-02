const int buzzerPin = 4;
const int upButtonPin = 2;
const int downButtonPin = 3;

int bpm = 60;
const int buzzerLength = 50;
const int minBPM = 40;
const int maxBPM = 250;

void metronomeSetup() {
  Serial.begin(9600);
  pinMode(upButtonPin, INPUT);
  pinMode(downButtonPin, INPUT);
  pinMode(buzzerPin, OUTPUT); //pin 4 is output
  attachInterrupt(digitalPinToInterrupt(upButtonPin), upButtonISR, RISING);
  attachInterrupt(digitalPinToInterrupt(downButtonPin), downButtonISR, RISING);
  Serial.print("Current BPM: " + String(bpm));
}

void metronomeLoop() {
  digitalWrite(buzzerPin, HIGH);
  delay(buzzerLength);
  digitalWrite(buzzerPin, LOW);
  delay(60000/bpm - buzzerLength); //buzz at a certain bpm
  Serial.println("Current BPM: " + String(bpm));
}

void upButtonISR(){
  if(bpm + 5 <= maxBPM){
    bpm += 5;
  }
}

void downButtonISR(){
  if(bpm - 5 >= minBPM){
    bpm -= 5;
  }
}

