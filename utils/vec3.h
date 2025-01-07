#ifndef _VEC3_H_
#define _VEC3_H_

#include <cstddef>
#include <cmath>

template<typename T>
class vec3_t {
public:
  vec3_t(T x0 = 0, T y0 = 0, T z0 = 0) : x(x0), y(y0), z(z0) {} 
  vec3_t(const vec3_t & other) : x(other.x), y(other.y), z(other.z) {}

  vec3_t operator + (const vec3_t & other) const {
    return vec3_t(x + other.x, y + other.y, z + other.z);
  }

  vec3_t operator - (const vec3_t & other) const {
    return vec3_t(x - other.x, y - other.y, z - other.z);
  }

  vec3_t operator * (T scalar) const {
    return vec3_t(x * scalar, y * scalar, z * scalar);
  }

  vec3_t operator / (T div) const {
    vec3_t ret(x, y, z);
    if (div != 0) {
      ret.x /= div;
      ret.y /= div;
      ret.z /= div;
    }
    return ret;
  }

  vec3_t & operator = (const vec3_t & other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }

  vec3_t & operator += (const vec3_t & other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  vec3_t & operator -= (const vec3_t & other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }

  vec3_t & operator *= (T scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }
  
  vec3_t & operator /= (T div) {
    if (div != 0) {
      x /= div;
      y /= div;
      z /= div;
    }
    return *this;
  }

  T & operator [] (size_t i) {
    // silently limit element index to proper range if
    // argument is invalid.
    if (i >= 3) {
      i %= 3;
    }

    switch(i) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
      default:    // makes compiler happy...should not be the case ever.
        return z;
    }
  }

  T component(size_t i) const {
    // silently limit element index to proper range if
    // argument is invalid.
    if (i >= 3) {
      i %= 3;
    }

    switch(i) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
      default:    // makes compiler happy...should not be the case ever.
        return z;
    }
  }

  vec3_t normalized() const {
    vec3_t result;
    T len = length();
    result.x = x / len;
    result.y = y / len;
    result.z = z / len;
    return result;
  }

  vec3_t & normalize() {
    T len = length();
    x = x / len;
    y = y / len;
    z = z / len;
    return *this;
  }

  T dot(const vec3_t & other) const {
    return (x * other.x + y * other.y + z * other.z);
  }

  vec3_t cross(const vec3_t & other) const {
    vec3_t result;
    // i  j  k  => result
    // a1 a2 a3 => this
    // b1 b2 b3 => other
    // (a2*b3 - a3*b2)*i - (a1*b3 - a3*b1)*j + (a1*b2 - a2*b1)*k
    result.x =  (y * other.z - z * other.y);
    result.y = -(x * other.z - z * other.x);
    result.z =  (x * other.y - y * other.x);
    return result;
  }

  void set(T x_, T y_, T z_) {
    x = x_;
    y = y_;
    z = z_;
  }

  T length() const {
    return (T)sqrtf((float)(x*x) + (float)(y*y) + (float)(z*z));
  }

  T x;
  T y;
  T z;
};

typedef vec3_t<int> ivec3_t;
typedef vec3_t<float> fvec3_t;

#endif
