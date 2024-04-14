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
  }

void stopfill(){
  digitalWrite(inletsol,LOW);
  isfilling = false;
  Serial.println("water off");
  if(aouto == true){
    washrun.enableDelayed(2000);
  }
}