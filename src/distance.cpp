//
// ----------------- Distance measurement routines ------------------
//

#include <DirectIO.h>
#include <AvgFilter.h>
#include "pin_numbers.h"

#define PING_OBSTACLE     1000 //  ~20 cm; distance = delay/58.2

extern void laserOn();
extern void laserOff();

Output<TRIGGERPIN>    pTrigger;
Input<ECHOPIN>        pEcho;
Input<IRPIN>          pIrPin;

long pingDistance = 39999;
long mPingFilterd[3];
avgFilter mPingFilter(3, mPingFilterd);
boolean obstacle;


boolean obstructed() {
    unsigned long d;

    laserOn();

    pTrigger = LOW;
    delayMicroseconds(4);
    pTrigger = HIGH;
    delayMicroseconds(10);
    pTrigger = LOW;
    d = pulseIn(ECHOPIN, HIGH, PING_OBSTACLE<<1);

    laserOff();

    pingDistance = mPingFilter.value((d ? d : PING_OBSTACLE<<1));
    return (pingDistance <= PING_OBSTACLE) || (!pIrPin);
}


long longRangePing(unsigned long aTimeout) {
    unsigned long d;

    laserOn();

    pTrigger = LOW;
    delayMicroseconds(4);
    pTrigger = HIGH;
    delayMicroseconds(10);
    pTrigger = LOW;
    d = pulseIn(ECHOPIN, HIGH, aTimeout);

    laserOff();

    return (d ? d : aTimeout);
}
