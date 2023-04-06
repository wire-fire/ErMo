const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;


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
  char c;
  String test =  "";
  state = !state;
  //Serial.println("I AM HERE");
  while (Serial.available())
  {
    c = Serial.read();
    test+=c;
  }
  Serial.print(test);
  digitalWrite(ledPin,state);
}
