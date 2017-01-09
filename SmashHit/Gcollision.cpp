#include "Gcollision.h"
#include "Gobject.h"
#include "Gvector.h"

Gcollision::Gcollision()
{
}

Gcollision::~Gcollision()
{
}

bool Gcollision::detection(Gobject a, Gobject b)
{
	if (detection_x(a, b) && detection_y(a, b) && detection_z(a, b)) {
		return true;
	}
	else {
		return false;
	}
	return false;
}

bool Gcollision::detection_x(Gobject a, Gobject b)
{
	double AxMax = a.getXmax();
	double AxMin = a.getXmin();
	double BxMax = b.getXmax();
	double BxMin = b.getXmin();

	if (AxMin < BxMax && AxMax > BxMin) {
		return true;
	}
	else {
		return false;
	}
	
}

bool Gcollision::detection_y(Gobject a, Gobject b)
{
	double AyMax = a.getYmax();
	double AyMin = a.getYmin();
	double ByMax = b.getYmax();
	double ByMin = b.getYmin();

	if (AyMin < ByMax && AyMax > ByMin) {
		return true;
	}
	else {
		return false;
	}
}

bool Gcollision::detection_z(Gobject a, Gobject b)
{
	double AzMax = a.getZmax();
	double AzMin = a.getZmin();
	double BzMax = b.getZmax();
	double BzMin = b.getZmin();

	if (AzMin < BzMax && AzMax > BzMin) {
		return true;
	}
	else {
		return false;
	}
}