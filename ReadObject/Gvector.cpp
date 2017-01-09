#include"Gvector.h"

Gvector::Gvector()
{
	x = 0;
	y = 0;
	z = 0;
}

Gvector::Gvector(double tx, double ty, double tz)
{
	x = tx;
	y = ty;
	z = tz;

}

Gvector::~Gvector()
{

}

double Gvector::Getx()
{
	return x;
}

double Gvector::Gety()
{
	return y;
}

double Gvector::Getz()
{
	return z;
}

void Gvector::Printinfo()
{
	cout << "(" << x << "," << y << "," << z << ")" << endl;
}

Gvector Gvector::operator+(Gvector v)
{
	return Gvector(x + v.x, y + v.y, z + v.z);
}

Gvector Gvector::operator-(Gvector v)
{
	return Gvector(x - v.x, y - v.y, z - v.z);
}

Gvector Gvector::operator*(double k)
{
	return Gvector(k*x, k*y, k*z);
}

Gvector Gvector::operator/(double k)
{
	return Gvector(x / k, y / k, z / k);
}

double Gvector::dotm(Gvector v)
{
	return x*v.x + y*v.y + z*v.z;
}

Gvector Gvector::crossm(Gvector v)
{
	return Gvector(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

double Gvector::getlength()
{
	return sqrt(x*x + y*y + z*z);
}
void Gvector::Normalize()
{
	double length = this->getlength();
	x = x / length;
	y = y / length;
	z = z / length;
}