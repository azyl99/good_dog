#pragma once
#include <GL/glut.h>
#include "object.h"
#include "Gobject.h"
extern Object obj;//ÍêÕûµÄ×¶
extern Object frags;//ËéÆ¬

class Cone : public Gobject
{
public:
	Cone() :Gobject(9, 18, 9, 1) { setPos(Gvector(0, 0, 0)); }
	Cone(int x, int y, int z): Gobject(9, 18, 9, 1) { setPos(Gvector(x, y, z)); }
	void drawWhole()
	{
		glPushMatrix();
		glTranslated(-25, 0, -21);
		glTranslated(getPos().Getx(), getPos().Gety(), getPos().Getz());
		obj.draw();
		glPopMatrix();
	}
	void drawBroken() 
	{
		glPushMatrix();
		glTranslated(-10, 0, -40); 
		glTranslated(getPos().Getx(), getPos().Gety(), getPos().Getz());
		frags.draw();
		glPopMatrix();
	}
};