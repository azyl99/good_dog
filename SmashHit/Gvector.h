#ifndef _GVECTOR_H
#define _GVECTOR_H
#include <iostream>
#include<cmath>

using namespace std;

class Gvector {
private:
	double x, y, z;

public:
	Gvector();
	Gvector(double x, double y, double z);
	~Gvector();
	double Getx();
	double Gety();
	double Getz();
	void Printinfo();

	Gvector operator+(Gvector v);
	Gvector operator-(Gvector v);
	Gvector operator*(double k);
	Gvector operator/(double k);
	double dotm(Gvector v);
	Gvector crossm(Gvector v);

	double getlength();
	void Normalize();

};
#endif