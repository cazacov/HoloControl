#include <Wire.h>
#include "WiiChuck.h"

WiiChuck chuck = WiiChuck();

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
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
  if (chuck.zPressed()) {
    Serial.println();
  }
  if (chuck.cPressed()) {
    Serial.print("--ESC--");
  }
}
