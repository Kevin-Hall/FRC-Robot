#ifndef CONSTANTS
#define CONSTANTS

#define VERSION "17.1"


/*-----------------------------------INIT FOR ENCODERS-------------------------------------*/
#define INITFASTROTATE	-0.8
#define INITFASTWAIT	0.0		// was 0.5
#define INITSLOWROTATE	-0.3
#define INITSLOWWAIT	0.0		// was 3.0

// Autonomous driving
#define AUTOSPEED 			0.5		    // Speed for Autonomous
#define AUTOSLOWSPEED 		0.3
#define AUTOTURNANGLE1   	45.0
#define AUTOTURNANGLE2		180.0

#define AUTOANGLETOLERANCE 20
#define AUTO0ETOLERANCE1	182.0	// first encoder tolerance
#define AUTO0ETOLERANCE2	40.0
#define AUTO0ETOLERANCE3	80.0

/*---------------------------------KICKING TIME---------------------------------------------------------*/
#define KICKSPINUPTIME		3.0
#define KICKFORWARDTIME   	 0.5
#define KICKFORWARDSPEED  	 0.4

#define KICKWAITTIME       1.0   //Now the time before the spinners turn off after shooting

#define KICKBACKWARDTIME   0.0   //Setting to Zero since not moving Kicker back now
#define KICKBACKWARDSPEED  -0.4
#define ANGLEROTATE			.3

/*---------------------------------SPIN SPEEDS----------------------------------------------------------*/
#define SPINDIRECTION      1

// motor speeds for shooting low
#define SPINLOW   0.4		// Right motor for shooting for Low


// motor speeds for shooting high
#define SPINHIGH   0.615    // Default right motor speed for shooting ball

// motor speeds for picking up the ball
#define SPINPICKUP     -0.4		// Right motor for picking up ball

/*---------------------------------SPIN FILTERS------------------------------------------------------------*/
#define SFILTER 0.9       //How much of old value to use in Filter
                          //1.0 means no adjustment in Speed
                          //The higher this is, the longer time to match speed
#define SPINTOLERANCE 1.0 //Average number of counts spinners can be off
                          //Without adjusting

#define STICKDEADZONE   0.15
/*--------------------------------ENCODERS------------------------------------------------------------------*/
#define ANGLETOLERANCE  3
#define ANGLEMINSPEED   .02
#define ENCODERLOW 		30		// encoder is 500 ticks to low mode
#define ENCODERPICKUP 	0
#define ENCODERSTOW 	120
#define ENCODERHIGH		400
#define ENCODERDEFENSE	850

#define MAXENCODER		900		// maximum the angle motor can go
#define MINENCODER		0

/*--------------------------------LAUNCHER PID CONTROLLER----------------------------------------------------*/
#define PROCONSTANT 	0.01
#define INTCONSTANT		0
#define DERCONSTANT		0

// modes to set for the Launcher

/*--------------------------------VISION---------------------------------------------------------------------*/
#define MINWIDTH	0
#define MAXWIDTH	0
#define MINHEIGHT	0
#define MAXHEIGHT	0
#define YVALUEMAX	50
#define YVALUEMIN	45
#define XVALUEMAX	162
#define XVALUEMIN   157

#endif
