#ifndef CURVE_HPP_
#define CURVE_HPP_

#include "Point.hpp"

#include <memory>
#include <vector>

// Base class for all other curve classes.
class Curve
{
public:
	enum Type
	{
		BEZIER,
		AITKEN,
		PIECEWISE,
		BSPLINE,
		QUAD_BSPLINE,
		CUBIC_BSPLINE
	};

	enum KnotType
	{
		DISTANCE,
		UNIFORM,
		CENTRIPITAL,
		CUSTOM
	};

	Curve(Type type, const std::vector<Point>& points = {}, int selectedPoint = 0);

	void setPoints(const std::vector<Point>& points);

	std::vector<Point> getPoints() const;

	const Point* getPoint(int pos) const;
	const Point* getPoint() const;

	Type getType() const;
	bool isAggregate() const;

	virtual void addPoint(const Point& point);

	virtual void insertPoint(const Point& point);
	virtual void insertPoint(const Point& point, int pos);

	virtual void movePoint(const Point& point);
	virtual void movePoint(const Point& point, int pos);

	virtual void deletePoint();
	virtual void deletePoint(int pos);

	Point frontPoint() const;
	Point backPoint() const;

	virtual void distanceKnots();
	virtual void uniformKnots();
	virtual void centripitalKnots();
	void updateKnots();

	std::vector<float> getKnots() const;
	void setKnots(std::vector<float> k);
	void setKnotType(KnotType kt);
	KnotType getKnotType() const;

	void printKnots() const;

	int numPoints() const;

	void setSelectedPoint(int selected);

	int getSelectedPoint() const;
	template<class C> std::shared_ptr<C> cast();

	virtual std::vector<Point *> getSelectablePoints();
	virtual Point c(float t) const = 0;
	virtual float tMax() const = 0;
	virtual float tMin() const = 0;

protected:
	std::vector<Point> points_;

	std::vector<float> knots;

	KnotType knotType;

	int selectedPoint_;

private:
	void setType(Type type);

	Type type_;
};

#endif
