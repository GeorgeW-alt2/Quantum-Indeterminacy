const int delayedInputPin = A4;      // Analog input pin
const int LDRPin = A1;      // Analog input pin
const int buzzerPin = 12;     // Digital output pin for inverter

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT); // Set inverter pin as output
}

void loop() {
  // Read the analog value
  int analogValue = analogRead(delayedInputPin);

  int LDRValue = analogRead(LDRPin);

  // Invert the signal (logic high if analog value is low and vice versa)
  if (analogValue < 512 && LDRValue > 512) {
    digitalWrite(buzzerPin, HIGH); // Inverted signal HIGH
  } else {
    digitalWrite(buzzerPin, LOW);  // Inverted signal LOW
  }

  // Print the original and inverted values
  Serial.print("delayed Input Value: ");
  Serial.print(analogValue);
  Serial.print(" - Buzzer Signal: ");
  Serial.println(digitalRead(buzzerPin));

  delay(1); // Delay for readability
}