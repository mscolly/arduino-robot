#include <DirectIO.h>
#include "pin_numbers.h"
#include "movements.h"

// PINs for DirectIO

AnalogOutput<M1PIN1>  pM1Pin1;
AnalogOutput<M1PIN2>  pM1Pin2;
AnalogOutput<M2PIN1>  pM2Pin1;
AnalogOutput<M2PIN2>  pM2Pin2;

// ----------------------- Movements --------------------------------

int rightLegSpeed, leftLegSpeed;
int shakeSettleSeconds = 2;

void moveStop() {
  rightLegSpeed = leftLegSpeed =0;
  pM1Pin1 = 0;
  pM1Pin2 = 0;
  pM2Pin1 = 0;
  pM2Pin2 = 0;
}

void moveRightLegsStop() {
  rightLegSpeed = 0;
  pM2Pin1 = 0;
  pM2Pin2 = 0;
}

void moveRightLegsForward(int aSpeed) {
  rightLegSpeed = aSpeed > MOVE_MAXSPEED ? MOVE_MAXSPEED : aSpeed;
  pM2Pin1 = rightLegSpeed;
  pM2Pin2 = 0;
}

void moveRightLegsBack(int aSpeed) {
  rightLegSpeed = aSpeed > MOVE_MAXSPEED ? -MOVE_MAXSPEED : -aSpeed;
  pM2Pin1 = 0;
  pM2Pin2 = -rightLegSpeed;
}

void moveLeftLegsStop() {
  leftLegSpeed = 0;
  pM1Pin1 = 0;
  pM1Pin2 = 0;
}

void moveLeftLegsForward(int aSpeed) {
  leftLegSpeed = aSpeed > MOVE_MAXSPEED ? MOVE_MAXSPEED : aSpeed;
  pM1Pin1 = leftLegSpeed;
  pM1Pin2 = 0;
}

void moveLeftLegsBack(int aSpeed) {
  leftLegSpeed = aSpeed > MOVE_MAXSPEED ? -MOVE_MAXSPEED : -aSpeed;
  pM1Pin1 = 0;
  pM1Pin2 = -leftLegSpeed;
}

void moveForward(int aS1, int aS2) {
  moveLeftLegsForward(aS1);
  moveRightLegsForward(aS2);
}

void moveBack(int aS1, int aS2) {
  moveLeftLegsBack(aS1);
  moveRightLegsBack(aS2);
}

void moveRotateRight(int aS1, int aS2) {
  moveLeftLegsForward(aS1);
  moveRightLegsBack(aS2);
}

void moveRotateLeft(int aS1, int aS2) {
  moveLeftLegsBack(aS2);
  moveRightLegsForward(aS1);
}
