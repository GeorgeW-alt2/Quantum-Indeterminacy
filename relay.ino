// Define the pins
const int relayPin = 7;   // Pin connected to the relay
const int inputPin = 2;   // Pin connected to the digital input (e.g., switch)

void setup() {
  // Set the relay pin as an output
  pinMode(relayPin, OUTPUT);
  // Set the input pin as an input
  pinMode(inputPin, INPUT);
}

void loop() {
  // Read the state of the input pin
  int inputState = digitalRead(inputPin);

  // Check if the input pin is HIGH
  if (inputState == HIGH) {
    // Turn the relay ON
    digitalWrite(relayPin, HIGH);
  } else {
    // Turn the relay OFF
    digitalWrite(relayPin, LOW);
  }
}
