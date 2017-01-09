#include "Gbounce.h"
#include "Gobject.h"
#include "Gvector.h"

Gbounce::Gbounce()
{
}

Gbounce::~Gbounce()
{
}

Gbounce::Gbounce(Gobject f)
{
	face = f;
}

bool Gbounce::bounce_x(Gobject b)
{
	double xMax = face.getXmax();
	double xMin = face.getXmin();
	double BxMax = b.getXmax();
	double BxMin = b.getXmin();

	if (b.getYmin() < face.getYmax() && b.getYmax() > face.getYmin()) {
		if (b.getZmin() < face.getZmax() && b.getZmax() > face.getZmin()) {
			if (xMin < BxMax && xMax > BxMin) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Gbounce::bounce_y(Gobject b)
{
	double yMax = face.getYmax();
	double yMin = face.getYmin();
	double ByMax = b.getYmax();
	double ByMin = b.getYmin();

	if (b.getXmin() < face.getXmax() && b.getXmax() > face.getXmin()) {
		if (b.getZmin() < face.getZmax() && b.getZmax() > face.getZmin()) {
			if (yMin < ByMax && yMax > ByMin) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Gbounce::bounce_z(Gobject b)
{
	double zMax = face.getZmax();
	double zMin = face.getZmin();
	double BzMax = b.getZmax();
	double BzMin = b.getZmin();
	
	//cout << AxMax << "+" << AxMin << endl;
	//cout << BxMax << "%" << BxMin << endl;
	if (b.getXmin() < face.getXmax() && b.getXmax() > face.getXmin()) {
		if (b.getYmin() < face.getYmax() && b.getYmax() > face.getYmin()) {
			if (zMin < BzMax && zMax > BzMin) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	
}
