#include "Vec3f.hpp"

float Vec3f::sqLen() const
{
  return x * x + y * y + z * z;
}

float Vec3f::dot(const Vec3f &other) const
{
  return x * other.x + y * other.y + z * other.z;
}

Vec3f Vec3f::operator+(const Vec3f &other) const
{
  return { x + other.x, y + other.y, z + other.z };
}

Vec3f Vec3f::operator-(const Vec3f &other) const
{
  return *this + (-other);
}

Vec3f Vec3f::operator-() const
{
  return { -x, -y, -z };
}

Vec3f Vec3f::operator*(float fac) const
{
  return { x * fac, y * fac, z * fac };
}

Vec3f Vec3f::operator/(float fac) const
{
  return *this * (1 / fac);
}

Vec3f &Vec3f::operator+=(const Vec3f &other)
{
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

Vec3f &Vec3f::operator-=(const Vec3f &other)
{
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

Vec3f &Vec3f::operator*=(float fac)
{
  x *= fac;
  y *= fac;
  z *= fac;
  return *this;
}

Vec3f &Vec3f::operator/=(float fac)
{
  *this *= 1 / fac;
  return *this;
}
