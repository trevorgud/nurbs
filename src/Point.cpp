#include "Point.hpp"

#include <algorithm>
#include <cmath>

HomogeneousCoordinate::HomogeneousCoordinate()
	: x(0.0), y(0.0), z(0.0), w(1.0)
{}

HomogeneousCoordinate::HomogeneousCoordinate(float setx, float sety, float setz, float setw)
	: x(setx), y(sety), z(setz), w(setw)
{}

HomogeneousCoordinate HomogeneousCoordinate::operator+(const HomogeneousCoordinate& other) const
{
	return HomogeneousCoordinate(x + other.x, y + other.y, z + other.z, w || other.w);
}

HomogeneousCoordinate HomogeneousCoordinate::operator-(const HomogeneousCoordinate& other) const
{
	return HomogeneousCoordinate(x - other.x, y - other.y, z - other.z, std::min(w - other.w, static_cast<float>(0)));
}

HomogeneousCoordinate HomogeneousCoordinate::operator*(float scale) const
{
	// TODO: Figure out if it makes sense to scale w as well.
	return HomogeneousCoordinate(x * scale, y * scale, z * scale, w);
}

Point2d::Point2d()
	: x(0.0), y(0.0)
{}

Point2d::Point2d(float setx, float sety)
	: x(setx), y(sety)
{}

Vector crossProduct(const Vector& v1, const Vector& v2)
{
	return Vector(v1.y * v2.z - v1.z * v2.y,
	              v1.z * v2.x - v1.x * v2.z,
	              v1.x * v2.y - v1.y * v2.x,
	              0.0);
}

Vector unitVector(const Vector& v)
{
	float length = distance(Point(0, 0, 0, 1), v);
	if(length != 0.0)
		return Vector(v.x / length, v.y / length, v.z / length, 0.0);
	else
	{
		// Preventing division by zero.
		return Vector(0.0, 0.0, 0.0, 0.0);
	}
}

float distance(const Point& p1, const Point& p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

Point rational(const Point& p)
{
	return Point(p.x * p.w, p.y * p.w, p.z * p.w, p.w);
}

Point irrational(const Point& p)
{
	return Point(p.x / p.w, p.y / p.w, p.z / p.w, p.w);
}
