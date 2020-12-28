#pragma once
#include <Constants.h>
#include "WPIlib.h" //Include the FRC Library

class Launcher
{
public:
	Launcher(uint32_t Rchannel, uint32_t Lchannel, uint32_t push, uint32_t rotate);
	void ForwardKicker();					// Move kicker forward
	void SetShootSpeed(float RInput_Speed);	// right speed and left speed
	float RGetShootSpeed();	// get the speed of the right motor
	float LGetShootSpeed();	// get the speed of the left motor
	void StopKicker();			// stop kicker
	void BackKicker();			// reverse kicker
	void Rotate(float Rvalue); //Rotate Shooter Angle. Same as RManual
	void AutoShoot();
//	void ResetEncoders();   //Reset the encoder values
//	void MatchSpeed();		// Read the speeds of the spinners and adjust
	int AngleSet(uint32_t Target, uint32_t Value); //Move from Value to Target with PID
private:
	Talon Rshooter;		// Right motor controller
	Talon Lshooter;		// Left motor controller
	Jaguar Kicker;		// Kicker
	Jaguar Rotator;		// R--R--Rotato
//	Encoder Lencoder;	// Encoder for the left spinner
//	Encoder Rencoder;	// Encoder for the right spinner

	float SetSpeed;	    // Speed that the Robot is set to to at. Rspeed and Lspeed are adjusted so that their average is SetSpeed
	float Rspeed;		// Variable for the speed of the right motor
	float Lspeed;		// Variable for the speed of the left motor
    float difference;   // Used to adjust spinner speed differnce
    /*-----------FOR ENCODERS--------------------*/
    int ACurrentTick = 0;	// angle current tick
    int TickDifference = 0;
    int NewSample = 0;
    int OldSample = 0;
    int SumSample = 0;
    int EncoderTarget = 0;
    float Power = 0.0;
    float ProTerm = 0.0;
    float IntTerm = 0.0;
    float DerTerm = 0.0;
};
