//Hoverboard Driving Code
//Written by Jack McTasney

#include <Servo.h>

Servo ch1;
Servo ch2;

int ch1Width = 0;
int ch2Width = 0;

int ch1Pin = 5;
int ch2Pin = 6;

int x = 127; //int, change to byte if no work
int y = 200;

char c[10];

String strX;//Hold strings for x and y
String strY;
String numStore = " "; //Stores characters as integer
int ind1, ind2, ind3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(20);
  ch1.attach(ch1Pin);
  ch2.attach(ch2Pin);
}

void loop() {
  int i = 0;
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    delay(100);
    while (Serial.available()&&i<10) {
      c[i++] = Serial.read();
    }
    Serial.print(c);
    //Serial.print(numStore);
    
  }
  else
  {
    //Serial.print(c);
    //delay(20);//SYNCHRONIZED STABILITY DELAY
    ind1 = numStore.indexOf("{"); //Finds { index
    ind2 = numStore.indexOf(","); //Finds , index
    ind3 = numStore.indexOf("}"); //Finds } index
    strX = numStore.substring(ind1 + 1, ind2); //captures first data String
    strY = numStore.substring(ind2 + 1, ind3); //captures second data String
    x = strX.toInt();
    y = strY.toInt();
    /*
      Serial.print(x);
      Serial.print(", ");
      Serial.println(y);
    */
    numStore = " ";
    ch1Width = map(x, 0, 99, 1000, 2000);
    ch2Width = map(y, 0, 99, 1000, 2000);
    ch1.writeMicroseconds(ch1Width);
    ch2.writeMicroseconds(ch2Width);
  }
}
