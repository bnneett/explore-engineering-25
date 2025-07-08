#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

//NOTE: SCK, MISO, MOSI pins are defined automatically by Arduino and must be wired correctly to work
// SCK = D13, MOSI = D11, MISO = D12

RF24 radio(10, 9); //CE, CSN
const byte address[10] = "ADDRESS01"; //can be any 9 character (ascii only) string literal. "\0" is automatically appended at the end, making it 10 bytes
//ensure address matches receiver

const int switchDC_1 = 4;
const int switchDC_2 = 3;

const int switchServo_1 = 6;
const int switchServo_2 = 5;

//defining what is actually transmitted based on what's pressed
char txt1[3] = "S1", txt2[3] = "S2", txt3[3] = "S3", txt4[3] = "S4", txt5[3] = "05", txt6[3] = "06"; 

void setup() {
  Serial.begin(9600);

  pinMode(switchDC_1, INPUT_PULLUP);
  pinMode(switchDC_2, INPUT_PULLUP);
  pinMode(switchServo_1, INPUT_PULLUP);
  pinMode(switchServo_2, INPUT_PULLUP);

  radio.begin();
  radio.openWritingPipe(address); //open communications w/ given address (writing)
  radio.setPALevel(RF24_PA_MAX); //idk what this does
  radio.stopListening();
}

void loop() {
  int DC1_State = digitalRead(switchDC_1);
  int DC2_State = digitalRead(switchDC_2);

  int SV1_State = digitalRead(switchServo_1);
  int SV2_State = digitalRead(switchServo_2);

  char message[5] = ""; //this could be a fun lesson, msg encoding for multidimensional data transmission

  if (DC1_State == LOW) {
    strcat(message, txt1);
  } else if (DC2_State == LOW) {
    strcat(message, txt2);
  } else {
    strcat(message, txt5);
  }

  if (SV1_State == LOW) {
    strcat(message, txt3);
  } else if (SV2_State == LOW) {
    strcat(message, txt4);
  } else {
    strcat(message, txt6);
  }

  Serial.println(message);
  bool success = radio.write(&message, sizeof(message));
  if (!success) {
    Serial.println("Failed to send");
  }

  delay(50);
}
