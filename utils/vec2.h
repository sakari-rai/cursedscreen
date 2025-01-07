#ifndef _VEC2_H_
#define _VEC2_H_

#include <cmath>
#include <optional>

template<typename T>
class vec2_t {
public:
  vec2_t(T x0 = 0, T y0 = 0) : x(x0), y(y0) {}
  vec2_t(const vec2_t & other) : x(other.x), y(other.y) {}

  vec2_t operator + (const vec2_t & other) const {
    return vec2_t(x + other.x, y + other.y);
  }

  vec2_t operator - (const vec2_t & other) const {
    return vec2_t(x - other.x, y - other.y);
  }

  vec2_t operator * (T scalar) const {
    return vec2_t(x * scalar, y * scalar);
  }

  vec2_t operator / (T div) const {
    vec2_t ret(x, y);
    if (div != 0) {
      ret.x /= div;
      ret.y /= div;
    }
    return ret;
  }

  vec2_t & operator = (const vec2_t & other) {
    x = other.x;
    y = other.y;
    return *this;
  }

  vec2_t & operator += (const vec2_t & other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  vec2_t & operator -= (const vec2_t & other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  vec2_t & operator *= (T scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  vec2_t & operator /= (T div) {
    if (div != 0) {
      x /= div;
      y /= div;
    }
    return *this;
  }

  vec2_t<T> perpendicular(bool cw = false) const {
    if (cw) {
      return {y, -x};
    } else {
      return {-y, x};
    }
  }

  vec2_t<T> scaled(const vec2_t<T>& other) {
    return vec2_t<T>{x * other.x, y * other.y};
  }

  T dot(const vec2_t<T>& other) const {
    return (x * other.x + y * other.y);
  }

  vec2_t<float> rotated(float radians);
  vec2_t<float>& rotate(float radians);

  T length() const {
    if (x == 0 && y == 0) {
      return 0;
    }

    return (T)sqrt((double)(x*x) + (double)(y*y));
  }

  inline bool isZero() const {return length() == 0;}
  
  vec2_t<T>& normalize() {
    T len = length();
    if (len) {
      x /= len;
      y /= len;
    }
    return *this;
  }

  vec2_t<T> normalized() const {
    T len = length();
    if (len) {
      return vec2_t<T>{x / len, y / len};
    }
    return {0.0f, 0.0f};
  }

  std::optional<vec2_t<T>> normalizedSafe() const {
    T len = length();
    if (len) {
      return vec2_t<T>{x / len, y / len};
    }
    return {};
  }

  vec2_t<int> to_ivec2() const {
    return vec2_t<int>(static_cast<int>(std::round(x)), static_cast<int>(std::round(y)));
  }
  
  T x;
  T y;
};

typedef vec2_t<int> ivec2_t;
typedef vec2_t<float> fvec2_t;


#endif
