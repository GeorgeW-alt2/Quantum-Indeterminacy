#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

const int checkPin = 10;
const int delayTimePin = A4;    // Potentiometer for delay time
const int LDR = A0;
const int delayedOutputPin = A3;
const int buzzerPin = 9;     // Digital output pin for inverter

const int powerPin = 12;     // Digital output pin for inverter

float delayLine[200];          // Maximum delay line size
int writeIndex = 0;              // Write index for delay line
int maxDelaySamples = 50;     // Max delay samples
int sampleRate = 50;          // Default sample rate
int delayTime = 1;             // Default delay time in milliseconds
int value = 15;

unsigned long unequalStartTime = 0; // Start time for proper time duration
unsigned long properTimeDuration = 0; // Measured proper time duration
bool unequalActive = false;    // Track if unequal period is active

void setup() {
  Serial.begin(9600);
  pinMode(powerPin, OUTPUT); // Set power pin as output
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  pinMode(checkPin, OUTPUT); // Set buzzer pin as output
  pinMode(LDR, OUTPUT); // Set buzzer pin as output

  digitalWrite(powerPin, HIGH);
}

void loop() {
  // Read values from potentiometers
  delayTime = map(analogRead(delayTimePin), 0, 1023, 1, 300);     // 1 ms to 100 ms

  // Update the maxDelaySamples based on the delay time
  maxDelaySamples = (sampleRate * delayTime) / 1000;

  // Read from analog input (e.g., LDR sensor)
  int input = analogRead(LDR);

  // Get the delayed value
  float delayedValue = delayLine[writeIndex];

  // Output the delayed value to analog output (PWM)
  analogWrite(delayedOutputPin, delayedValue);

  // Store the new sample in the delay line
  delayLine[writeIndex] = input;

  // Increment and wrap the write index
  writeIndex = (writeIndex + 2) % maxDelaySamples;

  // Check if input and delayed values are unequal
  if (input > value && delayedValue < value && input != delayedValue && delayedValue != 0 && input != 0) {
    if (input > delayedValue + 5 || input < delayedValue - 5) {
      if (!unequalActive) { // If this is the start of an unequal period
        unequalStartTime = millis();
        unequalActive = true;
      }
      tone(buzzerPin, melody[0], 10);
      digitalWrite(checkPin, HIGH);
    }
  } else {
    if (unequalActive) { // If unequal period just ended
      properTimeDuration = millis() - unequalStartTime;
      unequalActive = false;
    }
    noTone(buzzerPin);
    digitalWrite(checkPin, LOW);
  }
 // Print results to Serial Monitor
  Serial.print(" Input Value: ");
  Serial.print(input);
  Serial.print(" - Buzzer Signal: ");
  Serial.print(digitalRead(checkPin));

  Serial.print(" Delayed Output: ");
  Serial.print(delayedValue);
  Serial.print(" Sample Rate: ");
  Serial.print(sampleRate);
  Serial.print(" Hz, Coordinate Time: ");
  Serial.print(delayTime);
  Serial.print(" ms");

  // Display proper time duration when unequal period ends
  if (!unequalActive && properTimeDuration > 0) {
    Serial.print(" - Proper Time Duration: ");
    Serial.print(properTimeDuration);
    Serial.print(" ms");
  }
  
  Serial.println();
  delay(1);
}
