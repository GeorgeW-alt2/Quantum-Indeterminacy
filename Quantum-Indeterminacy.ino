#GeorgeW-alt2/Quantum-Indeterminacy

int analogPin = A0;  // Pin to read signal
int signalStartThreshold = 50; // Threshold to detect the signal starting (e.g., 50/1023 ≈ 0.24V)
int lowThreshold = 102;  // 10% of 5V (102/1023 ≈ 0.5V)
int highThreshold = 921; // 90% of 5V (921/1023 ≈ 4.5V)

unsigned long startTime = 0;
unsigned long endTime = 0;
bool signalDetected = false;  // To detect when signal starts
bool rising = false;
bool finished = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int signalValue = analogRead(analogPin);
  
  // Start measuring rise time only when the signal first rises above a small threshold
  if (signalValue >= signalStartThreshold && !signalDetected) {
    signalDetected = true;  // Signal has started
    Serial.println("Signal detected, starting measurement...");
  }
  
  // If signal has been detected, continue rise time measurement
  if (signalDetected) {
    
    // Check if signal is rising past 10% threshold
    if (signalValue >= lowThreshold && !rising) {
      startTime = micros();  // Start timer at 10% threshold
      rising = true;
    }

    // Check if signal has passed the 90% threshold
    if (signalValue >= highThreshold && rising && !finished) {
      endTime = micros();  // Stop timer at 90% threshold
      finished = true;
      
      unsigned long riseTime = endTime - startTime;  // Calculate rise time in microseconds
      Serial.print("Rise Time: ");
      Serial.print(riseTime);
      Serial.println(" microseconds");

      // Reset for the next signal detection
      signalDetected = false;
      rising = false;
      finished = false;
      delay(1);  // Delay between readings to avoid immediate re-triggering
    }
  }
}
