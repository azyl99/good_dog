#include"Gobject.h"
#include "Gvector.h"

Gobject::Gobject()
{
	mass = 1;
	size_x = 0;
	size_y = 0;
	size_z = 0;
	isExist = true;
}
Gobject::~Gobject()
{
}
Gobject::Gobject(double s, double m)
{
	size_x = size_y = size_z = s;
	mass = m;
	isExist = true;
}
Gobject::Gobject(double s_x, double s_y, double s_z, double m)
{
	size_x = s_x;
	size_y = s_y;
	size_z = s_z;
	mass = m;
	isExist = true;
}
void Gobject::setForce(Gvector v)
{
	force = v;
}

void Gobject::setPos(Gvector v)
{
	pos = v;
}

void Gobject::setVel(Gvector v)
{
	velocity = v;
}

Gvector Gobject::getPos()
{
	return pos;
}

Gvector Gobject::getVel()
{
	return velocity;
}

Gvector Gobject::getForce()
{
	return force;
}

double Gobject::getXmax()
{
	return pos.Getx() + size_x;
		
}

double Gobject::getXmin()
{
	return pos.Getx() - size_x;
}

double Gobject::getYmax()
{
	return pos.Gety() + size_y;
}

double Gobject::getYmin()
{
	return pos.Gety() - size_y;
}

double Gobject::getZmax()
{
	return pos.Getz() + size_z;
}

double Gobject::getZmin()
{
	return pos.Getz() - size_z;
}


void Gobject::simulate(double dt)
{
	Gvector accel = force / mass;
	velocity = velocity + accel*dt;
	pos = pos + velocity*dt;
}

bool Gobject::check_exist()
{
	if (abs(velocity.Getx()) < minVelocity && abs(velocity.Gety()) < minVelocity && abs(velocity.Getz()) < minVelocity) {
		isExist = false;
		return isExist;
	}
	else {
		return isExist;
	}

}



