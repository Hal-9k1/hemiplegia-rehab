#pragma once

struct Vec3f
{
  float x;
  float y;
  float z;
  
  float sqLen() const;
  float dot(const Vec3f &other) const;
  Vec3f operator+(const Vec3f &other) const;
  Vec3f operator-() const;
  Vec3f operator-(const Vec3f &other) const;
  Vec3f operator*(float fac) const;
  Vec3f operator/(float fac) const;
  Vec3f &operator+=(const Vec3f &other);
  Vec3f &operator-=(const Vec3f &other);
  Vec3f &operator*=(float fac);
  Vec3f &operator/=(float fac);
};
