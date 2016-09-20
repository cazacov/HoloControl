// Arduino Mini pinout
// https://cdn.sparkfun.com/datasheets/Dev/Arduino/Boards/ProMini8MHzv1.pdf

// Bluefruit EZ-Key pinout
// https://learn.adafruit.com/introducing-bluefruit-ez-key-diy-bluetooth-hid-keyboard/pinouts

// Wii nunchuk pinout
// https://oscarliang.com/wii-nunchuck-arduino-tutorial/

// Wii Nunchuck connection
// GND -> GND Arduino
// PWR -> VCC
// SDA (data)  -> A4
// SCL (clock) -> A5

// EZ-Key connection
// Grounds -> GND
// 3V -> VCC
// RX -> 11 (digital)

#include <Wire.h>
#include "WiiChuck.h"
#include <SoftwareSerial.h>

WiiChuck chuck = WiiChuck();
SoftwareSerial bt(3, 11); // RX, TX

// Arduino IDE settings:
// Tools->Board: "Arduino Pro or Pro Mini"
// Tools->Processor: "ATmega328 (3.3V, 8MHz)

void setup() {
  Serial.begin(9600);   // be sure that 8MHz board is selected in Arduino IDE
  bt.begin(9600);       // otherwise the transfer speed will be wrong
  chuck.begin();
  chuck.update();
}

uint8_t lastSent[6] = {0,0,0,0,0,0};

// the loop function runs over and over again forever
void loop() {
  delay(20);
  chuck.update(); 

  uint8_t keyFlags[6] = {0,0,0,0,0,0};
  short keysPressed = 0;

  // USB HID codes
  // http://www.freebsddiary.org/APC/usb_hid_usages.php

  // Set USB HID flags
  if (chuck.buttonZ)
  {
    keyFlags[keysPressed++] = 0x28; // Keyboard Return (ENTER)
  }
  if (chuck.buttonC)
  {
    keyFlags[keysPressed++] = 0x29;  // Keyboard ESCAPE
  }
  if (chuck.readJoyX() < -60)
  {
    keyFlags[keysPressed++] = 0x04; // Keyboard a and A
  }
  if (chuck.readJoyX() > 60)
  {
    keyFlags[keysPressed++] = 0x07; // Keyboard d and D
  }
  if (chuck.readJoyY() < -60)
  {
    keyFlags[keysPressed++] = 0x16; //Keyboard s and S
  }
  if (chuck.readJoyY() > 60)
  {
    keyFlags[keysPressed++] = 0x1A;  // Keyboard w and W
  }

  // add trailing 0
  while (keysPressed < 6)
  {
    keyFlags[keysPressed++] = 0;
  }

  // Check if keys state changed sicne last transfer
  bool flagsChanged = false;
  for (short i = 0; i < 6; i++)
  {
    if (lastSent[i] != keyFlags[i])
    {
      flagsChanged = true;
    }
  }

  if (flagsChanged) {
    uint8_t modifiers = 0;
    
    bt.write(0xFD);         // HID report
    bt.write(modifiers);    // modifiers
    bt.write((byte)0x00);   // reserved  
    bt.write(keyFlags[0]);  // key code #1
    bt.write(keyFlags[1]);  // key code #2
    bt.write(keyFlags[2]);  // key code #3
    bt.write(keyFlags[3]);  // key code #4
    bt.write(keyFlags[4]);  // key code #5
    bt.write(keyFlags[5]);  // key code #6

    for (short i = 0; i< 6; i++)
    {
      lastSent[i] = keyFlags[i];
      Serial.print(keyFlags[i]);
      Serial.print(",");
    }
    Serial.println();
  }
}
