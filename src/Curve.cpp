#include "Curve.hpp"

#include <cmath>
#include <iostream>

Curve::Curve(Type type, const std::vector<Point>& points, int selectedPoint)
	: type_(type), points_(points), selectedPoint_(selectedPoint), knotType(DISTANCE)
{}

void Curve::setPoints(const std::vector<Point>& points)
{
	points_ = points;
}

std::vector<Point> Curve::getPoints() const
{
	return points_;
}

const Point* Curve::getPoint(int pos) const
{
	if(pos >= 0 && pos < points_.size())
		return &(points_[pos]);
	else
		return nullptr;
}

const Point* Curve::getPoint() const
{
	return getPoint(selectedPoint_);
}

Curve::Type Curve::getType() const
{
	return type_;
}

bool Curve::isAggregate() const
{
	if(type_ == QUAD_BSPLINE || type_ == CUBIC_BSPLINE)
		return true;
	else
		return false;
}

void Curve::setType(Curve::Type type)
{
	type_ = type;
}

void Curve::addPoint(const Point& point)
{
	points_.push_back(point);
}

void Curve::insertPoint(const Point& point)
{
	insertPoint(point, selectedPoint_);
}

void Curve::insertPoint(const Point& point, int pos)
{
	if(pos < 0 || pos > points_.size()) return;
	else points_.insert(points_.begin() + pos, point);
}

void Curve::movePoint(const Point& point)
{
	movePoint(point, selectedPoint_);
}

void Curve::movePoint(const Point& point, int pos)
{
	if(pos < 0 || pos >= points_.size()) return;
	else points_[pos] = point;
}

void Curve::deletePoint()
{
	deletePoint(selectedPoint_);
}

void Curve::deletePoint(int pos)
{
	if(pos < 0 || pos >= points_.size()) return;
	else points_.erase(points_.begin() + pos);
}

int Curve::numPoints() const
{
	return points_.size();
}

void Curve::setSelectedPoint(int pos)
{
	if(pos < 0 || pos >= points_.size()) return;
	else selectedPoint_ = pos;
}

int Curve::getSelectedPoint() const
{
	return selectedPoint_;
}

std::vector<Point *> Curve::getSelectablePoints()
{
	std::vector<Point *> selectablePoints;
	for(auto it = points_.begin(); it != points_.end(); ++it)
		selectablePoints.push_back(&(*it));
	return selectablePoints;
}

void Curve::setKnots(std::vector<float> k)
{
	knots = k;
}

std::vector<float> Curve::getKnots() const
{
	return knots;
}

// NOTE: The following knots are a default (which works for QuadraticBSpline).
// Overridden function should be implemented for new curves.

void Curve::distanceKnots()
{
	knots.clear();
	if(points_.size() > 0)
		knots.push_back(0.0);

	for(auto it = points_.begin();
		(it != points_.end()) && (it + 1 != points_.end()); ++it)
	{
		float dist = distance(*it, *(it + 1));
		knots.push_back(knots.back() + dist);
	}
}

void Curve::uniformKnots()
{
	knots.clear();
	for(int i = 0; i < points_.size(); i++)
		knots.push_back(static_cast<float>(i));
}

void Curve::centripitalKnots()
{
	knots.clear();
	if(points_.size() > 0)
		knots.push_back(0.0);

	for(auto it = points_.begin();
		(it != points_.end()) && (it + 1 != points_.end()); ++it)
	{
		float sqrtDist = sqrt(distance(*it, *(it + 1)));
		knots.push_back(knots.back() + sqrtDist);
	}
}

void Curve::updateKnots()
{
	if(knotType == DISTANCE)
		this->distanceKnots();
	else if(knotType == UNIFORM)
		this->uniformKnots();
	else if(knotType == CENTRIPITAL)
		this->centripitalKnots();
}

void Curve::printKnots() const
{
	for(auto it = knots.begin(); it != knots.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void Curve::setKnotType(KnotType kt)
{
	knotType = kt;
}

Curve::KnotType Curve::getKnotType() const
{
	return knotType;
}

Point Curve::frontPoint() const
{
	return points_.front();
}

Point Curve::backPoint() const
{
	return points_.back();
}
