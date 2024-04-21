#pragma once
#include "variables.h"
unsigned long int filltime = 720000;//max time limit for water in

void filltimer(){
  filldelay.start(filltime);
}



void fill(){
    digitalWrite(inletsol,HIGH);
    Serial.println("water on");
    selectbutton.update();
    Serial.print(filldelay.remaining());
    if(filldelay.remaining() < 1){
      fillrun.disable();
    }
    if(selectbutton.isClicked()){
      fillrun.disable();
    }
    display.showString("IN", 2, 0, 0b01000000);
    int fillremaining = filldelay.remaining() / 1000;
    display.showNumber(fillremaining, 0, 2, 2);


}

void stopfill(){
  digitalWrite(inletsol,LOW);
  isfilling = false;
  Serial.println("water off");
  if(aouto == true){
    washrun.enableDelayed(2000);
  }
}