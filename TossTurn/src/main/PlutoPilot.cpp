/*Do not remove the include below*/
#include "PlutoPilot.h"
#include "Control.h"
#include "Estimate.h"
#include "Sensor.h"
#include "Motor.h"
#include "Utils.h"
#include "User.h"
int16_t angle;
#define ABS(x) ((x) > 0 ? (x) : -(x))
/*The setup function is called once at Pluto's hardware startup*/
void plutoInit()
{
/*Add your hardware initialization code here*/
Motor.initReversibleMotors();
}
/*The function is called once before plutoLoop when you activate Developer
Mode*/
void onLoopStart()
{
/*do your one time tasks here*/
LED.flightStatus(DEACTIVATE); /*Disable default LED Behaviour*/
/*Reverse the motor direction*/
Motor.setDirection(M1, ANTICLOCK_WISE);
Motor.setDirection(M2, CLOCK_WISE);
Motor.setDirection(M3, ANTICLOCK_WISE);
Motor.setDirection(M4, CLOCK_WISE);
}
/*The loop function is called in an endless loop*/
void plutoLoop()
{
/*Add your repeated code here*/
if(Acceleration.getNetAcc()<2&&(!ABS(angle)>800)&&(!FlightStatus.check(FS_CRASHED)))
/*Condition for free fall*/
{
Command.arm(); /*Arm the drone*/
LED.set(RED, ON);
LED.set(GREEN, ON);
}
/*Add your repeated code here*/
angle=Angle.get(AG_ROLL); /*read current angle value*/
Monitor.println("Angle: ", angle);
if(!FlightStatus.check(FS_ARMED)) /*check if drone is armed*/
{
if (ABS(angle)>800) /*checks if the inverted*/
{
/*set the motor input to max*/
Motor.set(M1, 2000);
Motor.set(M2, 2000);
}
else
{
Motor.set(M1, 1000);
Motor.set(M2, 1000);
Motor.set(M3, 1000);
Motor.set(M4, 1000);
}
}
}
/*The function is called once after plutoLoop when you deactivate Developer
Mode*/
void onLoopFinish()
{
/*do your cleanup tasks here*/
LED.flightStatus(ACTIVATE); /*Enable the default LED behavior*/
/*set motor value to default*/
Motor.set(M1, 1000);
Motor.set(M2, 1000);
Motor.set(M3, 1000);
Motor.set(M4, 1000);
/*set motor directions to default*/
Motor.setDirection(M1, CLOCK_WISE);
Motor.setDirection(M2, ANTICLOCK_WISE);
Motor.setDirection(M3, CLOCK_WISE);
Motor.setDirection(M4, ANTICLOCK_WISE);
}
