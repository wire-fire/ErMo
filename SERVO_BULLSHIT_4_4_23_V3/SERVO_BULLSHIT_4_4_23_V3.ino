const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;
String test = "";
 char c;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink_, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:

}


void blink_() {
  state = !state;
  //Serial.println("I AM HERE");
  if (c == '}') {
    Serial.print(test);
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

    /*
      if (c=='}'&&test.length()>5)
      {
       Serial.print(test);
       test=="";
      }
    */




    digitalWrite(ledPin, state);
  }
