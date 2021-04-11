#include "DeBoor.hpp"

#include "Point.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// interpolates as weighted by t on f2 and 1-t on f1
float interpolate(float f1, float f2, float t) {
	return ((1.0 - t) * f1 + t * f2);
}

// interpolation on Point objects
Point cInterpolate(const Point& p1, const Point& p2, float t) {
	Point cRet;
	cRet.x = interpolate(p1.x, p2.x, t);
	cRet.y = interpolate(p1.y, p2.y, t);
	cRet.z = interpolate(p1.z, p2.z, t);
	cRet.w = interpolate(p1.w, p2.w, t);
	return cRet;
}

// Implementation of de Boor algorithm for drawing b spline curves
Point tDeBoor(const BSplineCurve& bsc, float uBar)
{
	try
	{
		int order = bsc.getOrder();
		int knotIndex = 0;

		// Find the index of the knot value preceding uBar.
		for (unsigned int knot = 1; knot < bsc.getKnots().size(); knot++)
			if (uBar >= *(bsc.getKnot(knot))) knotIndex = knot;
		if(knotIndex - (order - 1) < 0)
			throw(std::runtime_error("Bad knotIndex"));
		else if(knotIndex == bsc.getPoints().size())
			knotIndex--;

		// Initialize the active points to start with.
		std::vector<Point> activePoints;
		for (int p = knotIndex - (order - 1); p <= knotIndex; p++)
		{
			const Point* next = bsc.getPoint(p);
			if(next != nullptr) activePoints.push_back(*next);
		}
		if(activePoints.size() < order)
			throw(std::runtime_error("Not enough starting points"));

		// Double loop for the DeBoor triangle scheme.
		for(int j = 1; j <= (order - 1); j++)
		{
			std::vector<Point> nextPoints;
			for (int i = knotIndex - (order - 1), point = 0; i <= knotIndex - j; i++, point++)
			{
				// Interpolation step.
				const float* Uik = bsc.getKnot(i + order);
				const float* Uij = bsc.getKnot(i + j);
				if(Uik == nullptr || Uij == nullptr)
					throw(std::runtime_error("knot is null"));
				float weight = (uBar - *Uij) / (*Uik - *Uij);
				Point c = cInterpolate(activePoints[point], activePoints[point + 1], weight);
				nextPoints.push_back(c);
			}
			activePoints = nextPoints;
		}
		return activePoints[0];
	}
	catch(const std::exception& err)
	{
		std::cout << err.what() << std::endl;
		return Point(0.0, 0.0, 0.0, 1.0);
	}
}

// Implementation of the De Boor algorithm for drawing rational nurbs surfaces.
Point tDeBoor3D(const NurbsSurface& surface, float u, float v)
{
	std::vector<Point> intermediatePoints;
	std::vector<std::vector<Point> > nurbsPoints = surface.getPoints();

	// Multiply all points by their weight.
	for(auto row = nurbsPoints.begin(); row != nurbsPoints.end(); ++row)
		for(auto point = row->begin(); point != row->end(); ++point)
			*point = rational(*point);

	for(auto row = nurbsPoints.begin(); row != nurbsPoints.end(); ++row)
	{
		BSplineCurve curve(*row, surface.getVKnots(), surface.getVOrder());
		intermediatePoints.push_back(tDeBoor(curve, v));
	}

	BSplineCurve curve(intermediatePoints, surface.getUKnots(), surface.getUOrder());
	Point point = tDeBoor(curve, u);
	return irrational(point);
}
