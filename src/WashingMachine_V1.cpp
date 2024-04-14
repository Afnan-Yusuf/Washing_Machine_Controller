#include "variables.h"
#include "wash.h"
#include "spin.h"
#include "fillwater.h"
#include "ui.h"

void setup() {
  pinMode(motoren, OUTPUT);
  pinMode(motordir, OUTPUT);
  pinMode(drainmot, OUTPUT);
  pinMode(inletsol, OUTPUT);
  pinMode(lidsw, INPUT);
  pinMode(startsw, INPUT);
  pinMode(adjsw, INPUT);
  pinMode(selectsw, INPUT);

  digitalWrite(motoren,LOW);
  digitalWrite(motordir,LOW);
  digitalWrite(drainmot,LOW);
  digitalWrite(inletsol,LOW);

  adjbutton.setActiveLogic(HIGH);
  starbutton.setActiveLogic(HIGH);
  selectbutton.setHoldTime(2000);
  selectbutton.setActiveLogic(HIGH); // Set the logic as active LOW, i.e. digital pin is LOW when button is pressed [default: HIGH]
  
  display.begin();
  display.setBrightness(1);
  display.clear();
  ts.addTask(spinrun);
  ts.addTask(fillrun);
  ts.addTask(washrun);
  ts.addTask(readui);
  readui.enable();

  Serial.begin(9600);
}

void loop() {
  ts.execute();//execute the scheduler
}

