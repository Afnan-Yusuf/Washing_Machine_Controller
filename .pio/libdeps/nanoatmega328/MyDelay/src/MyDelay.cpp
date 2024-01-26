/**************************************************************************/
/*!
    @file     MyDelay.cpp
    @author   Marshall G. Gates
    @license  MIT (see license.txt)

    Library for using Arduino's mills function without all the setup

    @section  HISTORY

    v1.0 - First release
*/
/**************************************************************************/

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "MyDelay.h"

/*========================================================================*/
/*                            CONSTRUCTORS                                */
/*========================================================================*/

/**************************************************************************/
/*!
    Constructor
*/
/**************************************************************************/
MyDelay::MyDelay(void) {
  this->_preMills = 0;
  this->setDelay(0);
}

MyDelay::MyDelay(unsigned long dtime) {
  this->_preMills = 0;
  this->setDelay(dtime);
}

MyDelay::MyDelay(unsigned long dtime, funTocall funcall) {
  this->_preMills = 0;
  this->setDelay(dtime);
  this->setCallback(funcall);
}

MyDelay::MyDelay(unsigned long dtime, funTocall funcall, int repeatCount) {
  this->_preMills = 0;
  this->setDelay(dtime);
  this->setCallback(funcall);
  this->setRepeat(repeatCount);
}

/*========================================================================*/
/*                           PUBLIC FUNCTIONS                             */
/*========================================================================*/

/**************************************************************************/
/*!
     @brief  Sets the amount of time the delay should wait before
				    the next update
     
     @params[in] dtime
     Time in miliseconds to wait
     
*/
/**************************************************************************/
void MyDelay::setDelay(unsigned long dtime) {
  this->_delaytime = dtime;
}

/**************************************************************************/
/*!
     @brief  Sets the callback function to execute when the timer has
            expired
     
     @params[in] funcall
     Function to call
     
*/
/**************************************************************************/
void MyDelay::setCallback(funTocall funcall) {
  if (funcall != 0) {
    this->_funcall = funcall;
    this->_useFunction = true;
  } else {
    this->_useFunction = false;
  }
}

/**************************************************************************/
/*!
     @brief  Sets the repeat count for the timer.  It will fire this many
            times then stop running
     
     @params[in] repeatCount
     Number of times to fire
     
*/
/**************************************************************************/
void MyDelay::setRepeat(int repeatCount) {
  this->_initialRepeatCount = repeatCount;
  this->_currentRepeatCount = repeatCount;
  this->_repeating = true;
}

/*!
     @brief  Used to restart the elapsed Time to 0.
            Allows you to better time when delays happen as the 0 time
			      happens when this is called     
     
*/
/**************************************************************************/
void MyDelay::start() {
  this->_preMills = millis();
  this->_currentRepeatCount = this->_initialRepeatCount;
  this->_running = true;
}

/*!
     @brief  Used to stop the timer from running
            Allows you to better time when delays happen a     
     
*/
/**************************************************************************/
void MyDelay::stop() {
  this->_preMills = 0;
  this->_running = false;
}

/**************************************************************************/
/*!
     @brief  Checks to see is delay time has expired and can then run code
	 Will run function call if one was used  Also manages repeat count, if any
     
     @returns boot: true if timer has expired, false if not 
*/
/**************************************************************************/
bool MyDelay::update() {
  if (this->_running) {
    this->_curMills = millis();
    if (this->_curMills - this->_preMills >= this->_delaytime) {
      if (this->_repeating) {
        if (this->_initialRepeatCount != MYDELAY_REPEAT_FOREVER) {
          this->_currentRepeatCount--;
          if (this->_currentRepeatCount == 0) {
            this->stop();
          }
        }
      }
      this->_preMills = this->_curMills;
      if (this->_useFunction == true) {
        this->_funcall();
        return true;
      } else {
        return true;
      }
    } else  {
      return false;
    }
  } else {
    return false;
  }
}

/*!
     @brief  Checks to see if the timer is running.
            
      @returns boot: true if timer is running false if not    
*/
/**************************************************************************/
bool MyDelay::isRunning() {
  return this->_running;
}

