#include "variables.h"
#include "wash.h"
#include "spin.h"
#include "WaterFill.h"
#include "ui.h"
#include <Arduino.h>
void setup()
{
  pinMode(motoren, OUTPUT);
  pinMode(motordir, OUTPUT);
  pinMode(drainmot, OUTPUT);
  pinMode(inletsol, OUTPUT);
  pinMode(lidsw, INPUT);
  pinMode(startsw, INPUT);
  pinMode(adjsw, INPUT);
  pinMode(selectsw, INPUT);
  digitalWrite(motoren, LOW);
  digitalWrite(motordir, LOW);
  digitalWrite(drainmot, LOW);
  digitalWrite(inletsol, LOW);
  adjbutton.setActiveLogic(HIGH);
  starbutton.setActiveLogic(HIGH);
  selectbutton.setHoldTime(2000);
  selectbutton.setActiveLogic(HIGH); // Set the logic as active LOW, i.e. digital pin is LOW when button is pressed [default: HIGH]
  byte numDigits = 4;
  byte digitPins[] = {8 + 2, 8 + 5, 8 + 6, 2};               // of ShiftRegister(s) | 8+x (2nd Register)
  byte segmentPins[] = {8 + 3, 8 + 7, 4, 6, 7, 8 + 4, 3, 5}; // of Shiftregister(s) | 8+x (2nd Register)
  bool resistorsOnSegments = false;                          // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE;                        // See README.md for options
  bool updateWithDelays = false;                             // Default 'false' is Recommended
  bool leadingZeros = false;                                 // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false;                              // Use 'true' if your decimal point doesn't exist or isn't connected
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(0);
  Serial.begin(9600);
  ts.addTask(spinrun);
  ts.addTask(fillrun);
  ts.addTask(washrun);
  ts.addTask(readui);
  readui.enable();
}

void loop()
{
  ts.execute(); // execute the scheduler
}
