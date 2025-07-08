//flex sensor calibration

const int pin = A0;

int min = 2000;
int max = -1;

void setup() {
  Serial.begin(9600);

}

void loop() {

  int read = analogRead(pin);

  if (read > max) {
    max = read;
  }
  if (read < min) {
    min = read;
  }
  

  Serial.print("Max:");
  Serial.print(max);
  Serial.print(" Min: ");
  Serial.println(min);



  delay(25);

}
