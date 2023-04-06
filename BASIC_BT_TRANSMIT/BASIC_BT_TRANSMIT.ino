#include <AltSoftSerial.h>
AltSoftSerial BTserial;

void setup() {
  // put your setup code here, to run once:
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
  Serial.print("Hello,World\n");
  
  BTserial.print("Hello,World\n");
  delay(50);
}
