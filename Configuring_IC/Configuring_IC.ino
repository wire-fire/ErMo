//12-4-23 11:43AM
//Making OLED work with IC to make debugging easier
//Jack (wire-fire) McTasney

/* CRUCIAL COMMANDS FOR OLED COMMS:
display.clearDisplay(); // Clear display buffer
display.display(); //Displays whatever you've drawn into the buffer
display.setTextSize(1);             // Normal 1:1 pixel scale font size
display.setTextColor(SSD1306_WHITE);        // Draw white text
display.setCursor(0,0);             // Start at top-left corner (128x64 display lol)
display.println(F("Hello, world!")); //Prints Hello, world!
THIS CONCLUDES CRUCIAL COMMANDS FOR OLED COMMS */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// SETTING UP OLED:
// On an arduino UNO:    A4(SDA), A5(SCL)
#define DEBUG_LED 10 //debug LED pin for IC
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // Check back of OLED for this!
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  pinMode(DEBUG_LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  display.setTextSize(1);             // Normal 1:1 pixel scale font size
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  for (int i=0;i<=100;i+=10){
      display.setCursor(i,0);
      display.print("H");
      display.display();
      delay(100);
      digitalWrite(DEBUG_LED,HIGH);
  }
  display.clearDisplay();
  for (int i=100;i>=0;i-=10){
      display.setCursor(i,0);
      display.print("E");
      display.display();
      delay(100);
      digitalWrite(DEBUG_LED,LOW);
  }
  display.clearDisplay();

}
