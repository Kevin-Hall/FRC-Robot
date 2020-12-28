#include "Constants.h"
#include "WPIlib.h"
#include "Ultrasonic.h"
#include "Launcher.h"
#include "LEDLights.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <TankDriveThrottle.h>
#include "Vision.h"
//#include <opencv/cv.h>
//using namespace cv;


class Robot: public SampleRobot
{
	private:
		TankDrive tankdrive;
		Joystick rightStick;
		Joystick leftStick;
		Joystick launchStick;
		Timer ShootTimer;
		Launcher launch;
		Talon winch;
		LEDLights leds;
		DigitalInput ballsensor;
		USSensor Usensor;
		Vision camera;
		Encoder AEncoder;
		Encoder LWEncoder;
		Encoder RWEncoder;
		AnalogGyro Gyro;
		SmartDashboard *dash;

		const char *JAVA = "/usr/local/frc/JRE/bin/java";
		char *GRIP_ARGS[5] = { "java", "-jar", "/home/lvuser/grip.jar", "/home/lvuser/project.grip", NULL };
		bool ManualOp = false;
		bool Override = false;
		float shootspeed;
/*-----------FOR ENCODERS--------------------*/
		int EncoderTarget = 0;
/*-------------For Autonomous--------------------*/
		int AutonomousMode = 0;
		int AutoLine = 0;
/*-----------------------------------------------*/
		bool InitRobot = false;
		std::vector<int> Vec;
		bool ball=false;
		enum RobotModes{LowMode, HighMode, StowMode, DefenseMode, PickupMode, WinchMode};
		RobotModes RobotMode;
		enum LauncherStates{Unloaded, Loaded, Shooting, ForwardPosition, MoveBackward};
		LauncherStates LauncherState;
		enum VisionStates{Aim, AutoOn, AutoOff};
		VisionStates VisionState;
	public:
		Robot() :
			tankdrive(0, 1),
			rightStick(0),
			leftStick(1),
			launchStick(2),
			ShootTimer(),
			launch(2,3,5,6),
			winch(4),
			leds(7,8,9),
			ballsensor(6),
			Usensor(1),
			camera(),
			AEncoder(4,5,false,Encoder::EncodingType::k4X),
			LWEncoder(0,1,false,Encoder::EncodingType::k4X),
			RWEncoder(2,3,false,Encoder::EncodingType::k4X),
			Gyro(0),
    		dash()
			{
				dash->init();
				dash->PutString("Version",VERSION);
				RobotMode=StowMode;
				LauncherState=Unloaded;
				shootspeed=0.0;
				LWEncoder.SetDistancePerPulse(0.048175);		//Set distance per pulse so encoders read in Inches
				RWEncoder.SetDistancePerPulse(0.047826);		//Set distance per pulse so encoders read in Inches

			}
	    void RobotInit() override {
//	         Run GRIP in a new process
			 if (fork() == 0) {
	            if (execv(JAVA, GRIP_ARGS) == -1) {
	                perror("Error running GRIP");
	            }
	        }
	    }

		void Autonomous()
		{
//		while(true)
//		{
//			if (camera.GetX() > 90)
//				tankdrive.Drive(0.3, 0.3);
//			else
//				tankdrive.Drive(0.0, 0.0);
//		}
			dash->PutNumber("AutoLine", 0);
			leds.SetColor(CYAN);
			shootspeed=0.0;
			launch.SetShootSpeed(shootspeed);
			launch.Rotate(0.0);
			tankdrive.Drive(0.0,0.0);
			launch.StopKicker();
			winch.Set(0.0);
			LWEncoder.Reset(); RWEncoder.Reset();    //Reset Wheel Encoders
			dash->PutNumber("AutoLine", 1);
			launch.Rotate(INITFASTROTATE);
			Wait(INITFASTWAIT);
			launch.Rotate(INITSLOWROTATE);
			Wait(INITSLOWROTATE);
			launch.Rotate(0.0);
			dash->PutNumber("AutoLine", 2);
			InitRobot = true;
			Gyro.Reset();
			AEncoder.Reset();

			dash->PutNumber("AutoLine", 4);
/*------------------------Add Go to Stow Mode Here ----------------*/
			while(abs(launch.AngleSet(ENCODERSTOW,AEncoder.Get()))>AUTOANGLETOLERANCE)		// Temporary
			{
				Wait(0.01);
			}
			launch.Rotate(0.0);
			dash->PutNumber("AutoLine", 5);
			/*-------------------------Autonomous Modes------------------------------- */

			tankdrive.SetSpeed(1.0);

			if (true/*AutonomousMode == 0*/) 													//Autonomous mode for shooting high
			{
				dash->PutNumber("AutoLine", 6);
				tankdrive.Drive(AUTOSPEED,AUTOSPEED);		//Drives both motors at standard length
				dash->PutNumber("Left Wheel Distance (Inches)", LWEncoder.GetDistance());
				dash->PutNumber("Right Wheel Distance (Inches)", RWEncoder.GetDistance());
				while(((LWEncoder.GetDistance() + RWEncoder.GetDistance()) / 2) <= AUTO0ETOLERANCE1)
				{
					Wait(0.01);
				}

				tankdrive.Drive(AUTOSLOWSPEED, 0.0); 											// Turn Right
				dash->PutNumber("AutoLine", 7);
				dash->PutNumber("Left Wheel Distance (Inches)", LWEncoder.GetDistance());
				dash->PutNumber("Right Wheel Distance (Inches)", RWEncoder.GetDistance());
				while (Gyro.GetAngle() <= AUTOTURNANGLE1)										//When the gyroscope gives a reading below/equal to 45
				{
				    Wait(0.01);
				    dash->PutNumber("Gyro Angle", Gyro.GetAngle());
				}
				tankdrive.Drive(0.0, 0.0);
				dash->PutNumber("AutoLine", 8);

				LWEncoder.Reset(); RWEncoder.Reset();    //Reset Wheel Encoders
				launch.SetShootSpeed(SPINHIGH);			//turn on spinner early so they are ready to shoot
				tankdrive.Drive(AUTOSPEED, AUTOSPEED);
				while(((LWEncoder.GetDistance() + RWEncoder.GetDistance()) / 2) <= AUTO0ETOLERANCE2)
				{
					Wait(0.01);
				}
				tankdrive.Drive(0.0, 0.0);
				dash->PutNumber("AutoLine", 9);

				launch.Rotate(ANGLEROTATE);
				while(camera.GetX() <= 0 || AEncoder.Get() <= ENCODERHIGH)
				{
					Wait(0.01);
				}
				launch.Rotate(0.0);
				dash->PutNumber("AutoLine", 10);

				launch.ForwardKicker();
				Wait(KICKFORWARDTIME);
				launch.StopKicker();
				shootspeed = 0.0;
				launch.SetShootSpeed(shootspeed);
				dash->PutNumber("AutoLine", 11);
				tankdrive.Drive(AUTOSLOWSPEED, 0.0);
				while (Gyro.GetAngle() <= AUTOTURNANGLE2)										//When the gyroscope gives a reading below/equal to 45
				{
					Wait(0.01);
					dash->PutNumber("Gyro Angle", Gyro.GetAngle());
				}
				tankdrive.Drive(0.0, 0.0);
				RWEncoder.Reset(); LWEncoder.Reset();
				tankdrive.Drive(AUTOSPEED, AUTOSPEED);
				while (((LWEncoder.GetDistance() + RWEncoder.GetDistance()) / 2) <= AUTO0ETOLERANCE3)
				{
					Wait(0.01);
				}
				tankdrive.Drive(0.0, 0.0);

			}
			/*else if (true AutonomousMode == 1)



			 */
		}
		void OperatorControl()
		{
			Vec.push_back(9);
			Vec.push_back(6);
			shootspeed=0.0;
			launch.SetShootSpeed(shootspeed);
			launch.Rotate(0.0);
			tankdrive.Drive(0.0,0.0);
			launch.StopKicker();
			leds.SetColor(RED);
			RobotMode=StowMode;
			EncoderTarget=ENCODERSTOW;
			ManualOp=false;
			LauncherState=Unloaded;
			winch.Set(0.0);

			if(!InitRobot)		//If the Angle Encoder was not reset, reset it
			{
				LWEncoder.Reset();
				RWEncoder.Reset();
				Gyro.Reset();
				launch.Rotate(INITFASTROTATE);
				Wait(INITFASTWAIT);
				launch.Rotate(INITSLOWROTATE);
				Wait(INITSLOWROTATE);
				launch.Rotate(0.0);
				AEncoder.Reset();
			}
			InitRobot=false;
			while (IsOperatorControl() && IsEnabled())
			{

				for(int i = 0; i < 10; ++i)
				{
					tankdrive.SetThrottle(rightStick.GetZ());		// read encoders
					tankdrive.Drive(leftStick.GetY(), rightStick.GetY());

/*---------------------------FOR CHANGING MODES-------------------------------------*/
					// LOW MODE
					if(launchStick.GetRawButton(2))    //If launch button 2 is pressed
					{
							RobotMode=LowMode;
							leds.SetColor(YELLOW);   //Make the LEDs yellow
						    winch.Set(0.0);
							EncoderTarget = ENCODERLOW;
							if(!ManualOp)
								launch.SetShootSpeed(shootspeed=SPINLOW);
					}

					// HIGH MODE
					if(launchStick.GetRawButton(3))
					{
							RobotMode=HighMode;
							leds.SetColor(GREEN);	// Sets robot to high mode and turns on Green LEDs
							winch.Set(0.0);
							EncoderTarget = ENCODERHIGH;
							if(!ManualOp)
							{
								shootspeed=SPINHIGH;
								launch.SetShootSpeed(shootspeed);
								Override=false;
							}

					}

					// Go to STOW MODE
					// Go to Stow Mode when in Pickup and Ball picked up and in place
					if(/*(ball && RobotMode==PickupMode) ||*/
							launchStick.GetRawButton(4))	// if button 11 in pushed, do the following:
					{
						leds.SetColor(RED);
						launch.SetShootSpeed(shootspeed=0.0);
					    RobotMode=StowMode;
						winch.Set(0.0);
						EncoderTarget = ENCODERSTOW;
					}

					// DEFENSE MODE
					if(launchStick.GetRawButton(7))
					{
						leds.SetColor(WHITE);
						launch.SetShootSpeed(shootspeed=0.0);
						RobotMode=DefenseMode;
						winch.Set(0.0);
						EncoderTarget = ENCODERDEFENSE;
					}

					// PICKUP MODE
					if(launchStick.GetRawButton(5))
					{
						leds.SetColor(PURPLE);
						RobotMode=PickupMode;
						winch.Set(0.0);
						EncoderTarget = ENCODERPICKUP;
						if(!ManualOp)
							launch.SetShootSpeed(shootspeed=SPINPICKUP);
					}

					// Vision - Aim
					if(launchStick.GetRawButton(6))
						VisionState = Aim;

					//Vision - AutoOn
					if(launchStick.GetRawButton(11))
						VisionState = AutoOn;

					if(launchStick.GetRawButton(10))
						VisionState = AutoOff;

/*--------------------------------FOR VISION MODES-----------------------------------*/
					if(VisionState == Aim)
					{
						if(camera.GetY() >= YVALUEMIN && !(camera.GetY() <= YVALUEMAX))		//greater then min and max
						{
							launch.AngleSet(abs((YVALUEMAX - YVALUEMIN) / 2), camera.GetY());	// PID controller
						}
					}

					// for the Y values checks
					if(camera.GetY() >= YVALUEMIN && camera.GetY() <= YVALUEMAX)
					{
						dash->PutBoolean("UP", true);
						dash->PutBoolean("DOWN", true);
					}
					else if(camera.GetY() >= YVALUEMIN)
						dash->PutBoolean("UP", true);
					else
						dash->PutBoolean("DOWN", true);

					}
				// for the X values checks
					if(camera.GetX() >= XVALUEMIN && camera.GetX() <= XVALUEMAX)
					{
						dash->PutBoolean("LEFT", true);
						dash->PutBoolean("RIGHT", true);
					}
					else if(camera.GetX() >= XVALUEMIN)
						dash->PutBoolean("RIGHT", true);
					else
						dash->PutBoolean("LEFT", true);

/*--------------------------------FOR VISION CHECKING--------------------------------*/

/*--------------------------For Turning on and Off Manual Operation--------------------*/
					// Manual Operation On
					if (launchStick.GetRawButton(9))
					{
						ManualOp = true;                //Turns on manual operation and turns LEDs Blue
						leds.SetColor(BLUE);
					}
					// Manual Operation Off
					if (launchStick.GetRawButton(8))
					{
						ManualOp = false;                //Turns off manual operation and turns LEDs off
						if(RobotMode==LowMode)
						{
							shootspeed=SPINLOW;
							launch.SetShootSpeed(shootspeed);
							EncoderTarget = ENCODERLOW;
							leds.SetColor(YELLOW);
						}
						if(RobotMode==HighMode)
						{
							shootspeed=SPINHIGH;
							launch.SetShootSpeed(shootspeed);
							EncoderTarget = ENCODERHIGH;
							leds.SetColor(GREEN);

						}
						if(RobotMode==PickupMode)
						{
							shootspeed=SPINPICKUP;
							launch.SetShootSpeed(shootspeed);
							EncoderTarget = ENCODERPICKUP;
							leds.SetColor(PURPLE);
						}
						if(RobotMode==StowMode)
						{
							shootspeed=0.0;
							launch.SetShootSpeed(shootspeed);
						    EncoderTarget = ENCODERSTOW;
							leds.SetColor(RED);
						}
						if(RobotMode==DefenseMode)				//V12 Correction
						{
							shootspeed=0.0;
							launch.SetShootSpeed(shootspeed);
						    EncoderTarget = ENCODERDEFENSE;
						    leds.SetColor(WHITE);				//V12 Added fix
						}
					}

/*--------------------------------FOR VISION MODES-----------------------------------*/


/*---------------------------------FOR PUSHER MANAGEMENT-----------------------------*/

/*----------------------------- SHOOTING STATE MACHINE -----------------------------------------*/
					if(launchStick.GetRawButton(1) && (RobotMode==HighMode || RobotMode==LowMode))
					{
						launch.ForwardKicker();		//shoot high
						LauncherState = Shooting;
						ShootTimer.Reset();	ShootTimer.Start();
					}

					// WHEN THE PUSHER REACHES THE FORWARD POSTISION
					if (ShootTimer.Get() >= KICKFORWARDTIME && LauncherState==Shooting) //If the timer is greater than or equal to 2 and the kicker is moving forward, make the kicker wait.
					{
						launch.StopKicker();
						LauncherState=ForwardPosition;
						ShootTimer.Reset();	ShootTimer.Start();
					}

					// WHEN THE PUSHER IS DONE WAITING
					if (ShootTimer.Get() >= KICKWAITTIME && LauncherState==ForwardPosition) //If the timer is greater than or equal to 1.0 and the kicker is in wait mode, make it go in reverse instead
					{
						launch.StopKicker();
						LauncherState=MoveBackward;
						ShootTimer.Reset(); ShootTimer.Start();
					}

					// WHEN THE PUSHER IS BACK IN ITS PLACE
					if (ShootTimer.Get() >= KICKBACKWARDTIME && LauncherState==MoveBackward)  //If the timer is 2 or more and the kicker is in reverse stop the kicker and reset the timer
					{
						launch.StopKicker();
						LauncherState=Unloaded;
						ShootTimer.Reset(); ShootTimer.Stop();

						// Set to Stow Mode after shooting Cycle is done
						RobotMode=StowMode;
						leds.SetColor(RED);
						EncoderTarget = ENCODERSTOW;
						shootspeed=0.0;
						launch.SetShootSpeed(shootspeed);
					}
/*--------------------------------------Spinner and Shoot Angle Management ---------------------------------*/
/* ---------------------------------------FOR LOW OPERATION------------------------------------------------*/
// 					if (!ManualOp && RobotMode == LowMode)      //V12 Removed Empty If
//					{
//					}
//
/*-------------------------- Process Winch Mode ----------------------------*/
					if (RobotMode==WinchMode)                   //V12 Fix
						winch.Set(launchStick.GetY()*(0.5*(1.0-leftStick.GetZ())));

/* --------------- For Manual Operation to control Spinners Spin Speed and Shoot and Pickup Angle-----------------*/
					if (ManualOp && RobotMode!=WinchMode)
					{
						launch.Rotate(launchStick.GetY()*(0.5*(1.0-leftStick.GetZ())) * -1);
						if(RobotMode==HighMode || RobotMode==LowMode)
						{
							shootspeed=(0.5*(launchStick.GetZ()-1.0) * -1);
							launch.SetShootSpeed(shootspeed);
						}
						if(RobotMode==PickupMode)
						{
							shootspeed=(0.5*(1.0-launchStick.GetZ()) * -1);
							launch.SetShootSpeed(shootspeed);
						}
					}

/*------------------ Sections for Non-Manual Op Angle Control -------------------------------------------------*/
/*------------------ Move Angle to Automatic position for all Modes except Manual and High Mode with Override */
					if(!ManualOp && !(RobotMode==HighMode && Override))  		//V12
						launch.AngleSet(EncoderTarget,AEncoder.Get());			 //Move to EncoderTarget Angle

/*----------------- Control Angle in High Mode and not Manual Operation ----------------------------*/
					if (!ManualOp && RobotMode==HighMode)   		//V12
					{
						if(Override)								//V12
							launch.Rotate(launchStick.GetY()*(0.5*(1.0-leftStick.GetZ()))*-1);  //If Override, control shoot angle
						else if(fabs(launchStick.GetY())>STICKDEADZONE) Override=true;    		//If stick is moved, turn off override
					}

/* -----------------Read Spinner Encoders and Adjust Speed if Different--------*/
				//	launch.ResetEncoders();
					Wait(.01);   	//Wait
				//	launch.MatchSpeed();
					if(ballsensor.Get())ball=true;
					else ball=false;
				}

				// Display SmartDashBoard
				dash->PutNumber("Robot Mode",RobotMode);
				dash->PutNumber("Shooting Speed", (shootspeed * -1.0));
				switch ( RobotMode )
				{
					case 0 : dash->PutString("Mode","LOW"); break ;
					case 1 : dash->PutString("Mode", "HIGH") ; break ;
					case 2 : dash->PutString("Mode","STOW") ; break ;
					case 3 : dash->PutString("Mode","DEFENSE") ; break ;
					case 4 : dash->PutString("Mode","PICKUP") ; break ;
					case 5 : dash->PutString("Mode","WINCH") ; break ;
				}
				dash->PutBoolean("Manual Operation", ManualOp);
				dash->PutNumber("Launcher Angle Encoder", AEncoder.Get());
				dash->PutNumber("Left Wheel Distance (Inches)", LWEncoder.GetDistance());
				dash->PutNumber("Right Wheel Distance (Inches)", RWEncoder.GetDistance());
				dash->PutBoolean("Ball Sensor", ball);
				dash->PutNumber("Gyro Angle", Vec[1]);
				dash->PutNumber("Vector", Vec[0]);
				dash->PutNumber("Target Area", camera.GetArea());
				dash->PutNumber("Target Height (Pixels)", camera.GetHeight());
				dash->PutNumber("Number of Contours", camera.GetNumContours());
				dash->PutNumber("Target Width", camera.GetWidth());
				dash->PutNumber("Target X", camera.GetX());
				dash->PutNumber("Target Y", camera.GetY());


			}
		}

};

START_ROBOT_CLASS(Robot);
