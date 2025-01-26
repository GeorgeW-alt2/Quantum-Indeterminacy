#include "pitches.h"

// Pins
const int LDR_PIN = A0;
const int DELAY_TIME_PIN = A4;
const int DIRECT_ADC_PIN = A1;
const int DELAYED_ADC_PIN = A2;
const int BUZZER_PIN = 9;
const int RELAY_PIN = 12;

// Parameters
float delayLine[200];
int writeIndex = 0;
int maxDelaySamples = 50;
int threshold = 512;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  for(int i = 0; i < 200; i++) delayLine[i] = 0;
}

void loop() {
  // Read inputs
  int ldrValue = analogRead(LDR_PIN);
  int delayTime = map(analogRead(DELAY_TIME_PIN), 0, 1023, 1, 300);
  maxDelaySamples = delayTime / 2;

  // Process delay line
  float delayedValue = delayLine[writeIndex];
  delayLine[writeIndex] = ldrValue;
  writeIndex = (writeIndex + 1) % maxDelaySamples;

  // Convert to digital
  int directDigital = ldrValue > threshold ? 1 : 0;
  int delayedDigital = delayedValue > threshold ? 1 : 0;

  // Compare states
  if(directDigital != delayedDigital) {
    tone(BUZZER_PIN, NOTE_C4, 10);
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    noTone(BUZZER_PIN);
    digitalWrite(RELAY_PIN, LOW);
  }

  Serial.print(ldrValue);
  Serial.print(",");
  Serial.println(delayedValue);
  delay(1);
}