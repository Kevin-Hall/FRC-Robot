#pragma once
#include <memory>
#include "WPIlib.h"
#include <unistd.h>
#include <stdio.h>
#include <vector>
using namespace std;
typedef shared_ptr<NetworkTable> NetTable;
typedef vector<double> Gvector;				// a vector designed for Grip
class Vision
{
public:
	Vision();
	double GetArea();
	double GetX();
	double GetY();
	double GetHeight();
	int GetNumContours();
	double GetWidth();
	~Vision();
private:
	NetTable Table;
	Gvector area;
	double Areavalue;
	Gvector X;
	double Xvalue;
	Gvector Y;
	double Yvalue;
	Gvector Height;
	double HeightValue;
	Gvector Width;
	double WidthValue;
};

