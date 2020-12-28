#include "LEDLights.h"
#include "WPILib.h"

LEDLights::LEDLights(uint32_t redch,uint32_t greench,uint32_t bluech):
pwmred(redch),
pwmgreen(greench),
pwmblue(bluech)
{

}
void LEDLights::SetColor(uint32_t name)
{

	switch (name)
	{
	case RED:
		pwmred.Set(1.0);
		pwmgreen.Set(-1.0);
		pwmblue.Set(-1.0);
		break;
	case GREEN:
		pwmred.Set(-1.0);
		pwmgreen.Set(1.0);
		pwmblue.Set(-1.0);
		break;
	case BLUE:
		pwmred.Set(-1.0);
		pwmgreen.Set(-1.0);
		pwmblue.Set(1.0);
		break;
	case YELLOW:
		pwmred.Set(1.0);
		pwmgreen.Set(0.4);
		pwmblue.Set(-1.0);
		break;
	case CYAN:
		pwmred.Set(-1.0);
		pwmgreen.Set(1.0);
		pwmblue.Set(1.0);
		break;
	case WHITE:
		pwmred.Set(1.0);
		pwmgreen.Set(1.0);
		pwmblue.Set(0.8);
		break;
	case PURPLE:
		pwmred.Set(0.8);
		pwmgreen.Set(-1.0);
		pwmblue.Set(1.0);
		break;
	case OFF:
		pwmred.Set(-1.0);
		pwmgreen.Set(-1.0);
		pwmblue.Set(-1.0);
		break;
	}
}

void LEDLights::SetRGB(uint32_t red,uint32_t green,uint32_t blue)
{
	pwmred.Set((red/128.0) -  1);
	pwmgreen.Set((green/128.0) - 1);
	pwmblue.Set((blue/128.0) - 1);
}
