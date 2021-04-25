#ifndef POINT_HPP_
#define POINT_HPP_

#include <nlohmann/json.hpp>

struct HomogeneousCoordinate
{
	HomogeneousCoordinate();
	HomogeneousCoordinate(float setx, float sety, float setz, float setw = 1.0);
	float x;
	float y;
	float z;
	float w;
	HomogeneousCoordinate operator+(const HomogeneousCoordinate& other) const;
	HomogeneousCoordinate operator-(const HomogeneousCoordinate& other) const;
	HomogeneousCoordinate operator*(float scaleFactor) const;
};

struct Point2d
{
	Point2d();
	Point2d(float setx, float sety);
	float x;
	float y;
};

typedef HomogeneousCoordinate Point;
typedef HomogeneousCoordinate Vector;

Vector crossProduct(const Vector& v1, const Vector& v2);
Vector unitVector(const Vector& v);
float dotProduct(const Vector& v1, const Vector& v2);
float distance(const Point& p1, const Point& p2);
Point rational(const Point& p);
Point irrational(const Point& p);

void to_json(nlohmann::json& json, const HomogeneousCoordinate& coord);
void from_json(const nlohmann::json& json, HomogeneousCoordinate& coord);

#endif
