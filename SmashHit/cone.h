#pragma once
#include <GL/glut.h>
#include "object.h"
#include "Gobject.h"
extern Object obj;//ÍêÕûµÄ×¶
extern Object frags;//ËéÆ¬

extern int wholeList;
extern int brokenList;

class Cone : public Gobject
{
public:
	bool bBroken;
	Cone() :bBroken(false),Gobject(9, 18, 9, 1) { setPos(Gvector(0, 0, 0)); }
	Cone(int x, int y, int z):bBroken(false), Gobject(9, 18, 9, 1) { setPos(Gvector(x, y, z)); }
	void draw()
	{
		glPushMatrix();
		glTranslated(getPos().Getx(), getPos().Gety(), getPos().Getz());
		if (bBroken)
			glCallList(wholeList);
		else
			glCallList(brokenList);
		glPopMatrix();
	}
	static int genWholeList()
	{
		GLint lid = glGenLists(1);
		glNewList(lid, GL_COMPILE);

		glPushMatrix();
		glTranslated(-25, 0, -21);
		obj.draw();
		glPopMatrix();

		glEndList();
		return lid;
	}
	static int genBrokenList()
	{
		GLint lid = glGenLists(1);
		glNewList(lid, GL_COMPILE);

		glPushMatrix();
		glTranslated(-10, 0, -40); 
		frags.draw();
		glPopMatrix();

		glEndList();
		return lid;
	}
};