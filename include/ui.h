#pragma once
#include "variables.h"

char *maninmenu[] = { "WASH", "SPIN",  "WATE"};
int menu = 0;
void readsw(){

  starbutton.update();
  selectbutton.update();
  adjbutton.update();

  if((isspinning == false)&&(iswashing == false)&&(isfilling == false)){
    display.showString("Washing machine", 4, 0);
  }


  if(selectbutton.isDoubleClicked()){
    Serial.println("aouto");
    aouto = true;
    fillrun.enable();
    
  }


  if(adjbutton.isHeld()){
    if((fillrun.isEnabled() == false)&& (spinrun.isEnabled()== false)){
      if(washrun.isEnabled()){
    Serial.println("washing off ");
    washrun.disable();
  }else{
    washrun.enable();
    Serial.println("wash in on");
  }
    } 
}
  if(selectbutton.isHeld()){
    if((washrun.isEnabled() == false)&& (spinrun.isEnabled()== false)){
      if(fillrun.isEnabled()){
      Serial.println("water off");
      fillrun.disable();
    }else{
      Serial.println("water in on");
      fillrun.enable();
    }
    }
  }
  if(starbutton.isHeld()){
    if((washrun.isEnabled() == false)&& (fillrun.isEnabled()== false)){
      if(spinrun.isEnabled()){
      spinrun.disable();
      Serial.println("spin off");
    }else { 
      spinrun.enable();
    }
    }
  }
}


