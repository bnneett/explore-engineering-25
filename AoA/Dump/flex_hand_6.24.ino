#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver hand = Adafruit_PWMServoDriver(0x40);       // called this way, it uses the default address 0x40   
#define SERVOMIN  125                                                 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  625                                                 // this is the 'maximum' pulse length count (out of 4096)

const int tmb = A0;
const int idx = A1;
const int mid = A2;
const int rng = A3;
//const int pky = A4;

int lastAngles[4] = {0, 0, 0, 0}; //for smoothing
const float smoothing = 0.1; //smoothing factor (lower = more smooth, 1 = no smooth)

void setup() {
  Serial.begin(9600);
  hand.begin();
  hand.setPWMFreq(60);
  Serial.println("Setup Complete!");

}

void loop() {

//important to know which fingers are which indices on the board
  int reads[4] = {
    analogRead(tmb),
    analogRead(idx),
    analogRead(mid),
    analogRead(rng)
    //analogRead(pky);
  };

  //follows the same order as the above array, tmb->pky
  int adcMins[4] = {
    324,
    97,
    58,
    61
    //87
  };

  // ditto
  int adcMaxes[4] = {
    779,
    940,
    574,
    909
    //710
  };

  for (int i = 0; i < 4; i++) {

    
    int raw = reads[i]; // sensor reading 

    //target angle
    int targetAngle = map(raw, adcMins[i], adcMaxes[i], 0, 180); //calculating the angle for the servo based on reading
    lastAngles[i] = lastAngles[i] + (targetAngle  - lastAngles[i]) * smoothing; // angle tracking + smoothing
    
    Serial.println(lastAngles[i]); // for debugging

    //corresponding pulse for angle
    int pulse = map(lastAngles[i], 0, 180, SERVOMIN, SERVOMAX);
    hand.setPWM(i, 0, pulse);

  }

  delay(25);
}
