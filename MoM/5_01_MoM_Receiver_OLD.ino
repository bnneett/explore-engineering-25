#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

//NOTE: SCK, MISO, MOSI pins are defined automatically by Arduino and must be wired correctly to work
// SCK = D13, MOSI = D11, MISO = D12

const int motor_enA = 6; //pwm required
const int motor_in1 = 5; //direction 1
const int motor_in2 = 4; //direction 2

RF24 radio(10, 9); //CE, CSN
const byte address[10] = "ADDRESS01"; //can be any 9 character (ascii only) string literal. "\0" is automatically appended at the end, making it 10 bytes
//ensure address matches transmitter

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address); //open communications w/ given address (reading)
  radio.setPALevel(RF24_PA_MAX); //idk what this does
  radio.startListening();

  pinMode(motor_enA, OUTPUT);
  pinMode(motor_in1, OUTPUT);
  pinMode(motor_in2, OUTPUT);

  analogWrite(motor_enA, 0); //0-255 for speed
  digitalWrite(motor_in1, HIGH); //forward
  digitalWrite(motor_in2, LOW); //forward

  Serial.println("Setup complete!");
}

void loop() {
  if (radio.available()) {
    char txt[5] = "";
    radio.read(&txt, sizeof(txt));

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

    if (strncmp(message + 2, "S3", 2) == 0) {
      Serial.println("SERVO LEFT");
    } else if (strncmp(message + 2, "S4", 2) == 0) {
      Serial.println("SERVO RIGHT");
    } else {
      Serial.println("SERVO STOP")
    }

    //Serial.println(txt);

  } else {
    Serial.println("NO TRANSMITTER FOUND!");
  }
  delay(50);

}
