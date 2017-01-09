#ifndef _GOBJECT_H
#define _GOBJECT_H
#include "Gvector.h"

#define minVelocity 0.001
class Gobject {
private:

	Gvector pos;
	Gvector velocity;

	Gvector force;
	double size_x;
	double size_y;
	double size_z;
	double mass;
	bool isExist;

public:
	Gobject();
	virtual ~Gobject();
	Gobject(double s, double m);
	Gobject(double s_x, double s_y, double s_z, double m);
	void setForce(Gvector);
	void setPos(Gvector);
	void setVel(Gvector);
	Gvector getPos();
	Gvector getVel();
	Gvector getForce();
	double getXmax();
	double getXmin();
	double getYmax();
	double getYmin();
	double getZmax();
	double getZmin();

	void simulate(double dt);
	bool check_exist();


};
#endif