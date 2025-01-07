#ifndef _VEC4_H_
#define _VEC4_H_

#include <cmath>
#include "vec3.h"

template<typename T>
class vec4_t {
public:
  vec4_t(T x0 = 0, T y0 = 0, T z0 = 0, T w0 = 1) : x(x0), y(y0), z(z0), w(w0) {} 
  vec4_t(const vec4_t<T> & other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
  vec4_t(const vec3_t<T> & v3, T w0 = 1) : x(v3.x), y(v3.y), z(v3.z), w(w0) {}

  vec4_t operator + (const vec4_t & other) const {
    return vec4_t(x + other.x, y + other.y, z + other.z, w + other.w);
  }

  vec4_t operator - (const vec4_t & other) const {
    return vec4_t(x - other.x, y - other.y, z - other.z, w - other.w);
  }

  vec4_t operator * (T scalar) const {
    return vec4_t(x * scalar, y * scalar, z * scalar, w * scalar);
  }

  vec4_t operator / (T div) const {
    vec4_t ret(x, y, z, w);
    if (div != 0) {
      ret.x /= div;
      ret.y /= div;
      ret.z /= div;
      ret.w /= div;
    }
    return ret;
  }

  vec4_t & operator = (const vec4_t & other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
  }

  vec4_t & operator += (const vec4_t & other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
  }

  vec4_t & operator -= (const vec4_t & other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
  }

  vec4_t & operator *= (T scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
  }
  
  vec4_t & operator /= (T div) {
    if (div != 0) {
      x /= div;
      y /= div;
      z /= div;
      w /= div;
    }
    return *this;
  }

  T & operator [] (size_t i) {
    // silently limit element index to proper range if
    // argument is invalid.
    if (i >= 4) {
      i %= 4;
    }

    switch(i) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
      case 3:
      default:    // makes compiler happy...should not be the case ever.
        return w;
    }
  }

  T component(size_t i) const {
    // silently limit element index to proper range if
    // argument is invalid.
    if (i >= 4) {
      i %= 4;
    }

    switch(i) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
      case 3:
      default:    // makes compiler happy...should not be the case ever.
        return w;
    }
  }

  vec4_t normalized() const {
    vec4_t result;
    T len = length();
    result.x = x / len;
    result.y = y / len;
    result.z = z / len;
    result.w = w / len;
    return result;
  }

  vec4_t & normalize() {
    T len = length();
    x = x / len;
    y = y / len;
    z = z / len;
    w = w / len;
    return *this;
  }

  T dot(const vec4_t & other) const {
    return (x * other.x + y * other.y + z * other.z + w * other.w);
  }

  void set(T x_, T y_, T z_, T w_) {
    x = x_;
    y = y_;
    z = z_;
    w = w_;
  }

  vec3_t<T> xyz() const {
    return vec3_t<T>(x, y, z);
  }

  T length() const {
    return (T)sqrt((double)(x*x) + (double)(y*y) + (double)(z*z) + (double)(w*w));
  }

  T x;
  T y;
  T z;
  T w;
};

typedef vec4_t<int> ivec4_t;
typedef vec4_t<float> fvec4_t;

#endif
