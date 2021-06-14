#include <math.h>

#include "HID.h"
#include "AlphaYokeExtension.h"


void setup() {
  //zero out the joystick state
  Joystick.clearState();
  
  //set pins as input (sparkfun joystick shield config)
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  
  // enable 12-bit analog resolution for Arduino Due
  analogReadResolution(12);

//  Serial.begin(9600);
 }


void loop() {
  //clear
  Joystick.clearState();

  float values[2] = {0.0, 0.0};
  
  //tweak the joystick state (see joystick.h for all possible fields)
  for (int i = 0; i < 50; i++)
  {
    delay(1);
    values[0] += analogRead(A0);
    values[1] += analogRead(A1);
  }
  values[0] /= 50.0;
  values[1] /= 50.0;

  Joystick.state.x.axis = map(values[0], 0, 4095, -32768, 32767);
  Joystick.state.y.axis = map(values[1], 0, 4095, -32768, 32767);
//  Joystick.state.x.axis = map(values[0], 0, 4095, 0, 4095);
//  Joystick.state.y.axis = map(values[1], 0, 4095, 0, 4095);

  /*Serial.println("X: " + String(analogRead(A0)) + " (" + String(map(analogRead(A0), 0, 1023, 0, 4095)) + ") " +
                 "Y: " + String(analogRead(A1)) + " (" + String(map(analogRead(A1), 0, 1023, 0, 4095)) + ")");

  */

  //call send state to pack and send the current state over usb
  Joystick.sendState();
  
  delay(5);
}
