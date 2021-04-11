#ifndef DEBOOR_HPP_
#define DEBOOR_HPP_

#include "BSplineCurve.hpp"
#include "NurbsSurface.hpp"

//interpolates as weighted by t on f2 and 1-t on f1
float interpolate(float f1, float f2, float t);

//interpolation on Point objects
Point cInterpolate(const Point& p1, const Point& p2, float t);

//Implementation of de Boor algorithm for drawing b spline curves
Point tDeBoor(const BSplineCurve& bsc, float uBar);

//Implementation of the De Boor algorithm for drawing rational nurbs surfaces.
Point tDeBoor3D(const NurbsSurface& surface, float u, float v);

#endif
