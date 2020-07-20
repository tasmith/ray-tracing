// geometry.h

#pragma once

struct Vector3D;
struct Point3D;

struct Point3D {
  double x {0.0};
  double y {0.0};
  double z {0.0};

  Point3D operator-() const;

  Point3D operator+(Vector3D v) const;
  Point3D operator-(Vector3D v) const;
  Vector3D operator-(Point3D p) const;
};

struct Vector3D {
  double x {0.0};
  double y {0.0};
  double z {0.0};

  Vector3D operator-() const;

  Vector3D operator+(Vector3D v) const;
  Vector3D operator-(Vector3D v) const;
  Point3D operator+(Point3D p) const;
};


