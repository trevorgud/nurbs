#include "Drawing.hpp"

#include "DeBoor.hpp"

#include <algorithm>

#include "GL/glut.h"

void drawLine(const Line& line, const Color& color, float lineWidth)
{
	glLineWidth(lineWidth);
	glColor3f(color.red, color.blue, color.green);
	glBegin(GL_LINES);
	glVertex3f(line.p1.x, line.p1.y, line.p1.z);
	glVertex3f(line.p2.x, line.p2.y, line.p2.z);
	glEnd();
}

void drawPoint(const Point& point, const Color& color)
{
	glBegin(GL_POINTS);
	glColor3f(color.red, color.blue, color.green);
	glVertex3f(point.x, point.y, point.z);
	glEnd();
}

//draws lines between control points i and i+1
void drawControlPoly(const std::vector<Point>& cp, const Color& color, float lineWidth)
{
	if(cp.size() < 2)
		return;
	for(auto it = cp.begin(); (it != cp.end()) && (it + 1 != cp.end()); ++it)
	{
		Line currentLine = {*it, *(it + 1)};
		drawLine(currentLine, color, lineWidth);
	}
}

//generate t interval values
//should be resolution + 1 values stored in t between begin and end
std::vector<float> tGenerate(int resolution, float begin, float end) {
	std::vector<float> t;
	for(int k = 0; k <= resolution; k++) {
		float weight = ((float)(k)) / ((float)(resolution));
		t.push_back(interpolate(begin, end, weight));
	}
	return t;
}

void drawBetween(const std::vector<Point>& points, const Color& color, float lineWidth)
{
	for(auto it = points.begin(); (it != points.end()) && (it + 1 != points.end()); ++it)
	{
		Line currentLine = {*it, *(it + 1)};
		drawLine(currentLine, color, lineWidth);
	}
}

void drawWireframe(const std::vector<std::vector<Point> >& points, const Color& color, float lineWidth)
{
	for(auto row = points.begin(); row != points.end(); ++row)
	{
		drawBetween(*row, color, lineWidth);
		if((row + 1) != points.end()) // If the next row exists.
			for
			(
				auto col = row->begin(), colNext = (row + 1)->begin(); // Iterate over both rows.
				col != row->end() && colNext != (row + 1)->end(); // End the loop if one of them is too short.
				++col, ++colNext
			)
				drawLine({*col, *colNext}, color, lineWidth);
	}
}

void drawBSpline(const BSplineCurve& bspline, const Color& color, float lineWidth, int resolution)
{
	std::vector<float> tValues = tGenerate(resolution, bspline.tMin(), bspline.tMax());
	std::vector<Point> controlPoints = bspline.getPoints();
	std::vector<Point> curvePoints;

	for(auto it = tValues.begin(); it != tValues.end(); ++it)
		curvePoints.push_back(bspline.c(*it));

	drawBetween(controlPoints, {0.0, 1.0, 0.0}, 1.0);

	drawBetween(curvePoints, color, lineWidth);
}

void drawNurbs(const NurbsSurface& surface, const Color& color, float lineWidth, int resolution)
{
	std::vector<std::vector<Point> > points;

	std::vector<float> uValues = tGenerate(resolution, surface.uMin(), surface.uMax());
	std::vector<float> vValues = tGenerate(resolution, surface.vMin(), surface.vMax());

	for(auto v = vValues.begin(); v != vValues.end(); ++v)
	{
		std::vector<Point> rowPoints;

		for(auto u = uValues.begin(); u != uValues.end(); ++u)
			rowPoints.push_back(tDeBoor3D(surface, *u, *v));

		points.push_back(rowPoints);
	}

	drawWireframe(points, color, lineWidth);
	if(surface.getMode() == NurbsSurface::ALL)
		drawWireframe(surface.getPoints(), {1.0, 0.0, 0.0}, 2.0);
	else
		drawWireframe(surface.getPoints(), {0.0, 1.0, 0.0}, 1.0);

	NurbsSurface::Index index = surface.getIndexSelected();
	std::vector<std::vector<Point> > controlPoints = surface.getPoints();

	if(surface.getMode() == NurbsSurface::ROW)
		drawBetween(controlPoints[index.i], {1.0, 0.0, 0.0}, 2.0);
	else if(surface.getMode() == NurbsSurface::COLUMN)
	{
		std::vector<Point> column;
		for(auto it = controlPoints.begin(); it != controlPoints.end(); ++it)
			column.push_back((*it)[index.j]);
		drawBetween(column, {1.0, 0.0, 0.0}, 2.0);
	}

	Point point = (surface.getPoints())[index.i][index.j];
	drawPoint(point, {1.0, 0.0, 0.0});
}

//renders strings to the command line subwindow at position yOffset
void renderString(const std::string& myString, float yOffset, int window)
{
	int current = glutGetWindow();
	glutSetWindow(window);
	glRasterPos2f(-.98, yOffset);
	for (int i = 0; i < myString.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, myString[i]);
	}
	glutPostRedisplay();
	glutSetWindow(current);
}
