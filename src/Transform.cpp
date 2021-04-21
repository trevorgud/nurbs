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

float darccos(float adjacent, float hypotenuse)
{
	return acos(adjacent / hypotenuse) * (180 / PI);
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
	return Point(p.x, y, z, p.w);
}

Point yRotate(const Point& p, float angle)
{
	float z = p.z * dcos(angle) - p.x * dsin(angle);
	float x = p.z * dsin(angle) + p.x * dcos(angle);
	return Point(x, p.y, z, p.w);
}

Point zRotate(const Point& p, float angle)
{
	float x = p.x * dcos(angle) - p.y * dsin(angle);
	float y = p.x * dsin(angle) + p.y * dcos(angle);
	return Point(x, y, p.z, p.w);
}

Point rotate(const Point& p, const Line& line, float angle)
{
	Vector v = line.p2 - line.p1;
	float zRotateAngle = std::abs(darctan(v.x, v.y));
	float xzVecLength = sqrt((v.x * v.x) + (v.y * v.y));
	float xRotateAngle = std::abs(darctan(xzVecLength, v.z));

	// Adjust angles so that rotation vector is always pointing towards positive Z.
	if(v.y < 0) zRotateAngle = 180.0 - zRotateAngle;
	if(v.x < 0) zRotateAngle = -zRotateAngle;
	if(v.z < 0) xRotateAngle = 180.0 - xRotateAngle;

	Point pReturn = p;

	// Translate the rotation line to the origin.
	pReturn = pReturn - line.p1;

	// Rotate line around Z axis onto YZ plane.
	pReturn = zRotate(pReturn, zRotateAngle);

	// Rotate the line around the X axis onto the Z axis.
	pReturn = xRotate(pReturn, xRotateAngle);

	// Rotate around Z axis whatever rotation angle was specified
	pReturn = zRotate(pReturn, angle);

	// Reverse transformations to reorient.
	pReturn = xRotate(pReturn, -xRotateAngle);
	pReturn = zRotate(pReturn, -zRotateAngle);
	pReturn = pReturn + line.p1;

	return pReturn;
}

Point translate(const Point& p, const Vector& v)
{
	return p + v;
}
