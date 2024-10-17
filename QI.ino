const int sampleRatePotPin = A1;  // Pin for sample rate potentiometer
const int delayTimePotPin = A2;    // Pin for delay time potentiometer
const int minSampleRate = 10;      // Minimum sample rate in Hz
const int maxSampleRate = 100;     // Maximum sample rate in Hz
const int minDelayTime = 100;      // Minimum delay time in milliseconds
const int maxDelayTime = 500;     // Maximum delay time in milliseconds

int audioBuffer[500]; // Buffer for delay line (max buffer size for safety)
int writeIndex = 0;    // Write index for audio buffer
const int threshold = 512; // Threshold for output inversion
const int outputPin = 9;   // Output pin

void setup() {
  Serial.begin(9600);
  pinMode(outputPin, OUTPUT); // Set pin as output
}

void loop() {
  // Read potentiometer values
  int potSampleRate = analogRead(sampleRatePotPin);
  int potDelayTime = analogRead(delayTimePotPin);

  // Map potentiometer values to desired ranges
  int sampleRate = map(potSampleRate, 0, 1023, minSampleRate, maxSampleRate);
  int delayTime = map(potDelayTime, 0, 1023, minDelayTime, maxDelayTime);

  // Calculate maximum delay samples based on delayTime and sampleRate
  const int maxDelaySamples = (delayTime * sampleRate) / 1000; // Maximum delay in samples

  // Store the audio sample in the delay buffer
  int audioIn = analogRead(A0); // Assume analog input on pin A0
  audioBuffer[writeIndex] = audioIn;

  // Calculate the read index for the delayed sample
  int readIndex = (writeIndex + 1) % maxDelaySamples; // Wrap around the buffer

  // Get the delayed audio sample
  int audioOut = audioBuffer[readIndex];

  // Invert the output based on the threshold
  if (audioOut > threshold) {
    digitalWrite(outputPin, LOW); // Output LOW if audioOut is above the threshold
  } else {
    digitalWrite(outputPin, HIGH); // Output HIGH if audioOut is below the threshold
  }

  // Print delayTime and sampleRate
  Serial.print("Sample Rate: ");
  Serial.print(sampleRate);
  Serial.print(" Hz, Delay Time: ");
  Serial.print(delayTime);
  Serial.println(" ms");

  // Update the write index
  writeIndex = (writeIndex + 1) % maxDelaySamples;

  // A small delay to maintain sample rate
  delayMicroseconds(1000000 / sampleRate);
}
