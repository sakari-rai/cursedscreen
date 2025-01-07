#include "mat4.h"

template <typename T>
mat4_t<T>::mat4_t()
{
  rows[0].set(1, 0, 0, 0);
  rows[1].set(0, 1, 0, 0);
  rows[2].set(0, 0, 1, 0);
  rows[3].set(0, 0, 0, 1);
}

template<typename T>
mat4_t<T>::mat4_t(const mat4_t & other)
{
  rows[0] = other.rows[0];
  rows[1] = other.rows[1];
  rows[2] = other.rows[2];
  rows[3] = other.rows[3];
}

template<>
mat4_t<float>::mat4_t(const float * values)
{
  rows[0].set(values[0], values[1], values[2], values[3]);
  rows[1].set(values[4], values[5], values[6], values[7]);
  rows[2].set(values[8], values[9], values[10], values[11]);
  rows[3].set(values[12], values[13], values[14], values[15]);
}

template<typename T>
void mat4_t<T>::setToZero()
{
  rows[0].set(0, 0, 0, 0);
  rows[1].set(0, 0, 0, 0);
  rows[2].set(0, 0, 0, 0);
  rows[3].set(0, 0, 0, 0);
}

template<typename T>
void mat4_t<T>::setToIdentity()
{
  rows[0].set(1, 0, 0, 0);
  rows[1].set(0, 1, 0, 0);
  rows[2].set(0, 0, 1, 0);
  rows[3].set(0, 0, 0, 1);
}

template<typename T>
vec4_t<T> mat4_t<T>::columnVector(size_t i) const
{
  if (i >= 4) {
    i %= 4;
  }
  vec4_t<T> result;
  result.x = rows[0].component(i);
  result.y = rows[1].component(i);
  result.z = rows[2].component(i);
  result.w = rows[3].component(i);
  return result;
}

template<typename T>
mat4_t<T> mat4_t<T>::operator*(const mat4_t<T> & other) const
{
  mat4_t<T> result;

  result.rows[0][0] = rows[0].dot(other.columnVector(0));
  result.rows[0][1] = rows[0].dot(other.columnVector(1));
  result.rows[0][2] = rows[0].dot(other.columnVector(2));
  result.rows[0][3] = rows[0].dot(other.columnVector(3));
 
  result.rows[1][0] = rows[1].dot(other.columnVector(0));
  result.rows[1][1] = rows[1].dot(other.columnVector(1));
  result.rows[1][2] = rows[1].dot(other.columnVector(2));
  result.rows[1][3] = rows[1].dot(other.columnVector(3));
  
  result.rows[2][0] = rows[2].dot(other.columnVector(0));
  result.rows[2][1] = rows[2].dot(other.columnVector(1));
  result.rows[2][2] = rows[2].dot(other.columnVector(2));
  result.rows[2][3] = rows[2].dot(other.columnVector(3));

  result.rows[3][0] = rows[3].dot(other.columnVector(0));
  result.rows[3][1] = rows[3].dot(other.columnVector(1));
  result.rows[3][2] = rows[3].dot(other.columnVector(2));
  result.rows[3][3] = rows[3].dot(other.columnVector(3));

  return result;
}

template<typename T>
vec4_t<T> mat4_t<T>::operator * (const vec4_t<T> & other) const
{
  vec4_t<T> result;
  result.x = rows[0].dot(other);
  result.y = rows[1].dot(other);
  result.z = rows[2].dot(other);
  result.w = rows[3].dot(other);
  return result;
}

template<typename T>
vec4_t<T> & mat4_t<T>::refRowVector(size_t i)
{
  if (i >= 4) {
    i %= 4;
  }
  return rows[i];
}

template<typename T>
void mat4_t<T>::setRowVector(size_t i, const vec4_t<T> & rowVec)
{
  if (i >= 4) {
    i %= 4;
  }
  rows[i] = rowVec;
}

template<>
void mat4_t<float>::translate(const vec3_t<float> & vector)
{
  const float matdata[16] = {
    1.0f, 0.0f, 0.0f, vector.x,
    0.0f, 1.0f, 0.0f, vector.y,
    0.0f, 0.0f, 1.0f, vector.z,
    0.0f, 0.0f, 0.0f, 1.0f,
  };
  
  mat4_t<float> tm(matdata);
  mat4_t<float> self(*this);
  mat4_t<float> result = self * tm;
  
  this->rows[0] = result.rows[0];
  this->rows[1] = result.rows[1];
  this->rows[2] = result.rows[2];
  this->rows[3] = result.rows[3];
}

template<>
void mat4_t<float>::scale(const vec3_t<float> & scale)
{
  const float matdata[16] = {
    scale.x, 0.0f, 0.0f, 0.0f,
    0.0f, scale.y, 0.0f, 0.0f,
    0.0f, 0.0f, scale.z, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
  };
  
  mat4_t<float> tm(matdata);
  mat4_t<float> self(*this);
  mat4_t<float> result = self * tm;
  
  this->rows[0] = result.rows[0];
  this->rows[1] = result.rows[1];
  this->rows[2] = result.rows[2];
  this->rows[3] = result.rows[3];
}

template<>
void mat4_t<float>::rotate(float angle, const vec3_t<float> & vector)
{
  const float cost = cosf(angle);
  const float sint = sinf(angle);

  vec3_t<float> u = vector.normalized();

  const float matdata[16] = {
    cost + u.x * u.x * (1.0f - cost), u.x * u.y * (1.0f - cost) - u.z * sint, u.x * u.z * (1.0f - cost) + u.y * sint, 0.0f,
    u.y * u.x * (1.0f - cost) + u.z * sint, cost + u.y * u.y * (1.0f - cost), u.y * u.z * (1.0f - cost) - u.x * sint, 0.0f,
    u.z * u.x * (1.0f - cost) - u.y * sint, u.z * u.y * (1.0f - cost) + u.x * sint, cost * u.z * u.z * (1.0f - cost), 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
  
  mat4_t<float> tm(matdata);
  mat4_t<float> self(*this);
  mat4_t<float> result = self * tm;
  
  this->rows[0] = result.rows[0];
  this->rows[1] = result.rows[1];
  this->rows[2] = result.rows[2];
  this->rows[3] = result.rows[3];
}

template<>
void mat4_t<float>::rotateAngles(const vec3_t<float> & angles)
{
  const float cosX = cosf(angles.x);
  const float sinX = sinf(angles.x);
  const float cosY = cosf(angles.y);
  const float sinY = sinf(angles.y);
  const float cosZ = cosf(angles.z);
  const float sinZ = sinf(angles.z);

  const float rotx[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, cosX, -sinX, 0.0f,
    0.0f, sinX, cosX, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };

  const float roty[16] = {
    cosY, 0.0f, sinY, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    -sinY, 0.0f, cosY, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };

  const float rotz[16] = {
    cosZ, -sinZ, 0.0f, 0.0f,
    sinZ, cosZ, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };

  mat4_t<float> pitch(rotx);
  mat4_t<float> yaw(roty);
  mat4_t<float> roll(rotz);

  mat4_t<float> tm = roll * yaw * pitch;
  mat4_t<float> self(*this);
  mat4_t<float> result = self * tm;

  this->rows[0] = result.rows[0];
  this->rows[1] = result.rows[1];
  this->rows[2] = result.rows[2];
  this->rows[3] = result.rows[3];
}

template<>
void mat4_t<float>::transpose()
{
  mat4_t<float> self(*this);
  this->rows[0] = self.columnVector(0);
  this->rows[1] = self.columnVector(1);
  this->rows[2] = self.columnVector(2);
  this->rows[3] = self.columnVector(3);
}

template<>
mat4_t<float> mat4_t<float>::transposed()
{
  mat4_t<float> result;
  result.rows[0] = columnVector(0);
  result.rows[1] = columnVector(1);
  result.rows[2] = columnVector(2);
  result.rows[3] = columnVector(3);
  return result;
}

template class mat4_t<float>;
