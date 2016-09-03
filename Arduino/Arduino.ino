#include <Wire.h>
#include "WiiChuck.h"

WiiChuck chuck = WiiChuck();

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(19200);
  chuck.begin();
  chuck.update();
}

// the loop function runs over and over again forever
void loop() {
  delay(20);
  chuck.update(); 

  if (chuck.rightJoy()) {
    Serial.print("d");
  }
  if (chuck.leftJoy()) {
    Serial.print("a");
  }
  if (chuck.upJoy()) {
    Serial.print("w");
  }
  if (chuck.downJoy()) {
    Serial.print("s");
  }
  if (chuck.zPressed()) {
    Serial.print("\0x0A");  // Enter
  }
  if (chuck.cPressed()) {
    Serial.print("\0x1B");  //ESC
  }
}
