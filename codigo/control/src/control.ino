#include <Servo.h>

#include "config.h"

Servo servGrip,servLeft,servRight,servRot;

void setup() {
  servRot.attach(PinServRot);
  servLeft.attach(PinServLeft);
  servRight.attach(PinServRight);
  servGrip.attach(PinServGrip);

  Serial.begin(9600);

}


// all the value between 0 and 1023
void setPos(int rot,int g,int l, int r){
  servGrip.writeMicroseconds(map(g,MinControl,MaxControl,MinGrip,MaxGrip));
  servLeft.writeMicroseconds(map(l,MinControl,MaxControl,MinLeft,MaxLeft));
  servRight.writeMicroseconds(map(r,MinControl,MaxControl,MinRight,MaxRight));
  servRot.writeMicroseconds(map(rot,MinControl,MaxControl,MinRot,MaxRot));
  Serial.println(String("r:")+r+" g:"+g+" l:"+l+" r:"+r);
}


void loop() {
  setPos( analogRead(PinControlRot), // Pot 1
          analogRead(PinControlGrip), // Pot 2
          analogRead(PinControlLeft),  // Joystick X
          analogRead(PinControlRight)); // Joystick Y
}
