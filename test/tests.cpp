#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "geometry.h"

TEST_CASE("Adding two vectors")
{
  Vector3D v1 {3, -2, 5};
  Vector3D v2 {-2, 3, 1};
  Vector3D v3 = v1 + v2;
  CHECK(v3.x == 1);
  CHECK(v3.y == 1);
  CHECK(v3.z == 6);
}

TEST_CASE("Subtracting two points")
{
  Point3D p1 {3, 2, 1};
  Point3D p2 {5, 6, 7};
  Vector3D v = p1 - p2;
  CHECK(v.x == -2);
  CHECK(v.y == -4);
  CHECK(v.z == -6);
}

TEST_CASE("Subtract a vector from a point")
{
  Point3D p {3, 2, 1};
  Vector3D v {5, 6, 7};
  Point3D p2 = p - v;
  CHECK(p2.x == -2);
  CHECK(p2.y == -4);
  CHECK(p2.z == -6);
}

TEST_CASE("Subtracting two vectors")
{
  Vector3D v1 {3, 2, 1};
  Vector3D v2 {5, 6, 7};
  Vector3D v3 = v1 - v2;
  CHECK(v3.x == -2);
  CHECK(v3.y == -4);
  CHECK(v3.z == -6);
}

TEST_CASE("Subtracting a vector from zero vector")
{
  Vector3D zero {0,0,0};
  Vector3D v {1, -2, 3};
  Vector3D v3 = zero - v;
  CHECK(v3.x == -1);
  CHECK(v3.y == 2);
  CHECK(v3.z == -3);
}

TEST_CASE("Negate a point")
{
  Point3D p {1, -2, 3};
  Point3D p2 = -p;
  CHECK(p2.x == -1);
  CHECK(p2.y == 2);
  CHECK(p2.z == -3);
}

TEST_CASE("Negate a vector")
{
  Vector3D v {1, -2, 3};
  Vector3D v2 = -v;
  CHECK(v2.x == -1);
  CHECK(v2.y == 2);
  CHECK(v2.z == -3);
}

