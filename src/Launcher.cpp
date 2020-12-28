#include "WPIlib.h"
#include "Launcher.h"
#include "Constants.h"
#include <math.h>

Launcher::Launcher(uint32_t Rchannel, uint32_t Lchannel, uint32_t push, uint32_t rotate)
:Rshooter(Rchannel), Lshooter(Lchannel), Kicker(push), Rotator(rotate)
 //Lencoder(6,7), Rencoder(8,9)
{
	SetSpeed = 0.0;
	Rspeed = 0.0;
	Lspeed = 0.0;
	difference = 0.0;
}

void Launcher::ForwardKicker()
{
	Kicker.Set(KICKFORWARDSPEED);
}


void Launcher::SetShootSpeed(float Input_Speed)
{
	SetSpeed = SPINDIRECTION*Input_Speed;
	Rspeed = -1.0 *SetSpeed;
	Lspeed = SetSpeed;
	Rshooter.Set(Rspeed);
	Lshooter.Set(Lspeed);
}

float Launcher::RGetShootSpeed()
{
	return Rspeed;
}

float Launcher::LGetShootSpeed()
{
	return Lspeed;
}

void Launcher::StopKicker()
{
	Kicker.Set(0);
}
void Launcher::BackKicker()
{
	Kicker.Set(KICKBACKWARDSPEED);
}

void Launcher::Rotate(float Rvalue)
{
	Rotator.Set(Rvalue);
}

int Launcher::AngleSet(uint32_t Target, uint32_t Value)
{
	EncoderTarget=Target;
	NewSample=Value;
	if (abs(EncoderTarget - NewSample) >= ANGLETOLERANCE)
	{
		TickDifference = EncoderTarget - NewSample;
		SumSample += TickDifference;
						// Proportional
		ProTerm = PROCONSTANT * (EncoderTarget - NewSample);
		IntTerm = INTCONSTANT * SumSample;
		DerTerm = DERCONSTANT * (NewSample - OldSample);
		Power = ProTerm + IntTerm + DerTerm;
		if(Power>1)Power=1;
		else if(Power < -1)Power=-1;
		else if(Power<ANGLEMINSPEED && Power>-1.0*ANGLEMINSPEED) Power=0.0;
		Launcher::Rotate(Power);
		OldSample = NewSample;
	}
	else
	{
		Power=0.0;
		Launcher::Rotate(Power);
	}
	return(TickDifference);
}
void Launcher::AutoShoot() {/* code here*/}


