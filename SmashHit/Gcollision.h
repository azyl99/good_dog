#ifndef _GCOLLISION_H
#define _GCOLLISION_H

#include "Gobject.h"

class Gcollision{
private:
	//Gobject a;
	//Gobject b;
public:
	Gcollision();
	~Gcollision();
	bool detection(Gobject a, Gobject b);
	bool detection_x(Gobject a, Gobject b);
	bool detection_y(Gobject a, Gobject b);
	bool detection_z(Gobject a, Gobject b);


};

#endif