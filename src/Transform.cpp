#include "Transform.hpp"

#include <cmath>

#define PI 3.1415926535897

// degree trig functions, because rads are not rad
float dcos(float angle) {
	return cos((double)angle * PI / 180);
}

float dsin(float angle) {
	return sin((double)angle * PI / 180);
}

float dtan(float angle)
{
	return tan((double)angle * PI / 180);
}

float darctan(float opposite, float adjacent) {
	if (std::abs(adjacent) < 1.0e-10) {
		return 90.0;
	}
	else {
		return atan(opposite / adjacent) * (180 / PI);
	}
}

Point xRotate(const Point& p, float angle)
{
	float y = p.y * dcos(angle) - p.z * dsin(angle);
	float z = p.y * dsin(angle) + p.z * dcos(angle);
	return Point(p.x, y, z, 1.0);
}

Point yRotate(const Point& p, float angle)
{
	float z = p.z * dcos(angle) - p.x * dsin(angle);
	float x = p.z * dsin(angle) + p.x * dcos(angle);
	return Point(x, p.y, z, 1.0);
}

Point zRotate(const Point& p, float angle)
{
	float x = p.x * dcos(angle) - p.y * dsin(angle);
	float y = p.x * dsin(angle) + p.y * dcos(angle);
	return Point(x, y, p.z, 1.0);
}

Point rotate(const Point& p, const Line& line, float angle)
{
	Vector v = line.p2 - line.p1;
	float zRotateAngle = darctan(v.x, v.y);
	float xzVecLength = sqrt((v.x * v.x) + (v.y * v.y));
	float xRotateAngle = darctan(xzVecLength, v.z);
	Point pReturn = p;
	// Translate the rotation line to the origin.
	pReturn = pReturn - line.p1;
	bool nPositive = pReturn.z > 0.0;
	// Rotate line around Z axis onto YZ plane.
	bool zPositive = pReturn.x * pReturn.y > 0.0;
	if(zPositive)
		pReturn = zRotate(pReturn, zRotateAngle);
	else
		pReturn = zRotate(pReturn, zRotateAngle * -1.0);


	// Rotate the line around the X axis onto the Z axis.
	bool xPositive = pReturn.y * pReturn.z > 0.0;
	if(xPositive)
		pReturn = xRotate(pReturn, xRotateAngle);
	else
		pReturn = xRotate(pReturn, xRotateAngle * -1.0);

	// Rotate around Z axis whatever rotation angle was specified
	if(nPositive)
		pReturn = zRotate(pReturn, angle);
	else
		pReturn = zRotate(pReturn, angle * -1.0);

	// Reverse transformations to reorient.
	if(xPositive)
		pReturn = xRotate(pReturn, xRotateAngle * -1.0);
	else
		pReturn = xRotate(pReturn, xRotateAngle);

	if(zPositive)
		pReturn = zRotate(pReturn, zRotateAngle * -1.0);
	else
		pReturn = zRotate(pReturn, zRotateAngle);

	pReturn = pReturn + line.p1;
	return pReturn;
}

Point translate(const Point& p, const Vector& v)
{
	return p + v;
}
