#pragma once

/**
 * A 3-component single-precision floating point vector.
 */
struct Vec3f
{
  /**
   * The x component of the vector.
   *
   * In all contexts, represents "right", whatever that means in context.
   */
  float x;
  /**
   * The y component of the vector.
   *
   * In 3D contexts, represents "forward", and in 2D contexts, represents "up", whatever that means
   * in context.
   */
  float y;
  /**
   * The z component of the vector.
   *
   * In 3D contexts, represents "up", whatever that means in context.
   */
  float z;
  
  /**
   * Returns the squared length of the vector.
   *
   * @return the squared length of this vector.
   */
  float sqLen() const;

  /**
   * Returns the dot product of this vector with another.
   *
   * @param other the other dot product factor.
   * @return the dot product of this vector with @a other.
   */
  float dot(const Vec3f &other) const;

  /**
   * Returns the sum of this vector and another.
   *
   * @param other the other addend.
   * @return a new vector which is the elementwise sum of this vector with @a other.
   */
  Vec3f operator+(const Vec3f &other) const;

  /**
   * Returns the negation of this vector.
   *
   * @return an elementwise negated copy of this vector.
   */
  Vec3f operator-() const;

  /**
   * Returns the difference between this vector and another.
   *
   * @param other the other subtractand.
   * @return a new vector which is the elementwise difference between this vector and @a other.
   */
  Vec3f operator-(const Vec3f &other) const;

  /**
   * Returns the product of this vector and a scalar.
   *
   * @param fac the scalar factor.
   * @return a new vector which is the scalar product of this vector and @a fac.
   */
  Vec3f operator*(float fac) const;

  /**
   * Returns the quotient of this vector and a scalar.
   *
   * @param fac the scalar divisor.
   * @return a new vector which is the scalar quotient of this vector and @a fac.
   */
  Vec3f operator/(float fac) const;

  /**
   * Adds another vector to this one in-place.
   *
   * @param other the other addend.
   * @return this vector, after adding @a other in-place.
   */
  Vec3f &operator+=(const Vec3f &other);

  /**
   * Subtracts another vector from this one in-place.
   *
   * @param other the other subtractand.
   * @return this vector, after subtracting @a other in-place.
   */
  Vec3f &operator-=(const Vec3f &other);

  /**
   * Multiplies this vector by a scalar in-place.
   *
   * @param fac the scalar factor.
   * @return this vector, after multiplying by @a fac in-place.
   */
  Vec3f &operator*=(float fac);

  /**
   * Divides this vector by a scalar in-place.
   *
   * @param fac the scalar divisor.
   * @return this vector, after dividing by @a fac in-place.
   */
  Vec3f &operator/=(float fac);
};
