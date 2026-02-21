#include "Vec3f.hpp"

float Vec3f::sqLen()
{
  return x * x + y * y + z * z;
}

Vec3f Vec3f::operator+(const Vec3f &other)
{
  return { x - other.x, y - other.y, z - other.z };
}

Vec3f Vec3f::operator-(const Vec3f &other)
{
  return *this + (-other);
}

Vec3f Vec3f::operator-()
{
  return { -x, -y, -z };
}

Vec3f Vec3f::operator*(float fac)
{
  return { x * fac, y * fac, z * fac };
}

Vec3f Vec3f::operator/(float fac)
{
  return *this * (1 / fac);
}
