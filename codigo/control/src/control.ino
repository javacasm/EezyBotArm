#include <Servo.h>


#include "config.h"

// Control of EEZyBotArm MK1 using 2 pots and a joystick

Servo servGrip,servLeft,servRight,servRot;

void setup() {
  servRot.attach(PinServRot);
  servLeft.attach(PinServLeft);
  servRight.attach(PinServRight);
  servGrip.attach(PinServGrip);

  Serial.begin(9600);

}

#define Min_Step 2

int sign(int value) {
 return (value>0)-(value<0);
}

void move(Servo s,int pinServ,int origin,int end){

  int step=sign(end-origin)*Min_Step;

  if(origin==end)
  {
    Serial.println("quiet");
    return;
  }
  if(step<Min_Step)
  {
    Serial.println("almost quiet");
  }
  if (step==0)
  {
    Serial.println("Error: step=0");
    return;
  }
//  s.attach(pinServ);
//  delay(50);
Serial.println(String(origin)+" > "+end+" by "+step);
  for(;abs(end-origin)<Min_Step;origin+=step){
      s.writeMicroseconds(origin);
      delay(10);
      //Serial.println(origin);
  }
  s.writeMicroseconds(end);
  delay(10);
  //s.detach();
}

int realG=(MaxGrip-MinGrip)/2;
int realLeft=(MaxLeft-MinLeft)/2;
int realRight=(MaxRight-MinRight)/2;
int realRot=(MaxRot-MinRot)/2;
// all the value between 0 and 1023
void setPos(int rot,int g,int l, int r){
  int newG=map(g,MinControl,MaxControl,MinGrip,MaxGrip);
  move(servGrip,PinControlGrip,realG,newG);
  realG=newG;

  int newLeft=map(l,MinControl,MaxControl,MinLeft,MaxLeft);
  move(servLeft,PinControlLeft, realLeft,newLeft);
  realLeft=newLeft;

  int newRight=map(r,MinControl,MaxControl,MinRight,MaxRight);
  move(servRight,PinControlRight,realRight,newRight);
  realRight=newRight;

  int newRot=map(rot,MinControl,MaxControl,MinRot,MaxRot);
  move(servRot,PinControlRot,realRot,newRot);
  realRot=newRot;

  Serial.println(String("r:")+r+" g:"+g+" l:"+l+" r:"+r);
}


void loop() {
  setPos( analogRead(PinControlRot), // Pot 1
          analogRead(PinControlGrip), // Pot 2
          analogRead(PinControlLeft),  // Joystick X
          analogRead(PinControlRight)); // Joystick Y
}
