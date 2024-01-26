/**************************************************************************/
/*!
    @file     MyDelay.h
    @author   Marshall G Gates

    
    
	@section LICENSE

    The MIT License (MIT)

	Copyright (c) 2020 Marshall G Gates

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.

  Based on noDelay library by Mario Avenoso of mtechcreations.com
  http://mario.mtechcreations.com/programing/nodelay-arduino-library/
*/
/**************************************************************************/

#ifndef _MyDelay_h_
#define _MyDelay_h_
#define MYDELAY_REPEAT_FOREVER -1

typedef void (*funTocall)(void);

/**
 * Implement a "delay" with the mills() call.
 * Must call update method in the main loop
 * Must have a delay
 * Can have a callback function to be called when timere expires
 * Can have a repeat count
 * 
 */
class MyDelay {
  public:
    MyDelay(void);
    MyDelay(unsigned long dtime);
    MyDelay(unsigned long dtime, funTocall funcall);
    MyDelay(unsigned long dtime, funTocall funcall, int repeatCount);


    void setDelay(unsigned long);
    void setCallback(funTocall);
    void setRepeat(int);
    bool update();
    bool isRunning();

    /**
     * Start the timer
     */
    void start();
    void stop();

  private:
    unsigned long _preMills, _curMills, _delaytime = 0L;
    int _initialRepeatCount = MYDELAY_REPEAT_FOREVER;
    int _currentRepeatCount = 0;
    funTocall _funcall;
    bool _useFunction = false;
    bool _running = false;
    bool _repeating = false;
};

#endif

