#pragma once
#include "variables.h"

void readsw()
{
  starbutton.update();
  selectbutton.update();
  adjbutton.update();
  if (selectbutton.isDoubleClicked())
  {
    aouto = true;
    fillrun.enable();
  }
  if (adjbutton.isHeld())
  {
    if ((fillrun.isEnabled() == false) && (spinrun.isEnabled() == false))
    {
      if (washrun.isEnabled())
      {
        washrun.disable();
      }
      else
      {
        washrun.enable();
      }
    }
  }
  if (selectbutton.isHeld())
  {
    if ((washrun.isEnabled() == false) && (spinrun.isEnabled() == false))
    {
      if (fillrun.isEnabled())
      {
        fillrun.disable();
      }
      else
      {
        fillrun.enable();
      }
    }
  }
  if (starbutton.isHeld())
  {
    if ((washrun.isEnabled() == false) && (fillrun.isEnabled() == false))
    {
      if (spinrun.isEnabled())
      {
        spinrun.disable();
      }
      else
      {
        spinrun.enable();
      }
    }
  }
}