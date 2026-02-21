#pragma once

struct Vec3f
{
  float x;
  float y;
  float z;
  
  float sqLen();
  Vec3f operator+(const Vec3f &other);
  Vec3f operator-();
  Vec3f operator-(const Vec3f &other);
  Vec3f operator*(float fac);
  Vec3f operator/(float fac);
};
