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
int maxDelaySamples = 100;     // Max delay samples
int sampleRate = 100;          // Default sample rate
int delayTime = 1;             // Default delay time in milliseconds
int value = 15;

void setup() {
  Serial.begin(9600);
  pinMode(powerPin, OUTPUT); // Set power pin as output
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  pinMode(checkPin, OUTPUT); // Set buzzer pin as output
  pinMode(LDR, OUTPUT); // Set buzzer pin as output

  digitalWrite(powerPin,HIGH );


}

void loop() {
  // Read values from potentiometers
  delayTime = map(analogRead(delayTimePin), 0, 1023, 1, 100);     // 100 ms to 1000 ms

  // Update the maxDelaySamples based on the delay time
  maxDelaySamples = (sampleRate * delayTime) / 1000;
  
  // Read from analog input (for example, a second potentiometer or sensor)
  int input = analogRead(LDR);
  
  // Convert input to a float value (0-1)
  float inputValue = input;

  // Get the delayed value
  float delayedValue = delayLine[writeIndex];

  // Output the delayed value to analog output (PWM)
  analogWrite(delayedOutputPin, delayedValue); // Assuming you're using pin 9 for output

  // Store the new sample in the delay line
  delayLine[writeIndex] = inputValue;

  // Increment and wrap the write index
  writeIndex = (writeIndex + 1) % maxDelaySamples;

  // Print sample rate and delay time to Serial Monitor
  if (delayedValue > value) {
   noTone(buzzerPin);
    digitalWrite(checkPin,LOW );
  }
  if ( input > value && delayedValue < value && input != delayedValue) {
  tone(buzzerPin, melody[0], 10);
  digitalWrite(checkPin,HIGH );
  }
  // Print the original and inverted values
  Serial.print("Input Value: ");
  Serial.print(input);
  Serial.print(" - Buzzer Signal: ");
  Serial.print(digitalRead(checkPin));



  Serial.print(" Delayed Output: ");
  Serial.print(delayedValue);
  Serial.print(" Sample Rate: ");
  Serial.print(sampleRate);
  Serial.print(" Hz, Delay Time: ");
  Serial.print(delayTime);
  Serial.println(" ms");
  delay(1);
}
