#include "mat3.h"

template <typename T>
mat3_t<T>::mat3_t()
{
  rows[0].set(1, 0, 0);
  rows[1].set(0, 1, 0);
  rows[2].set(0, 0, 1);
}

template<typename T>
mat3_t<T>::mat3_t(const mat3_t & other)
{
  rows[0] = other.rows[0];
  rows[1] = other.rows[1];
  rows[2] = other.rows[2];
}

template<typename T>
void mat3_t<T>::setToZero()
{
  rows[0].set(0, 0, 0);
  rows[1].set(0, 0, 0);
  rows[2].set(0, 0, 0);
}

template<typename T>
void mat3_t<T>::setToIdentity()
{
  rows[0].set(1, 0, 0);
  rows[1].set(0, 1, 0);
  rows[2].set(0, 0, 1);
}

template<typename T>
vec3_t<T> mat3_t<T>::columnVector(size_t i) const
{
  if (i >= 3) {
    i %= 3;
  }
  vec3_t<T> result;
  result.x = rows[0].component(i);
  result.y = rows[1].component(i);
  result.z = rows[2].component(i);
  return result;
}

template<typename T>
mat3_t<T> mat3_t<T>::operator*(const mat3_t<T> & other) const
{
  mat3_t<T> result;

  result.rows[0][0] = rows[0].dot(other.columnVector(0));
  result.rows[0][1] = rows[0].dot(other.columnVector(1));
  result.rows[0][2] = rows[0].dot(other.columnVector(2));
 
  result.rows[1][0] = rows[1].dot(other.columnVector(0));
  result.rows[1][1] = rows[1].dot(other.columnVector(1));
  result.rows[1][2] = rows[1].dot(other.columnVector(2));
  
  result.rows[2][0] = rows[2].dot(other.columnVector(0));
  result.rows[2][1] = rows[2].dot(other.columnVector(1));
  result.rows[2][2] = rows[2].dot(other.columnVector(2));

  return result;
}

template<typename T>
vec3_t<T> mat3_t<T>::operator * (const vec3_t<T> & other) const
{
  vec3_t<T> result;
  result.x = rows[0].dot(other);
  result.y = rows[1].dot(other);
  result.z = rows[2].dot(other);
  return result;
}

template<typename T>
vec3_t<T> & mat3_t<T>::refRowVector(size_t i)
{
  if (i >= 3) {
    i %= 3;
  }
  return rows[i];
}

template<typename T>
void mat3_t<T>::setRowVector(size_t i, const vec3_t<T> & rowVec)
{
  if (i >= 3) {
    i %= 3;
  }
  rows[i] = rowVec;
}

template class mat3_t<float>;
