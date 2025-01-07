#ifndef _MAT3_H_
#define _MAT3_H_

#include "vec3.h"
#include <stdbool.h>

/**
 * 3x3 matrix class 
 * 
 **/

template<typename T>
class mat3_t {
public:
  mat3_t();
  mat3_t(const mat3_t & other);
  
  void setToIdentity();
  void setToZero();

  vec3_t<T> columnVector(size_t i) const;

  mat3_t operator * (const mat3_t & other) const;
  vec3_t<T> operator * (const vec3_t<T> & other) const;

  vec3_t<T> & refRowVector(size_t i);

  void setRowVector(size_t i, const vec3_t<T> & rowVec);

private:

  vec3_t<T> rows[3];

};

typedef mat3_t<float> fmat3_t;

#endif
