

#include "TankDriveThrottle.h"	// includes tank drive in this code
#include "WPILib.h"	//includes WPILib bibrary 
TankDrive::TankDrive(uint32_t leftchannel, uint32_t rightchannel):
	left(leftchannel),
	right(rightchannel)
	{
	scalespeed=0;
	}
void TankDrive::Drive(float leftstick,float rightstick)
{
	left.Set(-1.0*leftstick*scalespeed); //left is now set to left
	right.Set(-1.0*rightstick*scalespeed/(-1));//right now goes right, -1 has significance because it discerns
	//different movements of the joysticks to have differrent movements of the robot
}
void TankDrive::SetThrottle(float othrottle)//adjusts the throttle to a no throttle value
{
	scalespeed=0.5*(1.0-othrottle); //we created a throttle that used to have values 0f -1 to 1 to now just 0 to 1
}
void TankDrive::SetSpeed(float throttle)
{
	scalespeed= -throttle;
}

