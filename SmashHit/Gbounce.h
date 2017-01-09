#ifndef _GBOUNCE_H
#define _GBOUNCE_H

#include "Gobject.h"

class Gbounce {
private:
	Gobject face;
public:
	Gbounce();
	~Gbounce();
	Gbounce(Gobject f);
	bool bounce_x(Gobject b);
	bool bounce_y(Gobject b);
	bool bounce_z(Gobject b);
	
};

#endif