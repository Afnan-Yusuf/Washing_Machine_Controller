#pragma once
#include "variables.h"
unsigned long int dmdelaytime = 120000;// drain motor wait time before spin
unsigned long int brktime = 7000;// free spin time before breaking
unsigned long int spintime = 180000;//spin time
unsigned long int totalspin= (spintime+dmdelaytime+brktime);// total time of spin process
bool last = false;// flag for if its last spin
void startdelay(){
  dmdelay.start(totalspin);
}

void spin(){
  digitalWrite(drainmot, HIGH);
  bool islidopen = digitalRead(lidsw);
  Serial.println(dmdelay.remaining());
  if(dmdelay.remaining()  == 0){
        spinrun.disable();
      }else if(dmdelay.remaining() < brktime){
        Serial.print("motoff");
        digitalWrite(motoren, LOW);
        digitalWrite(motordir, LOW);
  } else if(dmdelay.remaining() < spintime+brktime){
    digitalWrite(drainmot, HIGH);
    digitalWrite(motoren, HIGH);
    digitalWrite(motordir, HIGH);
    Serial.print("moton");
  }
    
  
}

void stopspin(){
  digitalWrite(drainmot, LOW);
    digitalWrite(motoren, LOW);
    digitalWrite(motordir, LOW);
    if(aouto == true && last == false ){
      fillrun.enable();
      last = true;
    }
  
  Serial.println("spin timeout");
}