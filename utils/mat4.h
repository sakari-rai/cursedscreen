#ifndef _MAT4_H_
#define _MAT4_H_

#include "vec4.h"
#include <stdbool.h>

/**
 * 4x4 matrix class 
 * 
 **/

template<typename T>
class mat4_t {
public:
  // Default constructor constructs an identity matrix.
  mat4_t();

  // Copy constructor
  mat4_t(const mat4_t & other);

  // Construct matrix using pointer to T type values.
  // Array is expected to be in row-major order.
  mat4_t(const T * values);

  void setToIdentity();
  void setToZero();

  vec4_t<T> columnVector(size_t i) const;

  mat4_t operator * (const mat4_t & other) const;
  vec4_t<T> operator * (const vec4_t<T> & other) const;

  vec4_t<T> & refRowVector(size_t i);

  void setRowVector(size_t i, const vec4_t<T> & rowVec);

  void translate(const vec3_t<T> & vector);
  void rotate(T angle, const vec3_t<T> & vector);
  void scale(const vec3_t<T> & scale);

  void rotateAngles(const vec3_t<T> & angles);

  void transpose();
  mat4_t<T> transposed();

private:

  vec4_t<T> rows[4];

};

typedef mat4_t<float> fmat4_t;

#endif
