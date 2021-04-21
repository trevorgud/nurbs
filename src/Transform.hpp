#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "Line.hpp"
#include "Point.hpp"

/** Trigonometric functions taking angle as degrees. */
float dcos(float angle);
float dsin(float angle);
float dtan(float angle);

/** Trigonometric functions returning angle as degrees. */
float darccos(float adjacent, float hypotenuse);
float darctan(float opposite, float adjacent);

/** Translate a point by the given vector.
 *
 * @param p The point to rotate.
 * @param v The vector specifying the direction and length of translation.
 * @return The translated point.
 */
Point translate(const Point& p, const Vector& v);

/** Rotate a point around the x-axis by a given angle.
 *
 * @param p The point to rotate.
 * @param angle The angle by which to rotate (in degrees).
 * @return The rotated point.
 */
Point xRotate(const Point& p, float angle);

/** Rotate a point around the y-axis by a given angle.
 *
 * @param p The point to rotate.
 * @param angle The angle by which to rotate (in degrees).
 * @return The rotated point.
 */
Point yRotate(const Point& p, float angle);

/** Rotate a point around the z-axis by a given angle.
 *
 * @param p The point to rotate.
 * @param angle The angle by which to rotate (in degrees).
 * @return The rotated point.
 */
Point zRotate(const Point& p, float angle);

/** Rotate a point around a line by a given angle.
 *
 * @param p The point to rotate.
 * @param line The line around which to rotate the point.
 * @param angle The angle by which to rotate (in degrees).
 * @return The rotated point.
 */
Point rotate(const Point& p, const Line& line, float angle);

#endif
