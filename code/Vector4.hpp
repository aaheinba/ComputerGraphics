/// \file Vector4.hpp
/// \brief Declaration of Vector4 class and any associated global functions.
/// \author Gary M. Zoppetti, Ph.D. & Chad Hogg
/// \version A07

#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include <iostream>

/// \brief A vector with 4 float components (x, y, z, and w).
class Vector4
{
public:
  /// \brief Initializes to zero vector.
  /// \post All coefficients are 0.0f.
  Vector4 ();

  /// \brief Initializes each component to the same value.
  /// \param[in] xyzw A number that should be used for each coefficient.
  /// \post All coefficients are equal to xyzw.
  explicit
  Vector4 (float xyzw);

  /// \brief Initializes each component to different values.
  /// \param[in] x The coefficient for the basis vector i.
  /// \param[in] y The coefficient for the basis vector j.
  /// \param[in] z The coefficient for the basis vector k.
  /// \param[in] w The coefficient for the basis vector in the 4th dimension.
  /// \post The coefficients are equal to x, y, z, and w respectively.
  Vector4 (float x, float y, float z, float w);

  /// \brief Returns a const pointer to the first element.
  /// \return A const pointer to the first element (m_x).
  const float*
  data () const;

  /// Assigns each component to the same value.
  /// \param[in] xyzw A number that should be used for each coefficient.
  /// \post All coefficients are equal to xyzw.
  void
  set (float xyzw);


  /// \brief Assigns each component to different values.
  /// \param[in] x The coefficient for the basis vector i.
  /// \param[in] y The coefficient for the basis vector j.
  /// \param[in] z The coefficient for the basis vector k.
  /// \param[in] w The coefficient for the basis vector in the 4th dimension.
  /// \post The coefficients are equal to x, y, z, and w respectively.
  void
  set (float x, float y, float z, float w);

  /// \brief Computes a dot product.
  /// \param[in] v Another vector.
  /// \return The doct product of this vector with v.
  float
  dot (const Vector4& v) const;

  /// \brief Computes the length of this vector.
  /// \return The length of this vector.
  float
  length () const;

  /// \brief Normalizes this vector.
  /// \post The length of this vector is 1, while the direction is unchanged.
  void
  normalize ();

  /// \brief Negates this vector.
  /// \post This vector points in precisely the opposite direction.
  void
  negate ();

  /// \brief Adds another vector to this.
  /// \param[in] v Another vector.
  /// \post This vector's components have had the other vector's components added.
  /// \return This vector.
  Vector4&
  operator+= (const Vector4& v);

  /// \brief Subtracts another vector from this.
  /// \param[in] v Another vector.
  /// \post This vector's components have had the other vector's components subtracted.
  /// \return This vector.
  Vector4&
  operator-= (const Vector4& v);

  /// \brief Multiplies (elementwise) this by another vector.
  /// \param[in] v Another vector.
  /// \post This vector's components have had the other vector's components multiplied.
  /// \return This vector.
  Vector4&
  operator*= (const Vector4& v);

  /// \brief Multiplies this vector by a scalar.
  /// \param[in] scalar A number.
  /// \post This vector's components have been multiplied by the scalar.
  /// \return This vector.
  Vector4&
  operator*= (float scalar);

  /// \brief Divides this vector by a scalar.
  /// \param[in] scalar A number.
  /// \post This vector's components have been divied by the scalar.
  /// \return This vector.
  Vector4&
  operator/= (float scalar);

public:
  /// \brief The location along the first dimension.
  float m_x;
  /// \brief The location along the second dimension.
  float m_y;
  /// \brief The location along the third dimension.
  float m_z;
  /// \brief The location along the fourth dimension.
  float m_w;
};
  
/// \brief Adds two vectors.
/// \param[in] v1 The first vector.
/// \param[in] v2 The second vector.
/// \return A new vector that is v1 + v2.
Vector4
operator+ (const Vector4& v1, const Vector4& v2);

/// \brief Subtracts two vectors.
/// \param[in] v1 The first vector.
/// \param[in] v2 The second vector.
/// \return A new vector that is v1 - v2.
Vector4
operator- (const Vector4& v1, const Vector4& v2);

/// \brief Negates a vector.
/// \param[in] v A vector.
/// \return The negation of that vector.
Vector4
operator- (const Vector4& v);

/// \brief Multiplies (elementwise) two vectors.
/// \param[in] v1 The first vector.
/// \param[in] v2 The second vector.
/// \return A new vector that is v1 * v2.
Vector4
operator* (const Vector4& v1, const Vector4& v2);

/// \brief Multiplies a vector by a scalar.
/// \param[in] v A vector.
/// \param[in] scalar A number.
/// \return A new vector that is v * scalar.
Vector4
operator* (const Vector4& v, float scalar);

/// \brief Multiplies a scalar by a vector.
/// \param[in] scalar A number.
/// \param[in] v A vector.
/// \return A new vector that is scalar * v.
Vector4
operator* (float scalar, const Vector4& v);

/// \brief Divides a vector by a scalar.
/// \param[in] v A vector.
/// \param[in] scalar A number.
/// \return A new vector that is v * scalar.
Vector4
operator/ (const Vector4& v, float scalar);

/// \brief Inserts a vector into an output stream.
/// Each component of the vector should have 2 digits of precision and a field
///   width of 10.
/// \param[in] out An output stream.
/// \param[in] v A vector.
/// \return The output stream.
/// \post The vector has been inserted into the output stream.
std::ostream&
operator<< (std::ostream& out, const Vector4& v);

/// \brief Checks whether or not two vectors are equal.
/// Vectors are equal if each of their respective components are within
///   0.00001f of each other due to floating-point imprecision.
/// \param[in] v1 A vector.
/// \param[in] v2 Another vector.
/// \return Whether or not v1 and v2 are equal.
bool
operator== (const Vector4& v1, const Vector4& v2);

#endif//TRANSFORM_HPP
