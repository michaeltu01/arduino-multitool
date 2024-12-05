#include "arduinoFFT.h"

#define SAMPLES 128
#define SAMPLING_FREQUENCY 2048
#define MIC_PIN A0

unsigned int samplingPeriod;
unsigned long microSeconds;
double vReal[SAMPLES];
double vImag[SAMPLES];

int micVolume = 0;

ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

void micTestSetup() {
  Serial.begin(9600);
  // samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY));
}

double testMicFrequency() {
  // Sample audio signal
  for(int i=0; i<SAMPLES; i++) {
    microSeconds = micros();
    
    vReal[i] = analogRead(MIC_PIN);
    vImag[i] = 0;

    while(micros() < (microSeconds + samplingPeriod)) {
      // Wait to maintain sampling rate
    }
  }

  // Perform FFT
  FFT.windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.complexToMagnitude(vReal, vImag, SAMPLES);

  // Find peak frequency
  double peakFrequency = FFT.majorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
  
  // Print results
  Serial.print("Peak Frequency: ");
  Serial.print(peakFrequency);
  Serial.println(" Hz");

  return peakFrequency;
}

void micTestLoop() {
  // double peakFrequency = testMicFrequency();
  micVolume = analogRead(MIC_PIN);

  // delay(500); // Sampling interval
  Serial.println(micVolume);
  delay(5);
}