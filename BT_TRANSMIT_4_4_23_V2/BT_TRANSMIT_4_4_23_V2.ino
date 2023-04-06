#include <AltSoftSerial.h>
AltSoftSerial BTserial;
int x = A0;
int y = A1;
int joystickX = 0; //Holds joystick x value for transmission
int joystickY = 0; //Holds joystick y value for transmission


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
}

void loop() {
  // put your main code here, to run repeatedly:
  joystickX = analogRead(x);
  joystickY = analogRead(y);
  
  Serial.print("{");
  Serial.print(joystickX);
  Serial.print(",");
  Serial.print(joystickY);
  Serial.print("}\n");
  
  BTserial.print("{");
  BTserial.print(joystickX);
  BTserial.print(",");
  BTserial.print(joystickY);
  BTserial.print("}\n");
  delay(100);
}
