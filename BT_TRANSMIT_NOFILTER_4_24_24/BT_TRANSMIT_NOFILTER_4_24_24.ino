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
// Ceiling variables for steering/throttle
int steeringMax = 1600;
int steeringMin = 1400;
int throttleMax = 2000;
int throttleMin = 1000;

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
  storedX = map(analogRead(x), 0, 1023, steeringMin, steeringMax); //Steering
  storedY = map(analogRead(y), 0, 1023, throttleMin, throttleMax); //throttle
}

void loop() {
  // put your main code here, to run repeatedly:
  joystickX = map(analogRead(x), 0, 1023, steeringMin, steeringMax); //Steering
  joystickY = map(analogRead(y), 0, 1023, throttleMin, throttleMax); //Throttle
  Serial.print("joystickX: ");
  Serial.println(joystickX);
  Serial.print("joystickY: ");
  Serial.println(joystickY);
  intensity = map(analogRead(intensityPin), 0, 1023, 0, 50); //Scaling factor from potentiometer (0-->1023 ---> 0-->10)
  Serial.print("Intensity: ");
  Serial.println(intensity);

  storedX = joystickX;
  storedY = joystickY;
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
