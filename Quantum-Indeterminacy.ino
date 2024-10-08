int analogPin = A0;            // Pin to read the signal
int buzzerPin = 3;             // Pin to control the buzzer

int signalStartThreshold = 50;  // Threshold to detect the signal starting (e.g., 50/1023 ≈ 0.24V)
int lowThreshold = 102;         // 10% of 5V (102/1023 ≈ 0.5V)
int highThreshold = 921;        // 90% of 5V (921/1023 ≈ 4.5V)

unsigned long startTime = 0;
unsigned long endTime = 0;
bool signalDetected = false;    // To detect when the signal starts
bool rising = false;
bool finished = false;

unsigned long sharpRiseTimeThreshold = 500; // Define what constitutes a "sharp" rise (in microseconds)

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);   // Set the buzzer pin as output
  digitalWrite(buzzerPin, LOW); // Initially, keep the buzzer off
}

void loop() {
  int signalValue = analogRead(analogPin);

  // Start measuring rise time only when the signal first rises above a small threshold
  if (signalValue >= signalStartThreshold && !signalDetected) {
    signalDetected = true;  // Signal has started
    Serial.println("Signal detected, starting measurement...");
  }

  // If the signal has been detected, continue rise time measurement
  if (signalDetected) {

    // Check if signal is rising past 10% threshold
    if (signalValue >= lowThreshold && !rising) {
      startTime = micros();  // Start timer at 10% threshold
      rising = true;
    }

    // Check if signal has passed the 90% threshold
    if (signalValue >= highThreshold && rising && !finished) {
      endTime = micros();    // Stop timer at 90% threshold
      finished = true;

      unsigned long riseTime = endTime - startTime;  // Calculate rise time in microseconds
      Serial.print("Rise Time: ");
      Serial.print(riseTime);
      Serial.println(" microseconds");

      // Check if the rise time is "sharp" and activate the buzzer if it is
      if (riseTime < sharpRiseTimeThreshold) {
        Serial.println("Sharp rise detected! Activating buzzer...");
        digitalWrite(buzzerPin, HIGH);  // Turn the buzzer ON
        delay(1000);                    // Keep the buzzer ON for 1 second
        digitalWrite(buzzerPin, LOW);   // Turn the buzzer OFF
      }

      // Reset for the next signal detection
      signalDetected = false;
      rising = false;
      finished = false;
      delay(1);  // Small delay between readings to avoid immediate re-triggering
    }
  }
}
