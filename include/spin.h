#pragma once
#include "variables.h"
void spin()
{
  digitalWrite(drainmot, HIGH);
  bool islidopen = digitalRead(lidsw);
  if (dmdelay.remaining() == 0)
  {
    spinrun.disable();
  }
  else if (dmdelay.remaining() < brktime)
  {
    digitalWrite(motoren, LOW);
    digitalWrite(motordir, LOW);
  }
  else if (dmdelay.remaining() < spintime + brktime)
  {
    digitalWrite(drainmot, HIGH);
    digitalWrite(motoren, HIGH);
    digitalWrite(motordir, HIGH);
  }
}
void startdelay()//on enable of spin
{
  dmdelay.start(totalspin);
}
void stopspin()//on disable of spin
{
  digitalWrite(drainmot, LOW);
  digitalWrite(motoren, LOW);
  digitalWrite(motordir, LOW);
  if (aouto == true && last == false)
  {
    fillrun.enable();
    last = true;
  }
}