const int analogPin = A0;      // Analog input pin
const int inverterPin = 8;     // Digital output pin for inverter

void setup() {
  Serial.begin(9600);
  pinMode(inverterPin, OUTPUT); // Set inverter pin as output
}

void loop() {
  // Read the analog value
  int analogValue = analogRead(analogPin);
  
  // Invert the signal (logic high if analog value is low and vice versa)
  if (analogValue < 512) {
    digitalWrite(inverterPin, HIGH); // Inverted signal HIGH
  } else {
    digitalWrite(inverterPin, LOW);  // Inverted signal LOW
  }

  // Print the original and inverted values
  Serial.print("Analog Value: ");
  Serial.print(analogValue);
  Serial.print(" - Inverted Signal: ");
  Serial.println(digitalRead(inverterPin));

  delay(1); // Delay for readability
}
