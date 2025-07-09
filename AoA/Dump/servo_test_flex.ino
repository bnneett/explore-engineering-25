#include <Servo.h>

const int flex = A0;
int pos = 90;
Servo servoFlex;


void setup() {
  servoFlex.attach(9);
  servoFlex.write(pos);
  Serial.begin(9600);


}

void loop() {

  int readFlex = analogRead(flex); //0-1023

  // instead of 0-1023, we should map the ACTUAL recorded range from each individual sensor
  int target = map(readFlex, 0, 1023, 0, 180); //map our ADC reading to servo position

  if (pos < target) {
    pos++;
  } else if (pos > target) {
    pos--;
  }

  Serial.print("adc:");
  Serial.println(readFlex);


  // just in case for not overriding the servo with unnecessary writing
  static int lastPos = -1;

  if (pos != lastPos) {
    servoFlex.write(pos);
  }
  lastPos = pos;

  delay(20);

}
