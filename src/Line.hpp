#ifndef LINE_HPP_
#define LINE_HPP_

#include "Point.hpp"

struct Line
{
	Line(const Point& setp1, const Point& setp2);
	Line(float x1, float y1, float z1, float x2, float y2, float z2);
	Point p1;
	Point p2;
};

struct Line2d
{
	Line2d(const Point2d& setp1, const Point2d& setp2);
	Line2d(float x1, float y1, float x2, float y2);
	Point2d p1;
	Point2d p2;
};

float length(const Line& line);

#endif
