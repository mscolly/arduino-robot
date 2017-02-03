#include <DirectIO.h>
#include "pin_numbers.h"

// PINs for DirectIO

Output<GREENLEDPIN>   pGreenLedPin;
Output<YELLOWLEDPIN>  pYellowLedPin;
Output<REDLEDPIN>     pRedLedPin;
Output<LASERPIN>      pLaserPin;

Output<13>            pLED;

//------------------------- LED CONTROL functions ----------------------

void ledRedOn () {
    pRedLedPin = HIGH;
}
void ledRedOff () {
    pRedLedPin = LOW;
}
void ledYellowOn () {
    pYellowLedPin = HIGH;
}
void ledYellowOff () {
    pYellowLedPin = LOW;
}
void ledGreenOn () {
    pGreenLedPin = HIGH;
}
void ledGreenOff () {
    pGreenLedPin = LOW;
}
void laserOn () {
    pLaserPin = HIGH;
}
void laserOff () {
    pLaserPin = LOW;
}
