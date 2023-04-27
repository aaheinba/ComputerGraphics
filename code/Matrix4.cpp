/// \file Matrix4.cpp
/// \brief Matrix4 class and any associated global functions.
/// \author Aaron Heinbaugh
/// \version A07

#include "Matrix4.hpp"
#include <math.h>
#include <iomanip>

/// \brief Initializes to the identity matrix.
  /// \post rx, uy, bz, and tw are 1.0f while all other elements are 0.0f.
  Matrix4::Matrix4 ()
  : m_right(1,0,0,0), m_up(0,1,0,0), m_back(0,0,1,0), m_translation(0,0,0,1)
  {}

  /// \brief Initializes a ne matrix from the four basis vectors.
  /// \param[in] right The first column of the new matrix.
  /// \param[in] up The second column of the new matrix.
  /// \param[in] back The third column of the new matrix.
  /// \param[in] translation The fourth column of the new matrix.
  Matrix4::Matrix4 (const Vector4& right, const Vector4& up,
	   const Vector4& back, const Vector4& translation)
  : m_right(right), m_up(up), m_back(back), m_translation(translation)
  {}

  /// \brief Gets the right vector.
  /// \return A copy of the first column.
  Vector4
  Matrix4::getRight () const
  {
      return m_right;
  }

  /// \brief Gets the up vector.
  /// \return A copy of the second column.
  Vector4
  Matrix4::getUp () const
  {
      return m_up;
  }

  /// \brief Gets the back vector.
  /// \return A copy of the third column.
  Vector4
  Matrix4::getBack () const
  {
      return m_back;
  }

  /// \brief Gets the translation vector.
  /// \return A copy of the fourth column.
  Vector4
  Matrix4::getTranslation () const
  {
      return m_translation;
  }

  /// \brief Sets this to the identity matrix.
  /// \post The elements along the main diagonal are 1.0f while all others are
  ///   0.0f.
  void
  Matrix4::setToIdentity ()
  {
      m_right.m_x = 1;
      m_right.m_y = 0;
      m_right.m_w = 0;
      m_right.m_z = 0;
      m_up.m_w = 0;
      m_up.m_x = 0;
      m_up.m_y = 1;
      m_up.m_z = 0;
      m_back.m_w = 0;
      m_back.m_x = 0;
      m_back.m_y = 0; 
      m_back.m_z = 1;
      m_translation.m_x = 0;
      m_translation.m_y = 0;
      m_translation.m_z = 0;
      m_translation.m_w = 1;
  }

  /// \brief Sets this to the zero matrix.
  /// \post All elements are 0.0f.
  void
  Matrix4::setToZero ()
  {
      m_right.m_x = 0;
      m_right.m_y = 0;
      m_right.m_w = 0;
      m_right.m_z = 0;
      m_up.m_w = 0;
      m_up.m_x = 0;
      m_up.m_y = 0;
      m_up.m_z = 0;
      m_back.m_w = 0;
      m_back.m_x = 0;
      m_back.m_y = 0; 
      m_back.m_z = 0;
      m_translation.m_x = 0;
      m_translation.m_y = 0;
      m_translation.m_z = 0;
      m_translation.m_w = 0;
  }
    
  /// \brief Gets a const pointer to the first element.
  /// \return A pointer to rx.
  const float*
  Matrix4::data () const
  {
      return &m_right.m_x;
  }

  // For the projection methods, do all computations using
  //   double-s and only cast to float when NECESSARY. 

  /// \brief Sets this to a symmetric perspective projection matrix.
  /// \param[in] fovYDegrees The vertical field of view angle, in degrees.
  /// \param[in] aspectRatio The ratio of width to height.
  /// \param[in] nearPlaneZ The distance to the near clip plane.
  /// \param[in] farPlaneZ The distance to the far clip plane.
  /// \post This has been set to a symmetric perspective projection.
  void
  Matrix4::setToPerspectiveProjection (double fovYDegrees, double aspectRatio,
			      double nearPlaneZ, double farPlaneZ)
  {
      /*
      m_right = Vector4(1 / (aspectRatio * tan(fovYDegrees / 2)), 0, 0, 0);
      m_up = Vector4(0, 1 / tan(fovYDegrees / 2), 0, 0);
      m_right = Vector4(0, 0, (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ), -1);
      m_translation = Vector4(0, 0, (2 * farPlaneZ * nearPlaneZ) / (nearPlaneZ - farPlaneZ), 0);
      */
      m_right.m_x = 1 / (aspectRatio * tan((fovYDegrees * M_PI / 180) / 2));
      m_right.m_y = 0;
      m_right.m_z = 0;
      m_right.m_w = 0;
      m_up.m_x = 0;
      m_up.m_y = 1 / tan((fovYDegrees * M_PI / 180) / 2);
      m_up.m_z = 0;
      m_up.m_w = 0;
      m_back.m_x = 0;
      m_back.m_y = 0;
      m_back.m_z = (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ);
      m_back.m_w = -1;
      m_translation.m_x = 0;
      m_translation.m_y = 0;
      m_translation.m_z = (2 * farPlaneZ * nearPlaneZ) / (nearPlaneZ - farPlaneZ);
      m_translation.m_w = 0;
  
  }

  /// \brief Sets this to an assymetric perspective projection matrix.
  /// \param[in] left The x-value of the left side of the projection plane.
  /// \param[in] right The x-value of the right side of the projection plane.
  /// \param[in] bottom The y-value of the bottom of the projection plane.
  /// \param[in] top The y-value of the top of the projection plane.
  /// \param[in] nearPlaneZ The distance to the near clip plane.
  /// \param[in] farPlaneZ The distance to the far clip plane.
  /// \post This has been set to an asymmetric perspective projection.
  void
  Matrix4::setToPerspectiveProjection (double left, double right,
			      double bottom, double top,
			      double nearPlaneZ, double farPlaneZ)
  {
      /*
      m_right = Vector4((2 * nearPlaneZ) / (right - left), 0, 0, 0);
      m_up = Vector4(0, (2 * nearPlaneZ) / (top - bottom), 0, 0);
      m_right = Vector4((right + left) / (right - left), (top + bottom) / (top - bottom), (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ), -1);
      m_translation = Vector4(0, 0, (2 * farPlaneZ * nearPlaneZ) / ( nearPlaneZ - farPlaneZ), 0);
      */
      m_right.m_x = (2 * nearPlaneZ) / (right - left);
      m_right.m_y = 0;
      m_right.m_z = 0;
      m_right.m_w = 0;
      m_up.m_x = 0;
      m_up.m_y = (2 * nearPlaneZ) / (top - bottom);
      m_up.m_z = 0;
      m_up.m_w = 0;
      m_back.m_x = (right + left) / (right - left);
      m_back.m_y = (top + bottom) / (top - bottom);
      m_back.m_z = (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ);
      m_back.m_w = -1;
      m_translation.m_x = 0;
      m_translation.m_y = 0;
      m_translation.m_z = (2 * farPlaneZ * nearPlaneZ) / (nearPlaneZ - farPlaneZ);
      m_translation.m_w = 0;
  }

  /// \brief Sets this to an orthographic projection matrix.
  /// \param[in] left The x-value of the left plane.
  /// \param[in] right The x-value of the right plane.
  /// \param[in] bottom The y-value of the bottom plane.
  /// \param[in] top The y-value of the top plane.
  /// \param[in] nearPlaneZ The distance to the near clip plane.
  /// \param[in] farPlaneZ The distance to the far clip plane.
  /// \post This has been set to an orthographic projection.
  void
  Matrix4::setToOrthographicProjection (double left, double right,
			       double bottom, double top,
			       double nearPlaneZ, double farPlaneZ)
  {
      /*
      m_right = Vector4(2 / (right - left), 0, 0, 0);
      m_up = Vector4(0, 2 / (top - bottom), 0, 0);
      m_back = Vector4(0 ,0 , 2 / (nearPlaneZ - farPlaneZ), 0);
      m_translation = Vector4(-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ), 1);
      */
      m_right.m_x = 2 / (right - left);
      m_right.m_y = 0;
      m_right.m_z = 0;
      m_right.m_w = 0;
      m_up.m_x = 0;
      m_up.m_y = 2 / (top - bottom);
      m_up.m_z = 0;
      m_up.m_w = 0;
      m_back.m_x = 0;
      m_back.m_y = 0;
      m_back.m_z = 2 / (nearPlaneZ - farPlaneZ);
      m_back.m_w = 0;
      m_translation.m_x = -(right + left) / (right - left);
      m_translation.m_y = -(top + bottom) / (top - bottom);
      m_translation.m_z = (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ);
      m_translation.m_w = 1;  
  
  }

/// \brief Inserts a matrix into an output stream.
/// Each element of the matrix should have 2 digits of precision and a field
///   width of 10.  Elements should be in this order:
///     rx ux bx tx
///     ry uy by ty
///     rz uz bz tz
///     rw uw bw tw
/// \param[inout] out An output stream.
/// \param[in] m A matrix.
/// \return The output stream.
/// \post The matrix has been inserted into the output stream.
std::ostream&
operator<< (std::ostream& out, const Matrix4& m)
{
      out << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data())
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 4)
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 8)
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 12) << "\n"
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 1)
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 5)
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 9)
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 13) << "\n"
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 2)
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 6)
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 10)
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 14) << "\n"
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 3)
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 7)
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 11)
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 15) << "\n";      
      return out;
}

/// \brief Checks whether or not two matrices are equal.
/// Matrices are equal if each of their respective elements are within
///   0.00001f of each other due to floating-point imprecision.
/// \param[in] m1 A matrix.
/// \param[in] m2 Another matrix.
/// \return Whether or not m1 and m2 are equal.
bool
operator== (const Matrix4& m1, const Matrix4& m2)
{
  const float precision = 0.00001f; 
  return ((fabs(*(m1.data()) - *(m2.data())) < precision) &&
          (fabs(*(m1.data() + 1) - *(m2.data() + 1)) < precision) &&
          (fabs(*(m1.data() + 2) - *(m2.data() + 2)) < precision) &&
          (fabs(*(m1.data() + 3) - *(m2.data() + 3)) < precision) &&
          (fabs(*(m1.data() + 4) - *(m2.data() + 4)) < precision) &&
          (fabs(*(m1.data() + 5) - *(m2.data() + 5)) < precision) &&
          (fabs(*(m1.data() + 6) - *(m2.data() + 6)) < precision) &&
          (fabs(*(m1.data() + 7) - *(m2.data() + 7)) < precision) &&
          (fabs(*(m1.data() + 8) - *(m2.data() + 8)) < precision) &&
          (fabs(*(m1.data() + 9) - *(m2.data() + 9)) < precision) &&
          (fabs(*(m1.data() + 10) - *(m2.data() + 10)) < precision) &&
          (fabs(*(m1.data() + 11) - *(m2.data() + 11)) < precision) &&
          (fabs(*(m1.data() + 12) - *(m2.data() + 12)) < precision) &&
          (fabs(*(m1.data() + 13) - *(m2.data() + 13)) < precision) &&
          (fabs(*(m1.data() + 14) - *(m2.data() + 14)) < precision) &&
          (fabs(*(m1.data() + 15) - *(m2.data() + 15)) < precision) 
         );
}