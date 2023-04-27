/// \brief Vector4.cpp
/// \brief Definitions of Vector4 class member and associated global functions.
/// \author Chad Hogg
/// \version A07

// For sqrt() and fabs().
#include <cmath>
// For output control.
#include <iomanip>

// Local includes.
#include "Vector4.hpp"

Vector4::Vector4 ()
{
  set (0.0f);
}

Vector4::Vector4 (float xyzw)
{
  set (xyzw);
}

Vector4::Vector4 (float x, float y, float z, float w)
{
  set (x, y, z, w);
}

const float*
Vector4::data () const
{
  return &m_x;
}

void
Vector4::set (float xyzw)
{
  set (xyzw, xyzw, xyzw, xyzw);
}

void
Vector4::set (float x, float y, float z, float w)
{
  m_x = x;
  m_y = y;
  m_z = z;
  m_w = w;
}

float
Vector4::dot (const Vector4& v) const
{
  return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z + m_w * v.m_w;
}

float
Vector4::length () const
{
  return sqrt (m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
}

void
Vector4::normalize ()
{
  float len = length ();
  m_x /= len;
  m_y /= len;
  m_z /= len;
  m_w /= len;
}

void
Vector4::negate ()
{
  m_x *= -1.0f;
  m_y *= -1.0f;
  m_z *= -1.0f;
  m_w *= -1.0f;
}

Vector4&
Vector4::operator+= (const Vector4& v)
{
  m_x += v.m_x;
  m_y += v.m_y;
  m_z += v.m_z;
  m_w += v.m_w;
  return *this;
}

Vector4&
Vector4::operator-= (const Vector4& v)
{
  m_x -= v.m_x;
  m_y -= v.m_y;
  m_z -= v.m_z;
  m_w -= v.m_w;
  return *this;
}

Vector4&
Vector4::operator*= (float s)
{
  m_x *= s;
  m_y *= s;
  m_z *= s;
  m_w *= s;
  return *this;
}

Vector4&
Vector4::operator*= (const Vector4& v)
{
  m_x *= v.m_x;
  m_y *= v.m_y;
  m_z *= v.m_z;
  m_w *= v.m_w;
  return *this;
}

Vector4&
Vector4::operator/= (float s)
{
  m_x /= s;
  m_y /= s;
  m_z /= s;
  m_w /= s;
  return *this;
}

Vector4
operator+ (const Vector4& v1, const Vector4& v2)
{
  return Vector4 (v1) += v2;
}

Vector4
operator- (const Vector4& v1, const Vector4& v2)
{
  return Vector4 (v1) -= v2;
}

Vector4
operator- (const Vector4& v)
{
  Vector4 result (v);
  result.negate ();
  return result;
}

Vector4
operator* (const Vector4& v1, const Vector4& v2)
{
  return Vector4 (v1) *= v2;
}

Vector4
operator* (float s, const Vector4& v)
{
  return Vector4 (v) *= s;
}

Vector4
operator* (const Vector4& v, float s)
{
  return Vector4 (v) *= s;
}

Vector4
operator/ (const Vector4& v, float s)
{
  return Vector4 (v) /= s;
}

std::ostream&
operator<< (std::ostream& out, const Vector4& v)
{
  out << std::fixed << std::setprecision(2)
      << std::setw(10) << v.m_x
      << std::setw(10) << v.m_y
      << std::setw(10) << v.m_z
      << std::setw(10) << v.m_w;
  return out;
}

bool
operator== (const Vector4& v1, const Vector4& v2)
{
  const float EPSILON = 0.00001f;
  return (fabs(v1.m_x - v2.m_x) < EPSILON) &&
    (fabs(v1.m_y - v2.m_y) < EPSILON) &&
    (fabs(v1.m_z - v2.m_z) < EPSILON) &&
    (fabs(v1.m_w - v2.m_w) < EPSILON);
}
