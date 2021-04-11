#ifndef BSPLINECURVE_HPP_
#define BSPLINECURVE_HPP_

#include "Curve.hpp"

#include <vector>

// Data structure for B spline curves, inherits from Curve
class BSplineCurve : public Curve
{
public:
	BSplineCurve();
	BSplineCurve(const std::vector<Point>& points = {}, int kVal = 3);
	BSplineCurve(const std::vector<Point>& points, const std::vector<float>& setKnots, int kVal = 3);

	void setKnots(const std::vector<float>& u);
	std::vector<float> getKnots() const;
	const float* getKnot(int i) const;
	void setKnot(int i, float u);
	// Inserts a control point before pos and updates the knot values
	void insertPointAndKnot(const Point& p, int pos);

	virtual void uniformKnots();
	virtual void distanceKnots();
	virtual void centripitalKnots();

	void setOrder(int order);
	int getOrder() const;

	virtual void movePoint(const Point& p);
	virtual void addPoint(const Point& p);
	virtual void deletePoint();
	virtual void deletePoint(int pos);

	virtual Point c(float t) const;
	virtual float tMax() const;
	virtual float tMin() const;

private:
	int k;
};

#endif
