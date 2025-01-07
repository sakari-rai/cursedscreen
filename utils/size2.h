#ifndef _SIZE2_H_
#define _SIZE2_H_

template<typename T>
class size2_t {
public:
  size2_t(T _w = 0, T _h = 0) : w(_w), h(_h) {}

  void operator = (const size2_t & other) {
    w = other.w;
    h = other.h;
  }

  T area() const {
    return w*h;
  }

  T w;
  T h;
};

typedef size2_t<int> isize2_t;
typedef size2_t<float> fsize2_t;

#endif
