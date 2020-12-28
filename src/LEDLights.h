#ifndef LEDLights_H_
#define LEDLights_H_
#include "WPIlib.h"

class LEDLights {

	public:

		LEDLights(uint32_t redch,uint32_t greench,uint32_t bluech);
		void SetColor(uint32_t name);
		void SetRGB(uint32_t red,uint32_t green,uint32_t blue);
		#define RED 0
		#define GREEN 1
		#define BLUE 2
		#define	YELLOW 3
		#define CYAN 4
		#define WHITE 5
		#define PURPLE 6
		#define OFF 7
	private:
		Jaguar pwmred;
		Jaguar pwmgreen;
		Jaguar pwmblue;
};

#endif
