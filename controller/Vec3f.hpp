#pragma once

struct Vec3f
{
  float x;
  float y;
  float z;
  
  /**
   * Returns the square length of the vector.
   */
  float sqLen() const;

  /**
   * Returns the dot product of this vector with another.
   *
   * @param other the other dot product factor.
   */
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
