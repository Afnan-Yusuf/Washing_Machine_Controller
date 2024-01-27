#pragma once
#include <TaskScheduler.h>
#include "SevSegShift.h"
#include <PushButton.h>
#include <millisDelay.h>

#define SHIFT_PIN_DS   13 /* Data input PIN */
#define SHIFT_PIN_STCP 12 /* Shift Register Storage PIN */
#define SHIFT_PIN_SHCP 11 /* Shift Register Shift PIN */
SevSegShift sevseg(SHIFT_PIN_DS, SHIFT_PIN_SHCP, SHIFT_PIN_STCP); //Instantiate a seven segment controller object
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
PushButton starbutton(startsw);
PushButton selectbutton(selectsw);
PushButton adjbutton(adjsw);
char *maninmenu[] = { "WASH", "SPIN",  "WATE"};
int menu = 0;

bool aouto = false;// if in aouto mode
bool last = false;// flag for if its last spin
int motontime = 4000;//motor on time during wash
int motofftime = 2000;// motor off time during wash
int washcycle = 60;//no of wash cycles . this determines wash time
uint8_t i = 0;
unsigned long int dmdelaytime = 120000;// drain motor wait time before spin
unsigned long int brktime = 7000;// free spin time before breaking
unsigned long int spintime = 180000;//spin time
unsigned long int totalspin= (spintime+dmdelaytime+brktime);// total time of spin process
unsigned long int filltime = 720000;//max time limit for water in
millisDelay dmdelay;
millisDelay washdelay;
millisDelay filldelay;
millisDelay washpause;
unsigned long washdelayt = ((motontime*2)+(motofftime*2));//total wash delay is calclated by adding on and off times
const int long motdelay1 = washdelayt - motontime;//12-4=8
const int long motdelay2 = motdelay1- motofftime;//8-2=6
const int long motdelay3 = motdelay2 -motontime;//6-4=2
const int long motdelay4 = motdelay3 - motofftime;//2-2=0
const int long washpausedelay = 300000;

void wash();
void readsw();
void spin();
void fill();
void stopfill();
void stopspin();
void stopwash();
void updatewashdelay();
void filltimer();
void startdelay();

Scheduler ts;
uint8_t count = 0;
Task spinrun(TASK_IMMEDIATE, TASK_FOREVER, &spin, &ts, false, &startdelay, &stopspin);
Task fillrun(TASK_IMMEDIATE, TASK_FOREVER, &fill, &ts, false, &filltimer ,&stopfill);
Task washrun(TASK_IMMEDIATE, TASK_FOREVER, &wash, &ts, false, &updatewashdelay, &stopwash);
Task readui(TASK_IMMEDIATE, TASK_FOREVER, &readsw, &ts, false);