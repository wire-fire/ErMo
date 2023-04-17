#include <AltSoftSerial.h>
AltSoftSerial BTserial;
int x = A0;
int y = A1;
int intensityPin = A2;
int joystickX = 0; //Holds joystick x value for transmission (STEERING)
int joystickY = 0; //Holds joystick y value for transmission (THROTTLE)
int intensity = 0; //Holds intensity potentiometer value
int storedX = 0; //Holds analog value for curve
int storedY = 0; //Holds analog value for curve
int scaleFactor = 10; //Variable for scaling output


void setup() {
  // put your setup code here, to run once:
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(intensityPin, INPUT);
  BTserial.begin(9600);
  Serial.begin(9600);
  BTserial.print("AT");
  delay(1000);
  BTserial.print("AT+CO094A9A83AED70");
  delay(1000);
  BTserial.print("AT+CO094A9A83AED70");
  delay(1000);
  BTserial.print("AT+CO094A9A83AED70");
  storedX = map(analogRead(x), 0, 1023, 1200, 1800);
  storedY = map(analogRead(y), 0, 1023, 1000, 2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  joystickX = map(analogRead(x), 0, 1023, 1200, 1800);
  joystickY = map(analogRead(y), 0, 1023, 1000, 2000);
  Serial.print("joystickX: ");
  Serial.println(joystickX);
  Serial.print("joystickY: ");
  Serial.println(joystickY);
  intensity = map(analogRead(intensityPin), 0, 1023, 0, 10); //Scaling factor from potentiometer
  Serial.print("Intensity: ");
  Serial.println(intensity);

  //Acceleration Curve
  if (joystickX > storedX) { //If joystick value is larger than stored value (X)
    storedX += (scaleFactor + intensity);
  }
  else if (joystickX < storedX) {
    storedX -= (scaleFactor + intensity);
  }
  else {
    storedX = storedX;
  }
  if (joystickY > storedY) { //If joystick value is larger than stored value (X)
    storedY += (scaleFactor + intensity);
  }
  else if (joystickY < storedY) {
    storedY -= (scaleFactor + intensity);
  }
  else {
    storedY = storedY;
  }

  //Centering forgiveness
  if (1400 < joystickX && joystickX < 1600)
  {
    storedX = 1470; //Experimentally determined center value (STEERING)
  }
  if (1400 < joystickY && joystickY < 1600)
  {
    storedY = 1557; //Experimentally determined center value (THROTTLE)
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
  delay(200);
}
