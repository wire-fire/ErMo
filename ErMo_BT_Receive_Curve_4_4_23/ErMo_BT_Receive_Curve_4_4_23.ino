//Hoverboard BT receiver code
//Written by Jack McTasney
//Based off of example from https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html

#include <AltSoftSerial.h>
AltSoftSerial BTserial;

char c = ' ';
boolean NL = true;
int CH1 = 5; //CHANNEL 1 pin
int CH2 = 6; //CHANNEL 2 pin
String strX;//Hold strings for x and y
String strY;
int x = 0;//x value from joystick
int y = 0;//y value from joystick
String numStore = " "; //Stores characters as integer
int finalNum = 0; //numStore converted into an integer
float conv = 0.24926; //Converts analog signal range to PWM transmission range
int ind1, ind2, ind3;
const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink_, FALLING);
  pinMode(CH1, OUTPUT);
  pinMode(CH2, OUTPUT);
  Serial.begin(9600);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");
 

  BTserial.begin(9600);
  Serial.println("BTserial started at 9600");
  //Bluetooth initialization protocol
  BTserial.print("AT");
  delay(1000);
  BTserial.print("AT+CO094A9A83B14FE  ");
  delay(1000);
  BTserial.print("AT+CO094A9A83B14FE  ");
  delay(1000);
  BTserial.print("AT+CO094A9A83B14FE  ");
  delay(1000);
}

void loop()
{
  

  // Read from the Bluetooth module and send to the Arduino Serial Monitor

/*
  if (BTserial.available())
  {
    delay(8);//SYNCHRONIZED STABILITY TIMER
    c = BTserial.read();
    numStore += String(c); //Adds character to numstore
  }
  else
  {
    Serial.flush();
    Serial.print(numStore);
   
      ind1 = numStore.indexOf("{"); //Finds { index
      ind2 = numStore.indexOf(',');  //finds location of first ,
      ind3 = numStore.indexOf("}"); //Finds } index
      strX = numStore.substring(ind1 + 1, ind2); //captures first data String
      strY = numStore.substring(ind2 + 1, ind3); //captures second data String
      x = strX.toInt();
      y = strY.toInt();
   
    numStore = " ";
  }
  */

  // Echo the user input to the main window.
  // If there is a new line print the ">" character.
  if (NL) {
    Serial.print("\r\n>");
    NL = false;
  }
  Serial.write(c);
  if (c == 10) {
    NL = true;
  }
}


void blink_() {
  state = !state;
  Serial.println("BLINK");
  digitalWrite(ledPin,state);
  delay(200);
}
