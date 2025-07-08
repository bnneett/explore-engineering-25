#include <Servo.h> // make sure you have this package installed, or your servo won't work

// the first thing we need to do is define the constant (immutable) variables that are going to be used throughout the sketch
// at the very least, define your pin numbers

const int piezoPin = A0;
const int ledPin = 2;
const int servoPin = 9;

const int threshold = 100; // we are also going to define a "threshold" variable to determine the sensitivity of our piezo disc sensor

Servo servo1; // instantiate a servo object named "servoname"
int servo1Pos = 0; // the servo functions by writing a position (0-180 degrees) to the hardware. initalize this variable to 0

void setup() {
  // this code only runs once when the UNO is reset or plugged in
  pinMode(ledPin, OUTPUT); // digital pins can be input or output, so we specify that the pin controlling our LED is an output pin
  servoname.attach(servoPin); // attach the servo object to the data pin (pin 9) it is connected to
  servoname.write(servoPos); // this function is how you write the given angle (stored in servoPos) to the servo

  Serial.begin(9600); // establish communication with the Serial monitor (this is where you print to)
}

void loop() {
  // this code will run on a continuous loop until the UNO is unplugged
  int sensorValue = analogRead(piezoPin); // take the reading from the piezoelectric disc and store it in a temporary variable
  Serial.println(sensorValue); // print what we read in
  

  // essentially, if the value we read in is at or higher than the threshold we set, that counts as a "press". a lower value = higher sensitivity to touch, and vice versa.
  if (sensorValue >= threshold) {

    // we turn the LED on for a brief moment to indicate a press
    // ditigal pins only have two states: HIGH (on) and LOW (off)
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);

    // all we do here is toggle the direction of the servo on a successful press, from 0 to 180 or 180 to 0
    if (servoPos == 0) {
      servoPos = 180;
    } else {
      servoPos = 0;
    }
  }
  servoname.write(servoPos); // actually have to write the new orientation to the servo after changing the variable
  delay(250); // small delay between cycles so we don't overwhelm the hardware (the number is in milliseconds)
}
