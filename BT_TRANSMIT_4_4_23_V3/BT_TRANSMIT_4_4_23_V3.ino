#include <AltSoftSerial.h>
AltSoftSerial BTserial;
int x = A0;
int y = A1;
int joystickX = 0; //Holds joystick x value for transmission
int joystickY = 0; //Holds joystick y value for transmission
int storedX = 0; //Holds analog value for curve
int storedY = 0; //Holds analog value for curve
int scaleFactor = 100;


void setup() {
  // put your setup code here, to run once:
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  BTserial.begin(9600);
  Serial.begin(9600);
  BTserial.print("AT");
  delay(1000);
  BTserial.print("AT+CO094A9A83AED70");
  delay(1000);
  BTserial.print("AT+CO094A9A83AED70");
  delay(1000);
  BTserial.print("AT+CO094A9A83AED70");
  storedX = analogRead(x);
  storedY = analogRead(y);
}

void loop() {
  // put your main code here, to run repeatedly:
  joystickX = analogRead(x);
  joystickY = analogRead(y);

  if (joystickX>storedX) { //If joystick value is larger than stored value (X)
    storedX+=scaleFactor*0.5; //0.5 is so it turns slower than it accelerates
  }
  else if (joystickX<storedX) {
    storedX-=scaleFactor*0.5; //0.5 is so it turns slower than it accelerates
  }
  else {
    storedX=storedX;
  }
 if (joystickY>storedY) { //If joystick value is larger than stored value (X)
    storedY+=scaleFactor;
  }
  else if (joystickY<storedY) {
    storedY-=scaleFactor;
  }
  else {
    storedY=storedY;
  }
  
  Serial.print("{");
  Serial.print(storedX);
  Serial.print(",");
  Serial.print(storedY);
  Serial.print("}\n");
  
  BTserial.print("{");
  BTserial.print(storedX);
  BTserial.print(",");
  BTserial.print(storedY);
  BTserial.print("}\n");
  delay(100);
}
