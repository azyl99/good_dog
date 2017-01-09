#include <windows.h>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <gl/glut.h>
#include "object.h" 
#include "cone.h" 

GLfloat aspect = 1;
GLfloat dx = 0, dy = 0, dz = 0;
GLfloat ax = 0, ay = 0, az = 0;
GLint mx = 0, my = 0;
GLint MouseDown = 0;
GLuint texture[5];
Object maze, obj, frags;

Cone cones[] = { 
	Cone(-73, 13, 0), 
	Cone(0, 13, 0), 
	Cone(73, 13, 0),
	Cone(-46, 13, -103),
	Cone(76, 22, -103),
	Cone(57, 13, -300),
	Cone(-44, 5, -399),
	Cone(-67, 29, -562),
	Cone(65, 17, -561),
	Cone(-45, 14, -758),
	Cone(43, 5, -759),
	Cone(4, 6, -878),
	Cone(-15, 4, -1145),
	Cone(75, 22, -1148),
	Cone(-13, 6, -1523),
	Cone(75, 22, -1526),
	Cone(-75, 22, -1603)
};
int coneCount = sizeof(cones) / sizeof(Cone);
int wHeight = 0;
int wWidth = 0;
int wholeList = 0;
int brokenList = 0;
bool bAction = false;

void myIdle()
{
	Sleep(10);
	glutPostRedisplay();
}

float eye[] = { 0, 60, 100 };
float center[] = { 0, 10, 10 };
void myReshape(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}

	wHeight = height;
	wWidth = width;

	aspect = (float)width / (height ? height : 1);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, aspect, 1, 10000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		dz += 5.0f;
		break;
	case 's':
		dz -= 5.0f;
		break;
	case 'a':
		dx -= 1.0f;
		break;
	case 'd':
		dx += 1.0f;
		break;
	case 'q':
		dy += 1.0f;
		break;
	case 'e':
		dy -= 1.0f;
		break;
	case 'b':
		cones[0].bBroken = !cones[0].bBroken;
		break;
	case ' ':
		bAction = !bAction;
		break;
	}
	myReshape(wWidth, wHeight);
}
#define  GLUT_WHEEL_UP 3           //定义滚轮操作  
#define  GLUT_WHEEL_DOWN 4  
void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_DOWN) {
		MouseDown = 1, mx = x, my = y;
		//std::cout << x << " " << y << "\n";
	}
	else if (button == GLUT_WHEEL_UP)
	{
		dz += 1.0f;
	}
	else if (button == GLUT_WHEEL_DOWN)
	{
		dz -= 1.0f;
	}
	else
	{
		MouseDown = 0;
	}
}

void myMotion(int x, int y)
{
	if (MouseDown)
	{
		ax += (y - my) / 5.0f;
		ay += (x - mx) / 5.0f;
		mx = x;
		my = y;
	}
}

void setLight()
{
	static const GLfloat light_position[] = { 50.0f,50.0f,50.0f,0.0f };
	static const GLfloat light_ambient[] = { 0.0f,0.0f,0.0f,0.0f };
	static const GLfloat light_diffuse[] = { 1.0f,0.9f,0.9f,0.0f };
	static const GLfloat light_specular[] = { 1.0f,1.0f,1.0f,0.0f };
	static const GLfloat light_direction[] = { -1.0f,-1.0f,-1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10.0f);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 120.0f);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

		glTranslatef(dx, dy, dz);
		glRotatef(ax, 1.0f, 0.0f, 0.0f);
		glRotatef(ay, 0.0f, 1.0f, 0.0f);
		//迷宫
		glPushMatrix();
		glTranslated(-64, 0, 0);
		maze.draw();
		glPopMatrix();

		//画cones
		for (int i = 0; i < coneCount; i++) {
			cones[i].draw();
		}

	glPopMatrix();

	if (bAction) { eye[2] -= 4.0f; center[2] -= 4.0f; myReshape(wWidth, wHeight);}
	glutSwapBuffers();
}

void init()
{
	glGenTextures(5, texture);
	maze.readObj("maze.obj");
	obj.readObj("完整.obj");
	frags.readObj("碎.obj");
	glClearColor(0.93, 0.94, 0.98, 1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_TEXTURE_2D);
	setLight();

	wholeList = Cone::genBrokenList();
	brokenList = Cone::genWholeList();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(320, 180);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("OpenGl");
	glutReshapeFunc(&myReshape);
	glutKeyboardFunc(&myKeyboard);
	glutMouseFunc(&myMouse);
	glutMotionFunc(&myMotion);
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle);
	init();
	glutMainLoop();
	return 0;
}