const int analogPin = A2;      // Analog input pin
const int inverterPin = 8;     // Digital output pin for inverter
const int delayLineLength = 4; // Length of the delay line
int delayLine[delayLineLength]; // Array to store previous analog readings
int currentIndex = 0;           // Current index for the delay line
unsigned long lastAnalogHighTime = 0;
unsigned long lastDelayedHighTime = 0;
int time = 970;

void setup() {
  Serial.begin(9600);
  pinMode(inverterPin, OUTPUT); // Set inverter pin as output
  // Initialize delay line
  for (int i = 0; i < delayLineLength; i++) {
    delayLine[i] = 0;
  }
}
int steps = 0;

void loop() {
  // Read the analog value
  int analogValue = analogRead(analogPin);
  
  // Store the current reading in the delay line
  delayLine[currentIndex] = analogValue;
  currentIndex = (currentIndex + 1) % delayLineLength; // Circular buffer

  // Get the delayed value
  int delayedValue = delayLine[(currentIndex + delayLineLength - 5) % delayLineLength];

  // Check conditions for inverter signal
  if (delayedValue > time && analogValue > time) {
    digitalWrite(inverterPin, HIGH); // Inverted signal HIGH

    if (steps > 2 && steps < 5){
    Serial.print(" HIGH ");
    Serial.print("Steps taken: ");
    Serial.print(steps);
      
    // Print the original and delayed values
    Serial.print(" Analog Value: ");
    Serial.print(analogValue);
    Serial.print(" - Delayed Value: ");
    Serial.print(delayedValue);
    Serial.print(" - Inverted Signal: ");
    Serial.println(digitalRead(inverterPin));
    }
    if (steps > 0 && steps < 3){
    Serial.print(" LOW ");
    Serial.print("Steps taken: ");
    Serial.print(steps);
      
    // Print the original and delayed values
    Serial.print(" Analog Value: ");
    Serial.print(analogValue);
    Serial.print(" - Delayed Value: ");
    Serial.print(delayedValue);
    Serial.print(" - Inverted Signal: ");
    Serial.println(digitalRead(inverterPin));
    }

    steps = 0; // Reset steps after printing
  } else {
    digitalWrite(inverterPin, LOW);  // Inverted signal LOW
    steps++; // Increment steps
  }
  

  //delay(1); // Optional delay for readability
}
