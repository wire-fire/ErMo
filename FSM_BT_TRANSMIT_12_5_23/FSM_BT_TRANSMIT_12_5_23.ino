#include <SoftwareSerial.h> //Software serial used for BT
#define RX 5
#define TX 6


SoftwareSerial btTransmit(RX,TX); //rx,tx

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  btTransmit.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()){
    btTransmit.write(Serial.read());
  }
  while (btTransmit.available()){
    Serial.write(btTransmit.read());
  }
}
