#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Servo.h>

// ?? integrate driver? optional, see if needed

//NOTE: SCK, MISO, MOSI pins are defined automatically by Arduino and must be wired correctly to work
// SCK = D13, MOSI = D11, MISO = D12

const int motor_enA = 6; //pwm required
const int motor_in1 = 5; //direction 1
const int motor_in2 = 4; //direction 2


//servo init
Servo steerServo;
int pos = 90;
int steerRate = 3; //multiplier for steering (no easing, just linear)

RF24 radio(10, 9); //CE, CSN
const byte address[10] = "ADDRESS01"; //can be any 9 character (ascii only) string literal. "\0" is automatically appended at the end, making it 10 bytes
//ensure address matches transmitter

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.printDetails();
  radio.openReadingPipe(0, address); //open communications w/ given address (reading)
  radio.setPALevel(RF24_PA_MAX); //idk what this does
  radio.startListening();

  pinMode(motor_enA, OUTPUT);
  pinMode(motor_in1, OUTPUT);
  pinMode(motor_in2, OUTPUT);

  steerServo.attach(3);
  steerServo.write(pos); // init position & the one we track

  analogWrite(motor_enA, 0); //0-255 for speed
  digitalWrite(motor_in1, HIGH); //forward
  digitalWrite(motor_in2, LOW); //forward

  Serial.println("Setup complete!");
}

void loop() {
  if (radio.available()) {
    char message[5] = "";
    radio.read(&message, sizeof(message));

    if (strncmp(message, "S1", 2) == 0) {
      analogWrite(motor_enA, 255); 
      digitalWrite(motor_in1, HIGH); 
      digitalWrite(motor_in2, LOW);
    } else if (strncmp(message, "S2", 2) == 0) {
      analogWrite(motor_enA, 255); 
      digitalWrite(motor_in1, LOW); 
      digitalWrite(motor_in2, HIGH);
    } else {
      analogWrite(motor_enA, 0);
    }

    int targetPos; //please make sure you actually calibrate direction...

    if (strncmp(message + 2, "S3", 2) == 0) {
      targetPos = 0;
    } else if (strncmp(message + 2, "S4", 2) == 0) {
      targetPos = 180;
    } else {
      targetPos = pos;
    }

    if (pos < targetPos) {
      pos = pos + steerRate;
    } else if (pos > targetPos) {
      pos = pos - steerRate;
    }

    // just in case for not overriding the servo with unnecessary writing
    static int lastPos = -1;

    if (pos != lastPos) {
      steerServo.write(pos);
    }
    lastPos = pos;

  } else {
    Serial.println("No message received!");
  }
  delay(50);

}
