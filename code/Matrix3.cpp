/// \file Matrix3.cpp
/// \brief Matrix3 class and any associated global functions.
/// \author Aaron Heinbaugh 
/// \version A05

// For overload of shift operator
#include <iostream>
#include <math.h>
#include <iomanip>
#include <limits>
#include "Vector3.hpp"
#include "Matrix3.hpp"

  /// \brief Initializes a new matrix to the identity matrix.
  /// \post rx, uy, and bz are 1.0f while all other elements are 0.0f.
  Matrix3::Matrix3 ()
  : Matrix3 (1.0f, 0, 0, 0, 1.0f, 0, 0, 0, 1.0f){}

  /// \brief Initializes a new matrix from its 9 elements.
  /// \param[in] rx The first column, first row.
  /// \param[in] ry The first column, second row.
  /// \param[in] rz The first column, third row.
  /// \param[in] ux The second column, first row.
  /// \param[in] uy The second column, second row.
  /// \param[in] uz The second column, third row.
  /// \param[in] bx The third column, first row.
  /// \param[in] by The third column, second row.
  /// \param[in] bz The third column, third row.
  /// \post Each element has the value of its matching parameter.
  Matrix3::Matrix3 (float rx, float ry, float rz,
           float ux, float uy, float uz,
           float bx, float by, float bz)
  : Matrix3(Vector3(rx, ry, rz), Vector3(ux, uy, uz), Vector3(bx, by, bz)) {}
  
  /// \brief Initializes a new matrix from three basis vectors.
  /// \param[in] right The first column of the matrix.
  /// \param[in] up The second column of the matrix.
  /// \param[in] back The third column of the matrix.
  /// \post Each column vector has the value of its matching parameter.
  Matrix3::Matrix3 (const Vector3& right, const Vector3& up,
           const Vector3& back)
  : m_right(right), m_up(up), m_back(back) {}
  
  /// \brief Initializes a new matrix from two basis vectors, computing the third.
  /// \param[in] up The second column of the matrix.
  /// \param[in] back The third column of the matrix.
  /// \param[in] makeOrthonormal Whether or not to orthonormalize the vectors.
  /// \post The up and back vectors have the value of their matching parameters.
  /// \post The right vector is the cross product of the up and back vectors.
  /// \post If makeOrthonormal is true, the vectors have been orthonormalized.
  Matrix3::Matrix3 (const Vector3& up, const Vector3& back, bool makeOrthonormal)
    : m_right(up.cross(back)), m_up(up), m_back(back) {
    if (makeOrthonormal == true){
      this->orthonormalize();
    }
  }

  ///\brief Destructs a matrix.
  Matrix3::~Matrix3 (){}

  /// \brief Sets this to the identity matrix.
  /// \post rx, uy, and bz are 1.0f while all other elements are 0.0f.
  void
  Matrix3::setToIdentity (){
    m_right = Vector3 (1.0f, 0, 0);
    m_up = Vector3 (0, 1.0f, 0);
    m_back = Vector3 (0, 0, 1.0f);
  }

  /// \brief Sets this to the zero matrix.
  /// \post All elements are 0.0f.
  void
  Matrix3::setToZero (){
    m_right = Vector3 (0, 0, 0);
    m_up = Vector3 (0, 0, 0);
    m_back = Vector3 (0, 0, 0);
  }

  /// \brief Retrieves a pointer to the first column, first row.
  /// \return A pointer to the beginning of the data.
  /// Because of the way our data is stored, you can use pointer arithmetic to
  ///   get to the first column second row, first column third row, second
  ///   column first row, and so forth.
  float*
  Matrix3::data (){
    return &m_right.m_x;
  }

  /// \brief Retrieves a constant pointer to the first column, first row.
  /// \return A constant pointer to the beginning of the data.
  /// Because of the way our data is stored, you can use pointer arithmetic to
  ///   get to the first column second row, first column third row, second
  ///   column first row, and so forth.  
  const float*
  Matrix3::data () const {
    return &m_right.m_x;
  }

  /// \brief Sets the right vector.
  /// \param[in] right The new value for the first column.
  /// \post The first column is a copy of the parameter.
  void
  Matrix3::setRight (const Vector3& right){
    m_right = right;
  }

  /// \brief Gets the right vector.
  /// \return A copy of the first column.
  Vector3
  Matrix3::getRight () const {
    return m_right;
  }

  /// \brief Sets the up vector.
  /// \param[in] up The new value for the second column.
  /// \post The second column is a copy of the parameter.
  void
  Matrix3::setUp (const Vector3& up){
    m_up = up;
  }

  /// \brief Gets the up vector.
  /// \return A copy of the second column.
  Vector3
  Matrix3::getUp () const {
    return m_up;
  }

  /// \brief Sets the back vector.
  /// \param[in] back The new value for the third column.
  /// \post The third column is a copy of the parameter.
  void
  Matrix3::setBack (const Vector3& back){
    m_back = back;
  }

  /// \brief Gets the back vector.
  /// \return A copy of the third column.
  Vector3
  Matrix3::getBack () const{
    return m_back;
  }

  /// \brief Sets the forward (opposite of back) vector.
  /// \param[in] forward The new forward vector.
  /// \post The third column is the negation of the parameter.
  void
  Matrix3::setForward (const Vector3& forward){
    m_back = -forward;
  }

  /// \brief Gets the forward (opposite of back) vector.
  /// \return A copy of the negation of the third column.
  Vector3
  Matrix3::getForward () const {
    return -m_back;
  }

  /// \brief Inverts this matrix, using an fast algorithm that will only work for rotations.
  /// \pre This matrix represents a pure rotation.
  /// \post This matrix has been replaced with its inversion.
  void
  Matrix3::invertRotation (){
    this->transpose();
  }

  /// \brief Inverts this matrix, using an expensive algorithm.
  /// \post This matrix has been replaced with its inversion.
  void
  Matrix3::invert (){
    float d = this->determinant();
    if (d == 0)
      return;
    float rightx = (m_up.m_y * m_back.m_z - m_back.m_y * m_up.m_z) / d;
    float righty = (m_right.m_z * m_back.m_y - m_right.m_y * m_back.m_z) / d;
    float rightz = (m_right.m_y * m_up.m_z - m_right.m_z * m_up.m_y) / d;
    float upx = (m_up.m_z * m_back.m_x - m_up.m_x * m_back.m_z) / d;
    float upy = (m_right.m_x * m_back.m_z - m_right.m_z * m_back.m_x) / d;
    float upz = (m_up.m_x * m_right.m_z - m_right.m_x * m_up.m_z) / d;
    float backx = (m_up.m_x * m_back.m_y - m_back.m_x * m_up.m_y) / d;
    float backy = (m_back.m_x * m_right.m_y - m_right.m_x * m_back.m_y) / d;
    float backz = (m_right.m_x * m_up.m_y - m_up.m_x * m_right.m_y) / d;
    m_right.m_x = rightx;
    m_right.m_y = righty;
    m_right.m_z = rightz;
    m_up.m_x = upx;
    m_up.m_y = upy;
    m_up.m_z = upz;
    m_back.m_x = backx;
    m_back.m_y = backy;
    m_back.m_z = backz;
  }

  /// \brief Calculates the determinant of this matrix.
  /// \return The determinant.
  float
  Matrix3::determinant () const {
    return m_right.m_x * (m_up.m_y * m_back.m_z - m_up.m_z * m_back.m_y) +
           m_right.m_y * (m_up.m_z * m_back.m_x - m_up.m_x * m_back.m_z) +
           m_right.m_z * (m_up.m_x * m_back.m_y - m_up.m_y * m_back.m_x);    
  }

  /// \brief Transposes this matrix.
  /// \post The first column has become the first row, etc.
  void
  Matrix3::transpose (){
    float upx = m_right.m_y;
    float upz = m_back.m_y;
    float righty = m_up.m_x;
    float rightz = m_back.m_x;
    float backx = m_right.m_z;
    float backy = m_up.m_z;
    m_right.m_y = righty;
    m_right.m_z = rightz;
    m_up.m_x = upx;
    m_up.m_z = upz;
    m_back.m_x = backx;
    m_back.m_y = backy;
  }

  /// \brief Makes the basis vectors orthonormal to each other.
  /// Starts by assuming that the back vector is pointing in the correct
  ///   direction.  Normalizes the back vector.  Computes the right vector by
  ///   crossing up with back, and then normalizes it.  Computes the up vector
  ///   by crossing back with right, and then normalizes it.
  /// \post All columns have a length of 1 and are mutually perpendicular.
  /// \post The back vector points in the same direction that it did before.
  void
  Matrix3::orthonormalize (){
    m_back.normalize();
    m_right = m_up.cross(m_back);
    m_right.normalize();
    m_up = m_back.cross(m_right);
    m_up.normalize();
  }

  /// \brief Makes this into a uniform scale matrix.
  /// \param[in] scale The amount to scale up (or down).
  /// \post This is a matrix that scales vectors by the specified factor.
  void
  Matrix3::setToScale (float scale){
    this->setToZero();
    m_right.m_x = scale;
    m_up.m_y = scale;
    m_back.m_z = scale;
  }

  /// \brief Makes this into a non-uniform scale matrix.
  /// \param[in] scaleX The scale factor for the X direction.
  /// \param[in] scaleY The scale factor for the Y direction.
  /// \param[in] scaleZ The scale factor for the Z direction.
  /// \post This is a matrix that scales vectors by the specified factors.
  void
  Matrix3::setToScale (float scaleX, float scaleY, float scaleZ){
    this->setToZero();
    m_right.m_x = scaleX;
    m_up.m_y = scaleY;
    m_back.m_z = scaleZ;
  }

  /// \brief Makes this into a matrix that shears X values.
  /// \param[in] shearY The amount to shear by Y.
  /// \param[in] shearZ The amount to shear by Z.
  /// \post This is a matrix that shears X by the specified factors of Y and Z.
  void
  Matrix3::setToShearXByYz (float shearY, float shearZ){
    this->setToIdentity();
    m_up.m_x = shearY;
    m_back.m_x = shearZ;
  }

  /// \brief Makes this into a matrix that shears Y values.
  /// \param[in] shearX The amount to shear by X.
  /// \param[in] shearZ The amount to shear by Z.
  /// \post This is a matrix that shears Y by the specified factors of X and Z.
  void
  Matrix3::setToShearYByXz (float shearX, float shearZ){
    this->setToIdentity();
    m_right.m_y = shearX;
    m_back.m_y = shearZ;
  }

  /// \brief Makes this into a matrix that shears Z values.
  /// \param[in] shearX The amount to shear by X.
  /// \param[in] shearY The amount to shear by Y.
  /// \post This is a matrix that shears Z by the specified factors of X and Y.
  void
  Matrix3::setToShearZByXy (float shearX, float shearY){
    this->setToIdentity();
    m_right.m_z = shearX;
    m_up.m_z = shearY;
  }

  /// \brief Makes this into a matrix that rotates around the X-axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post This is a matrix that rotates around the X-axis by the specified angle.
  void
  Matrix3::setToRotationX (float angleDegrees){
    this->setToIdentity();
    m_up.m_y = cos(M_PI * angleDegrees / 180);
    m_up.m_z = sin(M_PI * angleDegrees / 180);
    m_back.m_y = -sin(M_PI * angleDegrees / 180);
    m_back.m_z = cos(M_PI * angleDegrees / 180);

  }

  /// \brief Makes this into a matrix that rotates around the Y-axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post This is a matrix that rotates around the Y-axis by the specified angle.
  void
  Matrix3::setToRotationY (float angleDegrees){
    this->setToIdentity();
    m_right.m_x = cos(M_PI * angleDegrees / 180);
    m_right.m_z = -sin(M_PI * angleDegrees / 180);
    m_back.m_x = sin(M_PI * angleDegrees / 180);
    m_back.m_z = cos(M_PI * angleDegrees / 180);
  }

  /// \brief Makes this into a matrix that rotates around the Z-axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post This is a matrix that roates around the Z-axis by the specified angle.
  void
  Matrix3::setToRotationZ (float angleDegrees){
    this->setToIdentity();
    m_right.m_x = cos(M_PI * angleDegrees / 180);
    m_right.m_y = sin(M_PI * angleDegrees / 180);
    m_up.m_x = -sin(M_PI * angleDegrees / 180);
    m_up.m_y = cos(M_PI * angleDegrees / 180);
  }

  /// \brief Makes this into a matrix that rotates around an arbitrary vector.
  /// \param[in] angleDegrees How much to rotate.
  /// \param[in] axis The vector to rotate around.
  /// \post This is a matrix that rotates around the specified vector by the specified angle.
  void
  Matrix3::setFromAngleAxis (float angleDegrees, const Vector3& axis){
    
    Vector3 axis1 = axis;
    axis1.normalize();
    float temprx = axis1.m_x * axis1.m_x * (1 - cos(M_PI * angleDegrees / 180)) + cos(M_PI * angleDegrees / 180);
    float tempry = axis1.m_x * axis1.m_y * (1 - cos(M_PI * angleDegrees / 180)) + axis1.m_z * sin(M_PI * angleDegrees / 180);
    float temprz = axis1.m_x * axis1.m_z * (1 - cos(M_PI * angleDegrees / 180)) - axis1.m_y * sin(M_PI * angleDegrees / 180);
    float tempux = axis1.m_x * axis1.m_y * (1 - cos(M_PI * angleDegrees / 180)) - axis1.m_z * sin(M_PI * angleDegrees / 180);
    float tempuy = axis1.m_y * axis1.m_y * (1 - cos(M_PI * angleDegrees / 180)) + cos((M_PI * angleDegrees / 180));
    float tempuz = axis1.m_y * axis1.m_z * (1 - cos(M_PI * angleDegrees / 180)) + axis1.m_x * sin(M_PI * angleDegrees / 180);
    float tempbx = axis1.m_x * axis1.m_z * (1 - cos(M_PI * angleDegrees / 180)) + axis1.m_y * sin(M_PI * angleDegrees / 180);
    float tempby = axis1.m_y * axis1.m_z * (1 - cos(M_PI * angleDegrees / 180)) - axis1.m_x * sin(M_PI * angleDegrees / 180);
    float tempbz = axis1.m_z * axis1.m_z * (1 - cos(M_PI * angleDegrees / 180)) + cos((M_PI * angleDegrees / 180));
    m_right.m_x = temprx;
    m_right.m_y = tempry;
    m_right.m_z = temprz;
    m_up.m_x = tempux;
    m_up.m_y = tempuy;
    m_up.m_z = tempuz;
    m_back.m_x = tempbx;
    m_back.m_y = tempby;
    m_back.m_z = tempbz;
    

  }

  /// \brief Negates this matrix.
  /// \post Every element has been replaced by its negation.
  void
  Matrix3::negate (){
    m_right.m_x = -m_right.m_x;
    m_right.m_y = -m_right.m_y;
    m_right.m_z = -m_right.m_z;
    m_up.m_x = -m_up.m_x;
    m_up.m_y = -m_up.m_y;
    m_up.m_z = -m_up.m_z;
    m_back.m_x = -m_back.m_x;
    m_back.m_y = -m_back.m_y;
    m_back.m_z = -m_back.m_z;
  }

  /// \brief Transforms a vector, computing *this * v.
  /// \param[in] v The vector to multiply by this matrix.
  /// \return The result of the multiplication.
  Vector3
  Matrix3::transform (const Vector3& v) const {
    return Vector3(
      m_right.m_x * v.m_x + m_up.m_x * v.m_y + m_back.m_x * v.m_z,
      m_right.m_y * v.m_x + m_up.m_y * v.m_y + m_back.m_y * v.m_z,
      m_right.m_z * v.m_x + m_up.m_z * v.m_y + m_back.m_z * v.m_z
    );
  }

  /// \brief Adds another matrix to this.
  /// \param[in] m The other matrix.
  /// \return This matrix.
  /// \post Every element of this matrix has its sum with the equivalent element in the other.
  Matrix3&
  Matrix3::operator+= (const Matrix3& m){
    m_back.m_x += m.m_back.m_x;
    m_back.m_y += m.m_back.m_y;
    m_back.m_z += m.m_back.m_z;
    m_right.m_x += m.m_right.m_x;
    m_right.m_y += m.m_right.m_y;
    m_right.m_z += m.m_right.m_z;
    m_up.m_x += m.m_up.m_x;
    m_up.m_y += m.m_up.m_y;
    m_up.m_z += m.m_up.m_z;    
    return *this;
  }

  /// \brief Subtracts another matrix from this.
  /// \param[in] m The other matrix.
  /// \return This matrix.
  /// \post Every element of this matrix has the difference of it and the equivalent element in the other.
  Matrix3&
  Matrix3::operator-= (const Matrix3& m){
    m_back.m_x -= m.m_back.m_x;
    m_back.m_y -= m.m_back.m_y;
    m_back.m_z -= m.m_back.m_z;
    m_right.m_x -= m.m_right.m_x;
    m_right.m_y -= m.m_right.m_y;
    m_right.m_z -= m.m_right.m_z;
    m_up.m_x -= m.m_up.m_x;
    m_up.m_y -= m.m_up.m_y;
    m_up.m_z -= m.m_up.m_z;    
    return *this;
  }

  /// \brief Multiplies this matrix by a scalar.
  /// \param[in] scalar The number to multiply by.
  /// \return This matrix.
  /// \post Every element of this matrix has the product of it and the scalar.
  Matrix3&
  Matrix3::operator*= (float scalar){
    m_back.m_x *= scalar;
    m_back.m_y *= scalar;
    m_back.m_z *= scalar;
    m_right.m_x *= scalar;
    m_right.m_y *= scalar;
    m_right.m_z *= scalar;
    m_up.m_x *= scalar;
    m_up.m_y *= scalar;
    m_up.m_z *= scalar; 
    return *this;
  }

  /// \brief Multiplies this matrix by another matrix.
  /// \param[in] m The matrix to multiply by.
  /// \return This matrix.
  /// \post This matrix contains the product of itself with m.
  Matrix3&
  Matrix3::operator*= (const Matrix3& m){
    float rx = m_right.m_x * m.m_right.m_x + m_up.m_x * m.m_right.m_y + m_back.m_x * m.m_right.m_z;
    float ry = m_right.m_y * m.m_right.m_x + m_up.m_y * m.m_right.m_y + m_back.m_y * m.m_right.m_z;
    float rz = m_right.m_z * m.m_right.m_x + m_up.m_z * m.m_right.m_y + m_back.m_z * m.m_right.m_z;
    float ux = m_right.m_x * m.m_up.m_x + m_up.m_x * m.m_up.m_y + m_back.m_x * m.m_up.m_z;
    float uy = m_right.m_y * m.m_up.m_x + m_up.m_y * m.m_up.m_y + m_back.m_y * m.m_up.m_z;
    float uz = m_right.m_z * m.m_up.m_x + m_up.m_z * m.m_up.m_y + m_back.m_z * m.m_up.m_z;
    float bx = m_right.m_x * m.m_back.m_x + m_up.m_x * m.m_back.m_y + m_back.m_x * m.m_back.m_z;
    float by = m_right.m_y * m.m_back.m_x + m_up.m_y * m.m_back.m_y + m_back.m_y * m.m_back.m_z;
    float bz = m_right.m_z * m.m_back.m_x + m_up.m_z * m.m_back.m_y + m_back.m_z * m.m_back.m_z;
    m_right.m_x = rx;
    m_right.m_y = ry;
    m_right.m_z = rz;
    m_up.m_x = ux;
    m_up.m_y = uy;
    m_up.m_z = uz;
    m_back.m_x = bx;
    m_back.m_y = by;
    m_back.m_z = bz;
    return *this;
  }

/// \brief Adds two matrices.
/// \param[in] m1 The first matrix to add.
/// \param[in] m2 The secondn matrix to add.
/// \return A new matrix that is m1 + m2.
Matrix3
operator+ (const Matrix3& m1, const Matrix3& m2){
  Matrix3 temp = m1;
  return temp += m2;
}

/// \brief Subtracts two matrices.
/// \param[in] m1 The matrix to subtract from.
/// \param[in] m2 The matrix to subtract.
/// \return A new matrix that is m1 - m2.
Matrix3
operator- (const Matrix3& m1, const Matrix3& m2){
  Matrix3 temp = m1;
  return temp -= m2;
}

/// \brief Negates a matrix.
/// \param[in] m The matrix to negate.
/// \return A new matrix that is -m.
Matrix3
operator- (const Matrix3& m){
  Matrix3 temp = Matrix3(Vector3(0,0,0), Vector3(0,0,0), Vector3(0,0,0));
  return temp -= m;
}

/// \brief Multiplies a matrix by a scalar.
/// \param[in] m The matrix to multiply.
/// \param[in] scalar The number to multiply it by.
/// \return A new matrix that is m * scalar.
Matrix3
operator* (const Matrix3& m, float scalar){
  Matrix3 temp = m;
  return temp *= scalar;
}

/// \brief Multiplies a matrix by a scalar.
/// \param[in] scalar The number to multiply it by.
/// \param[in] m The matrix to multiply.
/// \return A new matrix that is m * scalar.
Matrix3
operator* (float scalar, const Matrix3& m){
  Matrix3 temp = m;
  return temp *= scalar;
}

/// \brief Multiplies a matrix by another matrix.
/// \param[in] m1 A matrix.
/// \param[in] m2 Another matrix.
/// \return A new matrix rhat is m * m.
Matrix3
operator* (const Matrix3& m1, const Matrix3& m2){
  Matrix3 temp = m1;
  return temp *= m2;
}

/// \brief Multiplies a matrix by a vector.
/// \param[in] m A matrix.
/// \param[in] v A vector.
/// \return A new vector that is m * v.
Vector3
operator* (const Matrix3& m, const Vector3& v){
  Matrix3 temp = m;
  Matrix3 temp2 (v, Vector3(0,0,0), Vector3(0,0,0));
  temp *= temp2;
  return temp.getRight();
}

/// \brief Inserts a matrix into an output stream.
/// Each element of the matrix should have 2 digits of precision and a field
///   width of 10.  Elements should be in this order:
///      rx ux bx
///      ry uy by
///      rz uz bz
/// \param[inout] out An output stream.
/// \param[in] m A matrix.
/// \return The output stream.
/// \post The matrix has been inserted into the output stream.
std::ostream&
operator<< (std::ostream& out, const Matrix3& m){
      out << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data())
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 3)
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 6) << "\n"
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 1)
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 4)
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 7) << "\n"
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 2)
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 5)
          << std::setw(10) << std::setprecision (2) << std::fixed << *(m.data() + 8) << "\n";
      return out;
}

/// \brief Checks whether or not two matrices are equal.
/// matrices are equal if each of their respective elements are within
///   0.00001f of each other due to floating-point imprecision.
/// \param[in] m1 A matrix.
/// \param[in] m2 Another matrix.
/// \return Whether or not m1 and m2 are equal.
bool
operator== (const Matrix3& m1, const Matrix3& m2){
  const float precision = 0.00001f; 
  return ((fabs(*(m1.data()) - *(m2.data())) < precision) &&
          (fabs(*(m1.data() + 1) - *(m2.data() + 1)) < precision) &&
          (fabs(*(m1.data() + 2) - *(m2.data() + 2)) < precision) &&
          (fabs(*(m1.data() + 3) - *(m2.data() + 3)) < precision) &&
          (fabs(*(m1.data() + 4) - *(m2.data() + 4)) < precision) &&
          (fabs(*(m1.data() + 5) - *(m2.data() + 5)) < precision) &&
          (fabs(*(m1.data() + 6) - *(m2.data() + 6)) < precision) &&
          (fabs(*(m1.data() + 7) - *(m2.data() + 7)) < precision) &&
          (fabs(*(m1.data() + 8) - *(m2.data() + 8)) < precision)
         );
}