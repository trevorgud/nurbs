#ifndef DRAWING_HPP_
#define DRAWING_HPP_

#include "BSplineCurve.hpp"
#include "Color.hpp"
#include "Line.hpp"
#include "NurbsSurface.hpp"
#include "Point.hpp"

#include <vector>

void drawLine(const Line& line, const Color& color, float lineWidth);

void drawPoint(const Point& point, const Color& color);

//draws lines between control points i and i+1
void drawControlPoly(const std::vector<Point>& cp, const Color& color, float lineWidth);

//generate t interval values
//should be resolution + 1 values stored in t between begin and end
std::vector<float> tGenerate(int resolution, float begin, float end);

void drawBetween(const std::vector<Point>& points, const Color& color, float lineWidth);

void drawWireframe(const std::vector<std::vector<Point> >& points, const Color& color, float lineWidth);

void drawBSpline(const BSplineCurve& bspline, const Color& color, float lineWidth, int resolution);

void drawNurbs(const NurbsSurface& surface, const Color& color, float lineWidth, int resolution);

//renders strings to the command line subwindow at position yOffset
void renderString(const std::string& myString, float yOffset, int window);

#endif
