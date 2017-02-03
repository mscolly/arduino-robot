#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_TIMECRITICAL
#define _TASK_PRIORITY
#include <TaskScheduler.h>

#include "globals.h"

#define PING_PERIOD       200  // 5 times per second
#define GYRO_PERIOD       10  // potentially 1 kHz if the board can handle it
#define ACCEL_PERIOD      100  // 5 times per second
#define MOVE_PERIOD       50 // 20 times per second
#define MOVECHK_PERIOD    500 // 2 times per second
#define SLOW_BLINK        500  // half second
#define FAST_BLINK        250  // 4 times per second
#define SUPERFAST_BLINK   100  // 10 times per second
#define LASER_STROBE      50  // was 100
#define LASER_STROBES     10
#define CALIBRATE_CYCLES  (5000/GYRO_PERIOD)

// Tasks
// gyroManager is a higher priority scheduler
// taskManager is a base scheduler

extern boolean obstructed();
extern void ledRedOn();
extern void ledYellowOn();
extern void ledGreenOn();
extern void ledRedOff();
extern void ledYellowOff();
extern void ledGreenOff();

Scheduler taskManager, gyroManager;

void mPingCallback();
void gyroCalibrate();
void accelCallback();
void moveCallback();
void moveCheckCallback();
void blinkRedOn();
void blinkYellowOn();
void blinkGreenOn();

Task tDistance (PING_PERIOD, TASK_FOREVER, &mPingCallback );
Task tGyro (GYRO_PERIOD, CALIBRATE_CYCLES, &gyroCalibrate );
Task tAccel (ACCEL_PERIOD, TASK_FOREVER, &accelCallback);
Task tMove (MOVE_PERIOD, TASK_FOREVER, &moveCallback );
Task tMoveCheck (MOVECHK_PERIOD, TASK_FOREVER, &moveCheckCallback);
Task tBlinkRed (FAST_BLINK, TASK_FOREVER, &blinkRedOn );
Task tBlinkYellow (SLOW_BLINK, TASK_FOREVER, &blinkYellowOn );
Task tBlinkGreen (SLOW_BLINK, TASK_FOREVER, &blinkGreenOn );
// Task tError (TASK_SECOND, TASK_FOREVER, &errorCallback);

void mPingCallback() {
    if ( obstructed() ) tDistance.delay(10);
}

#ifdef _DEBUG_
unsigned long counter = 0;
void displayCallback() {
    if (counter++ % 40 == 0) {
        Serial.println("obstacle, distance, angle");
    }
    Serial.print(obstacle); Serial.print(",");
    Serial.print(pingDistance); Serial.print(",");
    Serial.print(currentAngle); Serial.print(",");
    Serial.println("");
}

// Task tDisplay (SECOND, TASK_FOREVER, &displayCallback );
Task tDisplay (TASK_SECOND, TASK_FOREVER, &displayCallback );
#endif

void blinkRedOff () {
    ledRedOff();
    tBlinkRed.setCallback(&blinkRedOn);
}

void blinkYellowOff () {
    ledYellowOff();
    tBlinkYellow.setCallback(&blinkYellowOn);
}

void blinkGreenOff () {
    ledGreenOff();
    tBlinkGreen.setCallback(&blinkGreenOn);
}

void blinkRedOn () {
    ledRedOn();
    tBlinkRed.setCallback(&blinkRedOff);
}

void blinkYellowOn () {
    ledYellowOn();
    tBlinkYellow.setCallback(&blinkYellowOff);
}

void blinkGreenOn () {
    ledGreenOn();
    tBlinkGreen.setCallback(&blinkGreenOff);
}

void init_tasks() {
//  taskManager.init();

    gyroManager.addTask(tGyro);
    gyroManager.addTask(tAccel);

    taskManager.addTask(tDistance);
    taskManager.addTask(tMove);
    taskManager.addTask(tMoveCheck);
    taskManager.addTask(tBlinkRed);
    taskManager.addTask(tBlinkYellow);
    taskManager.addTask(tBlinkGreen);
//  taskManager.addTask(tError);

    taskManager.setHighPriorityScheduler(&gyroManager);

//  taskManager.allowSleep(false);
#ifdef _DEBUG_
    taskManager.addTask(tDisplay);
#endif

    tAccel.enable();
    tGyro.enable();
}

void execute_tasks() {
    taskManager.execute();
}
