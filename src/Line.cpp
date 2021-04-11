#include "Line.hpp"

Line::Line(const Point& setp1, const Point& setp2)
{
	p1 = setp1;
	p2 = setp2;
}

Line::Line(float x1, float y1, float z1, float x2, float y2, float z2)
{
	p1 = Point(x1, y1, z1);
	p2 = Point(x2, y2, z2);
}

Line2d::Line2d(const Point2d& setp1, const Point2d& setp2)
{
	p1 = setp1;
	p2 = setp2;
}

Line2d::Line2d(float x1, float y1, float x2, float y2)
{
	p1 = {x1, y1};
	p2 = {x2, y2};
}

float length(const Line& line)
{
	return distance(line.p1, line.p2);
}
