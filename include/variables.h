#pragma once
#include <TaskScheduler.h>
#include <PushButton.h>
#include <millisDelay.h>
#include <TM1637TinyDisplay.h>

#define motoren 9 // motor power relay
#define motordir 8 // motor direction selecter
#define drainmot 10// drain motor pin
#define inletsol 7// water in solenoid
#define lidsw 5// door switch
#define startsw 2//start sw
#define adjsw 4// adj sw
#define selectsw  3// select sw
bool iswashing = false;// true if washing 
bool isspinning = false;// ture if spinning
bool isfilling = false;//true if water in on
bool aouto = false;// if in aouto mode

PushButton starbutton(startsw);
PushButton selectbutton(selectsw);
PushButton adjbutton(adjsw);

millisDelay dmdelay;
millisDelay washdelay;
millisDelay filldelay;
millisDelay washpause;

void wash();
void readsw();
void spin();
void fill();
void stopfill();
void stopspin();
void stopwash();
void startdelay();
void updatewashdelay();
void filltimer();

Scheduler ts;
uint8_t count = 0;
Task spinrun(TASK_IMMEDIATE, TASK_FOREVER, &spin, &ts, false, &startdelay, &stopspin);
Task fillrun(TASK_IMMEDIATE, TASK_FOREVER, &fill, &ts, false, &filltimer ,&stopfill);
Task washrun(TASK_IMMEDIATE, TASK_FOREVER, &wash, &ts, false, &updatewashdelay, &stopwash);
Task readui(TASK_IMMEDIATE, TASK_FOREVER, &readsw, &ts, false);