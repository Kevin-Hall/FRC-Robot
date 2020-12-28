/*
 * vision.cpp
 *
 *  Created on: Feb 2, 2016
 *      Author: ossining
 */
#include "WPIlib.h"
#include "Vision.h"

Vision::Vision()
{
	Table = NetworkTable::GetTable("GRIP/myContoursReport");
}

double Vision::GetArea()
{
	area = Table->GetNumberArray("area", llvm::ArrayRef<double>());
	if (area.size() == 0)
		return 0.0;
	else
		return area[0];
}

double Vision::GetX()
{
	X = Table->GetNumberArray("centerX", llvm::ArrayRef<double>());
	if (X.size() == 0)
		return 0.0;
	else
		return X[0];
}

double Vision::GetY()
{
	Y = Table->GetNumberArray("centerY", llvm::ArrayRef<double>());
	if (Y.size() == 0)
		return 0.0;
	else
		return Y[0];
}
double Vision::GetHeight()
{
	Height = Table->GetNumberArray("targets/height", llvm::ArrayRef<double>());
	if (Height.size() == 0)
		return 0.0;
	else
		return Height[0];
}

int Vision::GetNumContours()
{
	area = Table->GetNumberArray("targets/area", llvm::ArrayRef<double>());
	return area.size();
}

double Vision::GetWidth()
{
	Width = Table->GetNumberArray("targets/width", llvm::ArrayRef<double>());
	if (Width.size() == 0)
		return 0.0;
	else
		return Width[0];
}
Vision::~Vision()
{}

