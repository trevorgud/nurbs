#include <catch2/catch.hpp>

#include "Transform.hpp"

#include "Line.hpp"
#include "Point.hpp"

#define EPSILON 1.0e-8
#define SQRT_2 1.41421356237

// Rotate around a vertical line centered at the origin.
Point rotateOrigin(const Point& pt, float angle) {
  const Line ln(Point(0, 0, 0), Point(0, 1, 0));
  return rotate(pt, ln, angle);
}

TEST_CASE("Test cases for transformations", "[Transform.hpp]")
{
  SECTION("Trivial rotations around x-axis")
  {
    REQUIRE(length(Line(
      xRotate(Point(1, 0, 0), 0.0),
      Point(1, 0, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(1, 0, 0), 45.0),
      Point(1, 0, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(1, 0, 0), 90.0),
      Point(1, 0, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(1, 0, 0), -45.0),
      Point(1, 0, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(1, 0, 0), 360.0),
      Point(1, 0, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(1, 0, 0), 361.0),
      Point(1, 0, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(1, 0, 0), 100000.0),
      Point(1, 0, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(1, 0, 0), -100000.0),
      Point(1, 0, 0)
    )) < EPSILON);
  }

  SECTION("Rotations around x-axis")
  {
    REQUIRE(length(Line(
      xRotate(Point(0, 1, 0), 0.0),
      Point(0, 1, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(0, 1, 0), 45.0),
      Point(0, SQRT_2 / 2, SQRT_2 / 2)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(0, 0, 1), 45.0),
      Point(0, -SQRT_2 / 2, SQRT_2 / 2)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(0, 1, 0), 90.0),
      Point(0, 0, 1)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(0, 0, 1), 90.0),
      Point(0, -1, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(0, 1, 0), -45.0),
      Point(0, SQRT_2 / 2, -SQRT_2 / 2)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(0, 0, 1), -45.0),
      Point(0, SQRT_2 / 2, SQRT_2 / 2)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(0, 1, 0), 360.0),
      Point(0, 1, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(0, 1, 0), 361.0),
      Point(0, dcos(1.0), dsin(1.0))
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(0, 1, 0), 361.0),
      xRotate(Point(0, 1, 0), 1.0)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(0, 1, 0), 100000.0),
      Point(0, dsin(10.0), -dcos(10.0))
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(0, 0, 1), -100000.0),
      Point(0, -dcos(10.0), dsin(10.0))
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(0, 1, 1), 45.0),
      Point(0, 0, SQRT_2)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(0, -1, 1), 45.0),
      Point(0, -SQRT_2, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(0, 1, -1), 45.0),
      Point(0, SQRT_2, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      xRotate(Point(0, -1, -1), 45.0),
      Point(0, 0, -SQRT_2)
    )) < EPSILON);
  }

  SECTION("Trivial rotations around y-axis")
  {
    REQUIRE(length(Line(
      yRotate(Point(0, 1, 0), 0.0),
      Point(0, 1, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(0, 1, 0), 45.0),
      Point(0, 1, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(0, 1, 0), 90.0),
      Point(0, 1, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(0, 1, 0), -45.0),
      Point(0, 1, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(0, 1, 0), 360.0),
      Point(0, 1, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(0, 1, 0), 361.0),
      Point(0, 1, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(0, 1, 0), 100000.0),
      Point(0, 1, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(0, 1, 0), -100000.0),
      Point(0, 1, 0)
    )) < EPSILON);
  }

  SECTION("Rotations around y-axis")
  {
    REQUIRE(length(Line(
      yRotate(Point(1, 0, 0), 0.0),
      Point(1, 0, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(1, 0, 0), 45.0),
      Point(SQRT_2 / 2, 0, -SQRT_2 / 2)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(0, 0, 1), 45.0),
      Point(SQRT_2 / 2, 0, SQRT_2 / 2)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(1, 0, 0), 90.0),
      Point(0, 0, -1)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(0, 0, 1), 90.0),
      Point(1, 0, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(1, 0, 0), -45.0),
      Point(SQRT_2 / 2, 0, SQRT_2 / 2)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(0, 0, 1), -45.0),
      Point(-SQRT_2 / 2, 0, SQRT_2 / 2)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(1, 0, 0), 360.0),
      Point(1, 0, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(1, 0, 0), 361.0),
      Point(dcos(1.0), 0, -dsin(1.0))
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(1, 0, 0), 361.0),
      yRotate(Point(1, 0, 0), 1.0)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(1, 0, 0), 100000.0),
      Point(dsin(10.0), 0, dcos(10.0))
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(0, 0, 1), -100000.0),
      Point(dcos(10.0), 0, dsin(10.0))
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(1, 0, 1), 45.0),
      Point(SQRT_2, 0, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(-1, 0, 1), 45.0),
      Point(0, 0, SQRT_2)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(1, 0, -1), 45.0),
      Point(0, 0, -SQRT_2)
    )) < EPSILON);
    REQUIRE(length(Line(
      yRotate(Point(-1, 0, -1), 45.0),
      Point(-SQRT_2, 0, 0)
    )) < EPSILON);
  }

  SECTION("Trivial rotations around z-axis")
  {
    REQUIRE(length(Line(
      zRotate(Point(0, 0, 1), 0.0),
      Point(0, 0, 1)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(0, 0, 1), 45.0),
      Point(0, 0, 1)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(0, 0, 1), 90.0),
      Point(0, 0, 1)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(0, 0, 1), -45.0),
      Point(0, 0, 1)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(0, 0, 1), 360.0),
      Point(0, 0, 1)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(0, 0, 1), 361.0),
      Point(0, 0, 1)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(0, 0, 1), 100000.0),
      Point(0, 0, 1)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(0, 0, 1), -100000.0),
      Point(0, 0, 1)
    )) < EPSILON);
  }

  SECTION("Rotations around z-axis")
  {
    REQUIRE(length(Line(
      zRotate(Point(1, 0, 0), 0.0),
      Point(1, 0, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(1, 0, 0), 45.0),
      Point(SQRT_2 / 2, SQRT_2 / 2, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(0, 1, 0), 45.0),
      Point(-SQRT_2 / 2, SQRT_2 / 2, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(1, 0, 0), 90.0),
      Point(0, 1, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(0, 1, 0), 90.0),
      Point(-1, 0, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(1, 0, 0), -45.0),
      Point(SQRT_2 / 2, -SQRT_2 / 2, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(0, 1, 0), -45.0),
      Point(SQRT_2 / 2, SQRT_2 / 2, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(1, 0, 0), 360.0),
      Point(1, 0, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(1, 0, 0), 361.0),
      Point(dcos(1.0), dsin(1.0), 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(1, 0, 0), 361.0),
      zRotate(Point(1, 0, 0), 1.0)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(1, 0, 0), 100000.0),
      Point(dsin(10.0), -dcos(10.0), 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(0, 1, 0), -100000.0),
      Point(-dcos(10.0), dsin(10.0), 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(1, 1, 0), 45.0),
      Point(0, SQRT_2, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(-1, 1, 0), 45.0),
      Point(-SQRT_2, 0, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(1, -1, 0), 45.0),
      Point(SQRT_2, 0, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      zRotate(Point(-1, -1, 0), 45.0),
      Point(0, -SQRT_2, 0)
    )) < EPSILON);
  }

  SECTION("Rotations around vertical origin line")
  {
    REQUIRE(length(Line(
      rotateOrigin(Point(1, 0, 0), 45.0),
      Point(SQRT_2 / 2, 0, -SQRT_2 / 2)
    )) < EPSILON);
    REQUIRE(length(Line(
      rotateOrigin(Point(1, 1, 0), 45.0),
      Point(SQRT_2 / 2, 1, -SQRT_2 / 2)
    )) < EPSILON);
    REQUIRE(length(Line(
      rotateOrigin(Point(1, -1, 0), 45.0),
      Point(SQRT_2 / 2, -1, -SQRT_2 / 2)
    )) < EPSILON);
    REQUIRE(length(Line(
      rotateOrigin(Point(1, 0, 0), -45.0),
      Point(SQRT_2 / 2, 0, SQRT_2 / 2)
    )) < EPSILON);
    REQUIRE(length(Line(
      rotateOrigin(Point(1, 1, 0), -45.0),
      Point(SQRT_2 / 2, 1, SQRT_2 / 2)
    )) < EPSILON);
    REQUIRE(length(Line(
      rotateOrigin(Point(1, -1, 0), -45.0),
      Point(SQRT_2 / 2, -1, SQRT_2 / 2)
    )) < EPSILON);
    REQUIRE(length(Line(
      rotateOrigin(Point(1, 1, 0), 1.0),
      Point(dcos(1.0), 1, -dsin(1.0))
    )) < EPSILON);
    REQUIRE(length(Line(
      rotateOrigin(Point(1, -1, 0), 1.0),
      Point(dcos(1.0), -1, -dsin(1.0))
    )) < EPSILON);
    REQUIRE(length(Line(
      rotateOrigin(Point(1, 1, 1), 45.0),
      Point(SQRT_2, 1, 0)
    )) < EPSILON);
    REQUIRE(length(Line(
      rotateOrigin(Point(1, -1, 1), 45.0),
      Point(SQRT_2, -1, 0)
    )) < EPSILON);
  }

  SECTION("Rotations around origin line on XZ plane")
  {
    // Closure to rotate a point around the line (0, 0, 0) -> (1, 0, 0).
    auto rotate1x = [](const Point& pt, float angle) -> Point {
      const Line ln(Point(0, 0, 0), Point(1, 0, 0));
      return rotate(pt, ln, angle);
    };

    REQUIRE(length(Line(
      rotate1x(Point(0, 0, -1), 45.0),
      Point(0, SQRT_2 / 2, -SQRT_2 / 2)
    )) < EPSILON);
  }
}
