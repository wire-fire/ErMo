#include <Servo.h>
const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;
String test = "";
char c;
Servo ch1;
Servo ch2;
int ch1Pin = 5;
int ch2Pin = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink_, CHANGE);
  ch1.attach(ch1Pin);
  ch2.attach(ch2Pin);
}

void loop() {
  // put your main code here, to run repeatedly:

}


void blink_() {
  state = !state;
  //Serial.println("I AM HERE");
  if (c == '}') {
    //Serial.print(test);
    int ind1 = test.indexOf("{"); //Finds { index
    int ind2 = test.indexOf(","); //Finds , index
    int ind3 = test.indexOf("}"); //Finds } index
    String strX = test.substring(ind1 + 1, ind2); //captures first data String
    String strY = test.substring(ind2 + 1, ind3); //captures second data String
    int x = strX.toInt();
    int y = strY.toInt();
    int ch1Width = map(x, 0, 1023, 1000, 2000);
    int ch2Width = map(y, 0, 1023, 1000, 2000);
    Serial.print(ch1Width);
    Serial.print(", ");
    Serial.println(ch2Width);
    ch1.writeMicroseconds(ch1Width);
    ch2.writeMicroseconds(ch2Width);
    test="";
    c = ' ';
  }
  else
  {
    while (Serial.available())
    {
      c = Serial.read();
      test += c;
    }
  }
    digitalWrite(ledPin, state);
  }
