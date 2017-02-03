#include <Arduino.h>
#include <I2Cdev.h>
#include <Wire.h>
#include <MPU6050.h>
#include <avr/sleep.h>
#include <avr/power.h>

#include "globals.h"
#include "pin_numbers.h"

extern void ledRedOn();
extern void ledYellowOn();
extern void ledGreenOn();
extern void laserOn();
extern void ledRedOff();
extern void ledYellowOff();
extern void ledGreenOff();
extern void laserOff();

extern void moveStop();

extern boolean obstacle;
extern int shakeSettleSeconds;

extern void init_tasks();
extern void execute_tasks();

// -------------- Main -----------------

void initPins() {
  pinMode(ECHOPIN, INPUT);
//  pLED = LOW;     // Turn off on-board LED used for overflow indication
}

void setup () {

  initPins();
  
  Wire.begin();       //Initiate the Wire library and join the I2C bus as a master
  randomSeed(analogRead(0));
  
#ifdef _DEBUG_
  Serial.begin(115200);
//  Serial.println(CToken);
#endif

  moveStop();

  ledRedOn();
  ledYellowOn();
  ledGreenOn();
  laserOn();
  
#ifdef _DEBUG_
//  Serial.println("Init move functions");
#endif

  power_adc_disable();
  power_adc_disable();

#ifndef _DEBUG_
  power_usart0_disable();
#endif

//  taskManager.init();

  shakeSettleSeconds = 3;  // Wait for at least three seconds for the robot to be motionless

  delay(2000);

  ledRedOff();
  ledYellowOff();
  ledGreenOff();
  laserOff();

    init_tasks();

  obstacle = false;
}

void loop ()
{
  execute_tasks();
}
