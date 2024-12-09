void micReceiverSetup() {
  //Serial.begin(9600);  // Match baud rate
}

void micReceiverLoop() {
  if (Serial.available()) {
    // Read incoming frequency
    String freqString = Serial.readStringUntil('\n');
    float frequency = freqString.toFloat();
    
    // Process or display frequency
    // Examples:
    // - Light up LEDs based on frequency range
    // - Control motor speed
    // - Trigger other actions
  }
}