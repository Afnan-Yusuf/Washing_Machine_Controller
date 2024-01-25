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
void startdelay(){
  dmdelay.start(totalspin);
}
void updatewashdelay(){
  washdelay.start(washdelayt);
  //washpause.start(washpausedelay);
}
void filltimer(){
  filldelay.start(filltime);
}

Scheduler ts;
uint8_t count = 0;
Task spinrun(TASK_IMMEDIATE, TASK_FOREVER, &spin, &ts, false, &startdelay, &stopspin);
Task fillrun(TASK_IMMEDIATE, TASK_FOREVER, &fill, &ts, false, &filltimer ,&stopfill);
Task washrun(TASK_IMMEDIATE, TASK_FOREVER, &wash, &ts, false, &updatewashdelay, &stopwash);
Task readui(TASK_IMMEDIATE, TASK_FOREVER, &readsw, &ts, false);

void wash(){
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

void fill(){
    digitalWrite(inletsol,HIGH);
    Serial.println("water on");
    selectbutton.update();
    Serial.print(filldelay.remaining());
    if(filldelay.remaining() < 1){
      fillrun.disable();
    }
    if(selectbutton.isClicked()){
      fillrun.disable();
    }
  }
void spin(){
  digitalWrite(drainmot, HIGH);
  bool islidopen = digitalRead(lidsw);
  Serial.println(dmdelay.remaining());
  if(dmdelay.remaining()  == 0){
        spinrun.disable();
      }else if(dmdelay.remaining() < brktime){
        Serial.print("motoff");
        digitalWrite(motoren, LOW);
        digitalWrite(motordir, LOW);
  } else if(dmdelay.remaining() < spintime+brktime){
    digitalWrite(drainmot, HIGH);
    digitalWrite(motoren, HIGH);
    digitalWrite(motordir, HIGH);
    Serial.print("moton");
  }
    
  
}
void readsw(){

  starbutton.update();
  selectbutton.update();
  adjbutton.update();
  if((isspinning == false)&&(iswashing == false)&&(isfilling == false)){
    sevseg.setChars(maninmenu[menu]);
  sevseg.refreshDisplay();
  }
  sevseg.setChars(maninmenu[menu]);
  sevseg.refreshDisplay();
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
void stopfill(){
  digitalWrite(inletsol,LOW);
  isfilling = false;
  Serial.println("water off");
  if(aouto == true){
    washrun.enableDelayed(2000);
  }
}
void stopspin(){
  digitalWrite(drainmot, LOW);
    digitalWrite(motoren, LOW);
    digitalWrite(motordir, LOW);
    if(aouto == true && last == false ){
      fillrun.enable();
      last = true;
    }
  
  Serial.println("spin timeout");
}
void setup() {
  pinMode(motoren, OUTPUT);
  pinMode(motordir, OUTPUT);
  pinMode(drainmot, OUTPUT);
  pinMode(inletsol, OUTPUT);
  pinMode(lidsw, INPUT);
  pinMode(startsw, INPUT);
  pinMode(adjsw, INPUT);
  pinMode(selectsw, INPUT);
  digitalWrite(motoren,LOW);
  digitalWrite(motordir,LOW);
  digitalWrite(drainmot,LOW);
  digitalWrite(inletsol,LOW);
  adjbutton.setActiveLogic(HIGH);
  starbutton.setActiveLogic(HIGH);
  selectbutton.setHoldTime(2000);
  selectbutton.setActiveLogic(HIGH); // Set the logic as active LOW, i.e. digital pin is LOW when button is pressed [default: HIGH]
  byte numDigits = 4;
  byte digitPins[] = {8+2, 8+5, 8+6, 2}; // of ShiftRegister(s) | 8+x (2nd Register)
  byte segmentPins[] = {8+3, 8+7, 4, 6, 7, 8+4, 3,  5}; // of Shiftregister(s) | 8+x (2nd Register)
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(0);
  Serial.begin(9600);
  ts.addTask(spinrun);
  ts.addTask(fillrun);
  ts.addTask(washrun);
  ts.addTask(readui);
  readui.enable();

}

void loop() {
  ts.execute();//execute the scheduler
}

