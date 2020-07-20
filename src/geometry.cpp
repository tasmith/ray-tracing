// geometry.cpp

#include "geometry.h"

// Point3D operators

Point3D Point3D::operator-() const
{
  return Point3D {-x, -y, -z};
}

Point3D Point3D::operator+(Vector3D v) const
{
  return Point3D {x + v.x, y + v.y, z + v.z};
}

Vector3D Point3D::operator-(Point3D p) const
{
  return Vector3D {x - p.x, y - p.y, z - p.z};
}

Point3D Point3D::operator-(Vector3D v) const
{
  return Point3D {x - v.x, y - v.y, z - v.z};
}

// Vector3D operators

Vector3D Vector3D::operator-() const
{
  return Vector3D {-x, -y, -z};
}

Vector3D Vector3D::operator+(Vector3D v) const
{
  return Vector3D {x + v.x, y + v.y, z + v.z};
}

Vector3D Vector3D::operator-(Vector3D v) const
{
  return Vector3D {x - v.x, y - v.y, z - v.z};
}

Point3D Vector3D::operator+(Point3D p) const
{
  return Point3D {x + p.x, y + p.y, z + p.z};
}

