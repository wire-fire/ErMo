#include <i2c_master.h>
#include <myADC.h>
#include <myGPIO.h>
#include <myTimer.h>
#include <my_ssd1306.h>

#include <AltSoftSerial.h>

AltSoftSerial BTserial;
const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;


void setup() {
  // put your setup code here, to run once:
  BTserial.begin(9600);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink_, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}


void blink_() {
  char c;
  String test =  "";
  state = !state;
  //Serial.println("I AM HERE");
  while (BTserial.available())
  {
    c = BTserial.read();
    test+=c;
  }
  Serial.print(test);
  digitalWrite(ledPin,state);
}
