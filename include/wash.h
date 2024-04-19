#pragma once
#include "variables.h"

int motontime = 4000;//motor on time during wash
int motofftime = 2000;// motor off time during wash
int washcycle = 60;//no of wash cycles . this determines wash time
unsigned long washdelayt = ((motontime*2)+(motofftime*2));//total wash delay is calclated by adding on and off times
const int long motdelay1 = washdelayt - motontime;//12-4=8
const int long motdelay2 = motdelay1- motofftime;//8-2=6
const int long motdelay3 = motdelay2 -motontime;//6-4=2
const int long motdelay4 = motdelay3 - motofftime;//2-2=0
const int long washpausedelay = 300000;
uint8_t i = 0;
void updatewashdelay(){
  washdelay.start(washdelayt);
  //washpause.start(washpausedelay);
}
void wash(){
  display.showString("WS", 2, 0, 0b01000000);
  int remaining = washdelay.remaining() / 1000;
  //display.showNumber(remaining, 0, 2, 2, 0b00000000);
    if (i <=washcycle){
      iswashing = true;
      if(washdelay.remaining() > motdelay1){
        digitalWrite(motordir,HIGH);
        digitalWrite(motoren,HIGH);
        Serial.println("++++++++++++++++++++++++++++");
      }else if(washdelay.remaining() > motdelay2){
        digitalWrite(motordir,LOW);
        digitalWrite(motoren,LOW);
        Serial.println("00000000000000000000000000000");
      }else if (washdelay.remaining() > motdelay3){
        digitalWrite(motoren,HIGH);
        digitalWrite(motordir,LOW);
        Serial.println("-------------------------");
      }else{
        digitalWrite(motordir,LOW);
        digitalWrite(motoren,LOW);
        Serial.println("oooooooooooooooooooooo");
        if(washdelay.remaining()==motdelay4){
          washdelay.start(washdelayt);
          if(i == (washcycle/2)){
            Serial.println("wash pause"+ String(i));
            washrun.restartDelayed(washpausedelay);
          }
          i++;
        }
      }
    }else{
      washrun.disable();
      i =0;
    }
  }
  void stopwash(){
  digitalWrite(drainmot, LOW);
  digitalWrite(motoren, LOW);
  digitalWrite(motordir, LOW);
  Serial.println("disabled wash");
  if(aouto == true){
    spinrun.enable();
  }
  i = 0;
}