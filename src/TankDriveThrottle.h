#ifndef tankdrivethrottle_H_	//this defines thank drive throttle for later use
#define tankdrivethrottle_H_	//this defines it as a variable
#include "WPILib.h"	//includes WPILib library

class TankDrive	//stating for later use
{
	public:	//enables incorporation of additional code
		TankDrive(uint32_t,uint32_t);
		void Drive(float,float); //makes the robot drive
		//takes two floating points ie: joystick axes
		void SetThrottle(float);//CONTROLS JOYSTICK SENSITIVITY/topspeed
		void SetSpeed(float);
	private:
		Talon left;
		Talon right;

		float scalespeed;
};
#endif 	//finir
