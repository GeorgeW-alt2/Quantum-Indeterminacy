const int sampleRate = 40; // Sample rate in Hz
const int delayTime = 700;     // Delay time in milliseconds

// Calculate maximum delay samples, ensuring it's an integer
const int maxDelaySamples = (delayTime * sampleRate) / 1000; // Maximum delay in samples

int audioBuffer[maxDelaySamples]; // Buffer for delay line
int writeIndex = 0;                // Write index for audio buffer
const int threshold = 512;         // Threshold for output inversion
const int outputPin = 9;           // Output pin

void setup() {
  Serial.begin(9600);
  pinMode(outputPin, OUTPUT); // Set pin as output
}

void loop() {
  // Read audio input
  int audioIn = analogRead(A0); // Assume analog input on pin A0

  // Store the audio sample in the delay buffer
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
 Serial.println(audioOut);
  // Update the write index
  writeIndex = (writeIndex + 1) % maxDelaySamples;

  // A small delay to maintain sample rate
  delayMicroseconds(1000000 / sampleRate);
}
