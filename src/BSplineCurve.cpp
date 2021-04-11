#include "BSplineCurve.hpp"

#include "DeBoor.hpp"

#include <cmath>

BSplineCurve::BSplineCurve()
	: Curve(BSPLINE)
{
	k = 2;
	knots.clear();
}

BSplineCurve::BSplineCurve(const std::vector<Point>& points, int kVal)
	: Curve(BSPLINE, points)
{
	k = kVal;
	knots.clear();
	for(int i = 0; i < numPoints() + k; i++)
		knots.push_back((float) i);
}

BSplineCurve::BSplineCurve(const std::vector<Point>& points, const std::vector<float>& setKnots, int kVal)
	: Curve(BSPLINE, points)
{
	k = kVal;
	knots = setKnots;
}

void BSplineCurve::setKnots(const std::vector<float>& u)
{
	knots = u;
}

std::vector<float> BSplineCurve::getKnots() const
{
	return knots;
}

const float* BSplineCurve::getKnot(int i) const
{
	if(i < 0 || i >= knots.size()) return nullptr;
	else return &(knots[i]);
}

void BSplineCurve::setKnot(int i, float u)
{
	if(i >= 0 && i < knots.size()) knots[i] = u;
}

// Inserts a control point before pos and updates the knot values
void BSplineCurve::insertPointAndKnot(const Point& p, int pos)
{
	//shift all knots up by one
	for (int i = k - 1 + pos; i <= numPoints() + k; i++) {
		knots[i] = knots[i] + 1.0;
	}
	//insert the previous knot plus one into the spot corresponding
	//to the new control point (with bounds checking)
	if (k - 2 + pos >= 0 && k - 2 + pos < knots.size()) {
		knots.insert(knots.begin() + k - 1 + pos, knots[k - 2 + pos]);
	}
	//insert the point into control point vector
	insertPoint(p, pos);
}

void BSplineCurve::uniformKnots()
{
	knots.clear();
	for(int i = 0; i < numPoints() + k; i++)
		knots.push_back((float) i);
}

void BSplineCurve::distanceKnots()
{
	knots.clear();
	if(points_.empty())
		return;

	knots.push_back(0.0); // Front knot starts at 0.0.
	if(points_.size() < 2)
		return;

	int numSegs = points_.size() - (k - 1);
	float totalDist;
	float frontDist;
	for(int i = 0; i < numSegs; i++)
	{
		totalDist = 0;
		for(int j = i; j < k + i; j++)
		{
			float dist = distance(points_[j], points_[j + 1]);
			totalDist += dist;
		}
		knots.push_back(knots.back() + totalDist);
		if(i == 0)
			frontDist = totalDist; //at this point in the loop it will be frontDist
	}
	float backDist = totalDist; //will be backDist once the loop finishes
	for(int i = 0; i < k - 1; i++)
	{
		//expand the range of knots
		knots.insert(knots.begin(), knots.front() - frontDist);
		knots.push_back(knots.back() + backDist);
	}
}

void BSplineCurve::centripitalKnots()
{
	knots.clear();
	if(points_.empty())
		return;

	knots.push_back(0.0); // Front knot starts at 0.0.
	if(points_.size() < 2)
		return;

	int numSegs = points_.size() - (k - 1);
	float totalDist;
	float frontDist;
	for(int i = 0; i < numSegs; i++)
	{
		totalDist = 0;
		for(int j = i; j < k + i; j++)
		{
			float sqrtDist = sqrt(distance(points_[j], points_[j + 1]));
			totalDist += sqrtDist;
		}
		knots.push_back(knots.back() + totalDist);
		if(i == 0)
			frontDist = totalDist; //at this point in the loop it will be frontDist
	}
	float backDist = totalDist; //will be backDist once the loop finishes
	for(int i = 0; i < k - 1; i++)
	{
		//expand the range of knots
		knots.insert(knots.begin(), knots.front() - frontDist);
		knots.push_back(knots.back() + backDist);
	}
}

void BSplineCurve::setOrder(int order)
{
	if(k != order)
	{
		knotType = Curve::DISTANCE;
		k = order;
	}

	updateKnots();
}

int BSplineCurve::getOrder() const
{
	return k;
}

void BSplineCurve::addPoint(const Point& c)
{
	points_.push_back(c);
	updateKnots();
}

void BSplineCurve::movePoint(const Point& c)
{
	Curve::movePoint(c);
	updateKnots();
}

void BSplineCurve::deletePoint()
{
	BSplineCurve::deletePoint(selectedPoint_);
}

void BSplineCurve::deletePoint(int pos)
{
	Curve::deletePoint(pos);
	updateKnots();
}

Point BSplineCurve::c(float t) const
{
	return tDeBoor(*this, t);
}

float BSplineCurve::tMax() const
{
	if(knots.size() > k - 1)
		return knots[(knots.size() - 1) - (k - 1)];
	else
		return 0.0;
}

float BSplineCurve::tMin() const
{
	if(knots.size() > k - 1) return knots[k - 1];
	else return 0.0;
}
