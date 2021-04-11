#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "Line.hpp"
#include "Point.hpp"

float dcos(float angle);
float dsin(float angle);
float dtan(float angle);
float darctan(float opposite, float adjacent);

Point translate(const Point& p, const Vector& v);

Point xRotate(const Point& p, float angle);
Point yRotate(const Point& p, float angle);
Point zRotate(const Point& p, float angle);

Point rotate(const Point& p, const Line& line, float angle);

#endif
