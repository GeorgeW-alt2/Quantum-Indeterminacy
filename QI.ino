const int sampleRatePin = A0;  // Potentiometer for sample rate
const int delayTimePin = A1;    // Potentiometer for delay time

float delayLine[300];          // Maximum delay line size
int writeIndex = 0;              // Write index for delay line
int maxDelaySamples = 100;     // Max delay samples
int sampleRate = 50;          // Default sample rate
int delayTime = 1;             // Default delay time in milliseconds

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read values from potentiometers
  sampleRate = map(analogRead(sampleRatePin), 0, 1023, 1, sampleRate); // 1 kHz to 44.1 kHz
  delayTime = map(analogRead(delayTimePin), 0, 1023, 1, delayTime);     // 100 ms to 1000 ms

  // Update the maxDelaySamples based on the delay time
  maxDelaySamples = (sampleRate * delayTime) / 1000;
  
  // Read from analog input (for example, a second potentiometer or sensor)
  int input = analogRead(A2);
  
  // Convert input to a float value (0-1)
  float inputValue = input / 1023.0;

  // Get the delayed value
  float delayedValue = delayLine[writeIndex];

  // Output the delayed value to analog output (PWM)
  analogWrite(9, delayedValue * 255); // Assuming you're using pin 9 for output

  // Store the new sample in the delay line
  delayLine[writeIndex] = inputValue;

  // Increment and wrap the write index
  writeIndex = (writeIndex + 1) % maxDelaySamples;

  // Print sample rate and delay time to Serial Monitor
  Serial.print("Sample Rate: ");
  Serial.print(sampleRate);
  Serial.print(" Hz, Delay Time: ");
  Serial.print(delayTime);
  Serial.println(" ms");

  // Small delay to match the sample rate
  delayMicroseconds(1000000 / sampleRate);
}
