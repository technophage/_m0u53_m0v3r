/**

ATTiny85 (Digispark) mouse mover

--[ USB IDENTIFIER MODIFICATION ]-----

edit \packages\digistump\hardware\avr\1.7.5\libraries\DigisparkMouse\usbconfig.h
USB_CFG_VENDOR_ID
USB_CFG_DEVICE_ID

to change vendor/device IDs 

reverse byte order - ie 
corsair VID == 1b1c -> 0x1c, 0x1b
darkcore PID == 1b2d ->  0x2d, 0x1b

USB lookup DB
https://the-sz.com/products/usbid/index.php

------

**/


#include <DigiMouse.h>

void setup(){

  DigiMouse.begin();
  pinMode(1, OUTPUT);
}

long neg(long arg){

  return -arg;
}

void loop() {

  // configuration
  // time bounds (msec)
  long delayTime_min = 12345;
  long delayTime_max = 78910;

  // move px distance
  long pxMove_mn = 1;
  long pxMove_mx = 5;

  long delayTime, move;

  while(true) {

    delayTime = random(delayTime_min, delayTime_max); // bounded delay
    move = random(pxMove_mn, pxMove_mx);              // bounded move
    
    digitalWrite(1, HIGH);                            // LED on
    
    if (random(0,1)){
            DigiMouse.moveX(move);
            DigiMouse.delay(random(50, 100));
            DigiMouse.moveX(neg(move));
    } else {
            DigiMouse.moveY(move);
            DigiMouse.delay(random(50, 100));
            DigiMouse.moveY(neg(move));
    }

    digitalWrite(1, LOW);                             // LED off

    DigiMouse.delay(delayTime);                       // sleep
  }
}

// @=X