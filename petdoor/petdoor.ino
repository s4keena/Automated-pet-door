#include <Servo.h>

const int reedSwitchPin = 5;    // Pin connected to the reed switch
const int irSensorPin = 10;     // Pin connected to the IR sensor
const int ledPin = 9;           // Pin connected to the LED
const int servoPin = 11;        // Pin connected to the servo motor

Servo myServo;

void setup() {
  pinMode(reedSwitchPin, INPUT);
  pinMode(irSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  myServo.attach(servoPin);
  myServo.write(0); // Initial position of the servo motor
  
  Serial.begin(9600);
}

void loop() {
  int reedSwitchState = digitalRead(reedSwitchPin);
  int irSensorState = digitalRead(irSensorPin);

  Serial.print("Reed Switch State: ");
  Serial.println(reedSwitchState);
  Serial.print("IR Sensor State: ");
  Serial.println(irSensorState);

  if (reedSwitchState == HIGH) {
    // Activate the servo motor
    myServo.write(90); // Move the servo to 90 degrees
    delay(1000);       // Hold position for 1 second
    myServo.write(0);  // Move the servo back to 0 degrees
    delay(1000);       // Hold position for 1 second
    // Send data to Raspberry Pi
    Serial.println("pet_detected");
  }

  if (irSensorState == HIGH) {
    // Turn on the LED
    digitalWrite(ledPin, HIGH);
    // Send data to Raspberry Pi
    Serial.println("movement_detected");
  } else {
    // Turn off the LED
    digitalWrite(ledPin, LOW);
  }

  // Check for serial input to control the servo motor
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'o') {
      // Open the servo (move to 90 degrees)
      myServo.write(90);
    } else if (command == 'c') {
      // Close the servo (move to 0 degrees)
      myServo.write(0);
    }
  }

  delay(500); // Add a small delay for easier observation
}
