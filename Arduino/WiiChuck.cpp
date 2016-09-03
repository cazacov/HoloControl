#include "WiiChuck.h"
#include "Arduino.h" 
#include <Wire.h>

// these may need to be adjusted for each nunchuck for calibration
#define ZEROX 510  
#define ZEROY 490
#define ZEROZ 460
#define RADIUS 210  // probably pretty universal

#define DEFAULT_ZERO_JOY_X 124
#define DEFAULT_ZERO_JOY_Y 132

void WiiChuck::begin() {

    Wire.begin();
    cnt = 0;
    averageCounter = 0;
    // instead of the common 0x40 -> 0x00 initialization, we
    // use 0xF0 -> 0x55 followed by 0xFB -> 0x00.
    // this lets us use 3rd party nunchucks (like cheap $4 ebay ones)
    // while still letting us use official oness.
    // only side effect is that we no longer need to decode bytes in _nunchuk_decode_byte
    // see http://forum.arduino.cc/index.php?topic=45924#msg333160
    //  
    Wire.beginTransmission(0x52);       // device address
    Wire.write(0xF0);
    Wire.write(0x55);
    Wire.endTransmission();
    delay(1);
    Wire.beginTransmission(0x52);
    Wire.write(0xFB);
    Wire.write(0x00);
    Wire.endTransmission();
    update();            
    for (i = 0; i<3;i++) {
        angles[i] = 0;
    }
    zeroJoyX = DEFAULT_ZERO_JOY_X;
    zeroJoyY = DEFAULT_ZERO_JOY_Y;
}

void WiiChuck::calibrateJoy() {
    zeroJoyX = joyX;
    zeroJoyY = joyY;
}

void WiiChuck::update() {

    Wire.requestFrom (0x52, 6); // request data from nunchuck
    while (Wire.available ()) {
        // receive byte as an integer
        status[cnt] = _nunchuk_decode_byte (Wire.read()); //
        cnt++;
    }
    if (cnt > 5) {
        lastZ = buttonZ;
        lastC = buttonC;
        lastJoyX = readJoyX();
        lastJoyY = readJoyY();
        //averageCounter ++;
        //if (averageCounter >= AVERAGE_N)
        //    averageCounter = 0;

        cnt = 0;
        joyX = (status[0]);
        joyY = (status[1]);
        for (i = 0; i < 3; i++) 
            //accelArray[i][averageCounter] = ((int)status[i+2] << 2) + ((status[5] & (B00000011 << ((i+1)*2) ) >> ((i+1)*2))); 
            angles[i] = (status[i+2] << 2) + ((status[5] & (B00000011 << ((i+1)*2) ) >> ((i+1)*2))); 

        //accelYArray[averageCounter] = ((int)status[3] << 2) + ((status[5] & B00110000) >> 4); 
        //accelZArray[averageCounter] = ((int)status[4] << 2) + ((status[5] & B11000000) >> 6); 

        buttonZ = !( status[5] & B00000001);
        buttonC = !((status[5] & B00000010) >> 1);
        _send_zero(); // send the request for next bytes

    }
}


float WiiChuck::readAccelX() {
   // total = 0; // accelArray[xyz][averageCounter] * FAST_WEIGHT;
    return (float)angles[0] - ZEROX;
}

float WiiChuck::readAccelY() {
    // total = 0; // accelArray[xyz][averageCounter] * FAST_WEIGHT;
    return (float)angles[1] - ZEROY;
}

float WiiChuck::readAccelZ() {
    // total = 0; // accelArray[xyz][averageCounter] * FAST_WEIGHT;
    return (float)angles[2] - ZEROZ;
}

boolean WiiChuck::zPressed() {
    return (buttonZ && ! lastZ);
}

boolean WiiChuck::cPressed() {
    return (buttonC && ! lastC);
}

// for using the joystick like a directional button
boolean WiiChuck::rightJoy(int thresh) {
    return (readJoyX() > thresh and lastJoyX <= thresh);
}

// for using the joystick like a directional button
boolean WiiChuck::leftJoy(int thresh) {
    return (readJoyX() < -thresh and lastJoyX >= -thresh);
}


int WiiChuck::readJoyX() {
    return (int) joyX - zeroJoyX;
}

int WiiChuck::readJoyY() {
    return (int)joyY - zeroJoyY;
}


// R, the radius, generally hovers around 210 (at least it does with mine)
// int R() {
//     return sqrt(readAccelX() * readAccelX() +readAccelY() * readAccelY() + readAccelZ() * readAccelZ());  
// }


// returns roll degrees
int WiiChuck::readRoll() {
    return (int)(atan2(readAccelX(),readAccelZ())/ M_PI * 180.0);
}

// returns pitch in degrees
int WiiChuck::readPitch() {        
    return (int) (acos(readAccelY()/RADIUS)/ M_PI * 180.0);  // optionally swap 'RADIUS' for 'R()'
}

    
byte WiiChuck::_nunchuk_decode_byte (byte x)
{
    //decode is only necessary with certain initializations 
    //x = (x ^ 0x17) + 0x17;
    return x;
}

void WiiChuck::_send_zero()
{
    Wire.beginTransmission (0x52);      // transmit to device 0x52
    Wire.write (0x00);           // sends one byte
    Wire.endTransmission ();    // stop transmitting
}

