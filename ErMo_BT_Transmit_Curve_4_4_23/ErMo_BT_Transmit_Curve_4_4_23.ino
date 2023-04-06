//ErMo Joystick Transmitter Code
//Written by Jack McTasney
//Based off of example from https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html

#include <AltSoftSerial.h>
AltSoftSerial BTserial;
// https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html


char c = ' ';
boolean NL = true;
int x = A0;
int y = A1;
int joystickX = 0; //Holds joystick x value for transmission
int joystickY = 0; //Holds joystick y value for transmission
int storedX = 0;
int storedY = 0;
int scaleFactor = 2; //factor for acceleration
int lowerRange = 10; //lower bound of range for mapping
int upperRange = 89; //upper bound of range for mapping

void setup()
{
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  Serial.begin(9600);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");
  BTserial.begin(9600);
  Serial.println("BTserial started at 9600");
  //Initialization protocol version 1
  BTserial.print("AT");
  delay(1000);
  BTserial.print("AT+CO094A9A83AED70");
  delay(1000);
  BTserial.print("AT+CO094A9A83AED70");
  delay(1000);
  BTserial.print("AT+CO094A9A83AED70");
  storedX = map(analogRead(x), 0, 1023, lowerRange, upperRange);
  storedY = map(analogRead(y), 0, 1023, lowerRange, upperRange);
}

void loop()
{
  // Read from the Bluetooth module and send to the Arduino Serial Monitor
  if (BTserial.available())
  {
    c = BTserial.read();
    Serial.write(c);
  }
  /*
  //Attempt 1 at an in-loop connection protocol
  if (BTserial.available() != true) //If connection is unavailable for 1 second, begin connection protocol
  {
    delay(1000);
    if (BTserial.available() != true)
    {
      BTserial.print("AT");
      delay(500);
      BTserial.print("AT+CO094A9A83AED70");
      delay(500);
      BTserial.print("AT+CO094A9A83AED70");
      delay(500);
      BTserial.print("AT+CO094A9A83AED70");
    }
  }
*/


  joystickX = map(analogRead(x), 0, 1023, lowerRange, upperRange);
  joystickY = map(analogRead(y), 0, 1023, lowerRange, upperRange);
  if (joystickX>storedX) { //If joystick value is larger than stored value (X)
    storedX+=scaleFactor;
  }
  else if (joystickX<storedX) {
    storedX-=scaleFactor;
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
  Serial.flush();
  Serial.write("----------{");
  Serial.print(storedX);
  Serial.write(",");
  Serial.print(storedY);
  Serial.write("}");
  Serial.write("\n");
  BTserial.print("----------{");
  BTserial.print(storedX);
  BTserial.print(",");
  BTserial.print(storedY);
  BTserial.print("}\n"); //Includes a newline to avoid packet deformation
  delay(1000);
}
