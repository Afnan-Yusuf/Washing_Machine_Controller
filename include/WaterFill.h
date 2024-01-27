#pragma once
#include "variables.h"
void fill()
{
  digitalWrite(inletsol, HIGH);
  Serial.println("water on");
  selectbutton.update();
  if (filldelay.remaining() < 1)
  {
    fillrun.disable();
  }
  if (selectbutton.isClicked())
  {
    fillrun.disable();
  }
}
void filltimer()
{
  filldelay.start(filltime);
}
void stopfill()
{
  digitalWrite(inletsol, LOW);
  isfilling = false;
  if (aouto == true)
  {
    washrun.enableDelayed(2000);
  }
}