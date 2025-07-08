/*
this code reads sensor values connected to a multiplexer (MUX)
and prints the output to the serial monitor.
MUX channels are controlled by the microcontroller and each connected to one sensor:
- c0 and c1 are active sensor channels
- c2 is a grounded channel for testing crosstalk
*/

//define pins:
const int sig = A0; //pin for analog signal from MUX
const int s0 = D3; // s0 - s3 are MUX select pins
const int s1 = D4;
const int s2 = D5;
const int s3 = D6;
int c0, c1, c2; //variables to store sensor readings

//define helper function:
void selectChannel(int channel) {
  /* 
  digitalWrite(pin, LOW/HIGH) writes 0 (LOW) or 1 (HIGH) to the select pins.
  we use bitwise shifts and masks to set each bit in the correct order
  to select the desired channel
  */
    digitalWrite(s3, (channel >> 3) & 0b0001); //most significant bit
    digitalWrite(s2, (channel >> 2) & 0b0001);
    digitalWrite(s1, (channel >> 1) & 0b0001);
    digitalWrite(s0, channel & 0b0001); //least significant bit
  }

void setup() {
 //initialize GPIO pins to their desired modes (output for MUX selects, input for MUX signal)
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sig, INPUT);

  analogSetAttenuation(ADC_11db);  //ensuring ADC (analog-to-digital converter) range is 0V - 3.3V
  Serial.begin(115200); //start communication with the serial monitor at 115200 baud rate
  Serial.println("Resetting..."); //print to the serial monitor (debugging purposes)
}

void loop() {
  /*
  we manually select MUX channels and read the analog signal for each channel/sensor.
  loop structure:
  -select desired channel # (0-15)
  -brief delay for signal to stabilize (in milliseconds)
  -read in the analog signal from signal pin (sig) and store in variables (c0, c1, c2)
  */

  selectChannel(0);
  delay(50);
  c0 = analogRead(sig);
  c0 = (c0 / 4096) * 3.3; //convert to voltage
  
  selectChannel(1);
  delay(50);
  c1 = analogRead(sig);
  c1 = (c1 / 4096) * 3.3; //convert to voltage

  selectChannel(2);
  delay(50);
  c2 = analogRead(sig);
  c2 = (c2 / 4096) * 3.3; //convert to voltage

  //print iteration readings to the serial monitor & plotter
  Serial.print(" ");
  Serial.print(c0);
  Serial.print(" ");
  Serial.print(c1);
  Serial.print(" ");
  Serial.println(c2);

  delay(50); //short delay before next iteration

}
