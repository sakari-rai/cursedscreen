#ifndef _RECT2_H_
#define _RECT2_H_

#include <sstream>
#include <vector>
#include "vec2.h"
#include "size2.h"

template<typename T>
class rect2_t {
public:
  rect2_t() {}

  rect2_t(T x, T y, T w, T h) :
    tl(x, y), rsize(w, h) {}

  rect2_t(const vec2_t<T> & topleft, const size2_t<T> & size):
    tl(topleft), rsize(size) {}

  rect2_t(const vec2_t<T>& topLeft, const vec2_t<T>& bottomRight) :
    tl(topLeft), rsize(bottomRight.x - topLeft.x, bottomRight.y - topLeft.y) {}

  rect2_t(const rect2_t<T> & other) {
    tl = other.tl;
    rsize = other.rsize;
  }

  std::string str() const {
    std::stringstream ss;

    ss << "(" << tl.x << ", " << tl.y << ") - (" << rsize.w << ", " << rsize.h << ")";

    return ss.str();
  }

  rect2_t<T> & operator = (const rect2_t<T> &
   other) {
    tl = other.tl;
    rsize = other.rsize;
    return *this;
  }

  void set(T x, T y, T w, T h) {
    tl.x = x;
    tl.y = y;
    rsize.w = w;
    rsize.h = h;
  }

  vec2_t<T> topLeft() const { return tl; }
  vec2_t<T> & refTopLeft() { return tl; }

  size2_t<T> size() const { return rsize; }
  size2_t<T> & refSize() { return rsize; }

  vec2_t<T> bottomRight() const {
    return vec2_t<T>(tl.x + rsize.w, tl.y + rsize.h);
  }

  vec2_t<T> center() const {
    return vec2_t<T>(tl.x + rsize.w / 2, tl.y + rsize.h / 2);
  }

  rect2_t<T> scaled(vec2_t<T> by) {
    const T w = rsize.w * by.x;
    const T h = rsize.h * by.y;
    return {
      tl.x + (rsize.w - w) / 2,
      tl.y + (rsize.h - h) / 2,
      w, h
    };
  }

  rect2_t<T> translated(vec2_t<T> by) const {
    return {
      tl + by,
      rsize
    };
  }

  void setRight(T right) {
    if (right < tl.x) {
      rsize.w = tl.x - right;
      tl.x = right;
    } else {
      rsize.w = right - tl.x;
    }
  }

  void setBottom(T bottom) {
    if (bottom < tl.y) {
      rsize.h = tl.y - bottom;
      tl.y = bottom;
    } else {
      rsize.h = bottom - tl.y;
    }
  }

  void setBottomRight(const vec2_t<T> & br) {
    if (br.x < tl.x) {
      rsize.w = tl.x - br.x;
      tl.x = br.x;
    } else {
      rsize.w = br.x - tl.y;
    }

    if (br.y < tl.y) {
      rsize.h = tl.y - br.y;
      tl.y = br.y;
    } else {
      rsize.h = br.y - tl.y;
    }
  }

  bool contains(const vec2_t<T>& pt) {
    if (pt.x < tl.x) {return false;}
    if (pt.x > (tl.x + rsize.w)) {return false;}
    if (pt.y < tl.y) {return false;}
    if (pt.y > (tl.y + rsize.h)) {return false;}
    return true;
  }

  std::vector<vec2_t<T>> toVertices() const {
    return {
      {topLeft().x, topLeft().y},
      {bottomRight().x, topLeft().y},
      {bottomRight().x, bottomRight().y},
      {topLeft().x, bottomRight().y}
    };
  }

  T width() const {return rsize.w;}
  T height() const {return rsize.h;}

private:
  vec2_t<T> tl;
  size2_t<T> rsize;

};

typedef rect2_t<int> irect2_t;
typedef rect2_t<float> frect2_t;

#endif
