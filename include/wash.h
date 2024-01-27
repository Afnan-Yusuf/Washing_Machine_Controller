#pragma once
#include "variables.h"
void wash()
{
  if (i <= washcycle)
  {
    iswashing = true;
    if (washdelay.remaining() > motdelay1)
    {
      digitalWrite(motordir, HIGH);
      digitalWrite(motoren, HIGH);
    }
    else if (washdelay.remaining() > motdelay2)
    {
      digitalWrite(motordir, LOW);
      digitalWrite(motoren, LOW);
    }
    else if (washdelay.remaining() > motdelay3)
    {
      digitalWrite(motoren, HIGH);
      digitalWrite(motordir, LOW);
    }
    else
    {
      digitalWrite(motordir, LOW);
      digitalWrite(motoren, LOW);
      if (washdelay.remaining() == motdelay4)
      {
        washdelay.start(washdelayt);
        if (i == (washcycle / 2))
        {
          washrun.restartDelayed(washpausedelay);
        }
        i++;
      }
    }
  }
  else
  {
    washrun.disable();
    i = 0;
  }
}

void updatewashdelay()
{ // on wash enable
  washdelay.start(washdelayt);
  // washpause.start(washpausedelay);
}

void stopwash()
{ // one wash disable
  digitalWrite(drainmot, LOW);
  digitalWrite(motoren, LOW);
  digitalWrite(motordir, LOW);
  if (aouto == true)
  {
    spinrun.enable();
  }
  i = 0;
}