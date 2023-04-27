/// \file Transform.cpp
/// \brief Scene class and any associated global functions.
/// \author Aaron Heinbaugh
/// \version A06

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include "Matrix3.hpp"
#include "Vector3.hpp"
#include "Matrix4.hpp"
#include "Transform.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
#include <math.h>

/// \brief A 4x4 matrix of floats with the requirement that the bottom row
///   must be 0, 0, 0, 1.  This type of matrix can be used to represent any
///   affine transformation.
/// The matrix is interpreted thus:
///   [ rx ux bx px ]
///   [ ry uy by py ]
///   [ rz uz bz pz ]
///   [  0  0  0  1 ] 
/// 'r', 'u', 'b', and 'p' are the right, up, back,
///   and position vectors, respectively. 
/// The last row is not explicitly stored since it is always
///    [  0  0  0  1 ].

  /// \brief Initializes a new transform to the identity transform: one that
  ///   represents no scale, rotation, shear, reflection, translation, or
  ///   other change.
  /// \post The Matrix3 component is the identity matrix, while the Vector3
  ///   component is the zero vector.
  Transform::Transform ()
  : m_rotScale(Matrix3()), m_position(Vector3(0,0,0))
  {}

  /// \brief Initializes a new transform from its orientation and position.
  /// \param[in] orientation The orientation of the new transform.
  /// \param[in] position The position of the new transform.
  /// \post The components have been copied from the parameters.
  Transform::Transform (const Matrix3& orientation, const Vector3& position)
  : m_rotScale(orientation), m_position(position)
  {}
  
  /// \brief Orthonormalizes the Matrix3 component.
  /// \post The Matrix3 component contains three perpendicular unit vectors.
  void
  Transform::orthonormalize ()
  {
      m_rotScale.orthonormalize();
  }
  
  /// \brief Resets to the identity transform.
  /// \post The Matrix3 component is the identity matrix, while the Vector3
  ///   component is the zero vector.
  void
  Transform::reset ()
  {
      m_rotScale.setToIdentity();
      m_position.set(0,0,0);
  }
  
  /// \brief Converts this to a 4x4 GLM matrix, so that it can be passed to our
  ///   shader program.
  /// \return A glm::mat4 containing the numbers of this matrix.
  Matrix4
  Transform::getTransform () const 
  {
      
      /*
      return glm::mat4(glm::vec4(m_rotScale.getRight().convert(), 0), glm::vec4(m_rotScale.getUp().convert(), 0),
        glm::vec4(m_rotScale.getBack().convert(), 0), glm::vec4(m_position.m_x, m_position.m_y, m_position.m_z, 1));
      */
      return Matrix4(
        Vector4(m_rotScale.getRight().m_x, m_rotScale.getRight().m_y, m_rotScale.getRight().m_z, 0),
        Vector4(m_rotScale.getUp().m_x, m_rotScale.getUp().m_y, m_rotScale.getUp().m_z, 0),
        Vector4(m_rotScale.getBack().m_x, m_rotScale.getBack().m_y, m_rotScale.getBack().m_z, 0), 
        Vector4(m_position.m_x, m_position.m_y, m_position.m_z, 1));    
  
  }
  
  /// \brief Copies the elements of this transform into an array, in column-
  ///   major order.
  /// \param[out] array The array to fill up.
  /// \post The array contains rx, ry, rz, 0, ux, ... px, py, pz, 1.
  void
  Transform::getTransform (float array[16]) const
  {
      array[0] = m_rotScale.getRight().m_x;
      array[1] = m_rotScale.getRight().m_y;
      array[2] = m_rotScale.getRight().m_z;
      array[3] = 0.0f;
      array[4] = m_rotScale.getUp().m_x;
      array[5] = m_rotScale.getUp().m_y;
      array[6] = m_rotScale.getUp().m_z;
      array[7] = 0.0f;
      array[8] = m_rotScale.getBack().m_x;
      array[9] = m_rotScale.getBack().m_y;
      array[10] = m_rotScale.getBack().m_z;
      array[11] = 0.0f;
      array[12] = m_position.m_x;
      array[13] = m_position.m_y;
      array[14] = m_position.m_z;
      array[15] = 1.0f;
  }

  /// \brief Gets the position component.
  /// \return A copy of the position in this transformation.
  Vector3
  Transform::getPosition () const
  {
      return m_position;
  }
  
  /// \brief Sets the position component.
  /// \param[in] position The new position component.
  /// \post The position in this transformation has been set to position.
  void
  Transform::setPosition (const Vector3& position)
  {
      m_position = position;
  }

  /// \brief Sets the position component.
  /// \param[in] x The new x-coordinate of the position.
  /// \param[in] y The new y-coordinate of the position.
  /// \param[in] z The new z-coordinate of the position.
  /// \post The position in this transformation has been set to [x, y, z].
  void
  Transform::setPosition (float x, float y, float z)
  {
      m_position.m_x = x;
      m_position.m_y = y;
      m_position.m_z = z;
  }

  /// \brief Gets the right basis vector.
  /// \return A copy of the right basis vector.
  Vector3
  Transform::getRight () const
  {
      return m_rotScale.getRight();
  }
  
  /// \brief Gets the up basis vector.
  /// \return A copy of the up basis vector.
  Vector3
  Transform::getUp () const
  {
      return m_rotScale.getUp();
  }
  
  /// \brief Gets the back basis vector.
  /// \return A copy of the back basis vector.
  Vector3
  Transform::getBack () const
  {
      return m_rotScale.getBack();
  }

  /// \brief Gets the orientation/scale matrix.
  /// \return A copy of the orientation/scale matrix.
  Matrix3
  Transform::getOrientation () const
  {
      return m_rotScale;
  }

  /// \brief Sets the orientation/scale matrix.
  /// \param[in] orientation The new orientation/scale matrix.
  /// \post The orientation/scale matrix has been set to the parameter.
  void
  Transform::setOrientation (const Matrix3& orientation)
  {
      m_rotScale = orientation;
  }

  /// \brief Sets the orientation/scale matrix.
  /// \param[in] right The new right vector.
  /// \param[in] up The new up vector.
  /// \param[in] The new back vector.
  /// \post The orientation/scale matrix has been set to [right, up, back].
  void
  Transform::setOrientation (const Vector3& right, const Vector3& up,
		  const Vector3& back)
  {
      m_rotScale.setRight(right);
      m_rotScale.setUp(up);
      m_rotScale.setBack(back);
  }

  /// \brief Moves "distance" units along the right vector.
  /// \param[in] distance How far to move.
  /// \post The position has been moved that far in the local right direction.
  void
  Transform::moveRight (float distance)
  {
      m_position += (distance * m_rotScale.getRight());
  }

  /// \brief Moves "distance" units along the up vector.
  /// \param[in] distance How far to move.
  /// \post The position has been moved that far in the local up direction.
  void
  Transform::moveUp (float distance)
  {
      m_position += (distance * m_rotScale.getUp());
  }

  /// \brief Moves "distance" units along the back vector.
  /// \param[in] distance How far to move.
  /// \post The position has been moved that far in the local back direction.
  void
  Transform::moveBack (float distance)
  {
      m_position += (distance * m_rotScale.getBack());
  }

  /// \brief Moves "distance" units in "localDirection", which is relative
  ///   to the coordinate system defined by this transform.
  /// \param[in] distance How far to move.
  /// \param[in] localDirection The (local) direction to move in.
  /// \post The position has been moved that far in that direction.
  void
  Transform::moveLocal (float distance, const Vector3& localDirection)
  {
      m_position += (m_rotScale * distance * localDirection);
  }

  /// \brief Moves "distance" units in "worldDirection", which is relative
  ///   to the world coodinate system.
  /// \param[in] distance How far to move.
  /// \param[in] worldDirection The (world) direction to move in.
  /// \post The position has been moved that far in that direction.
  void
  Transform::moveWorld (float distance, const Vector3& worldDirection)
  {
      m_position += distance * worldDirection;
  } 

  /// \brief Rotates about the local X axis.
  /// \param[in] angleDegrees how much to rotate.
  /// \post The orientation/scale matrix includes this rotation before whatever
  ///   transformations it already encoded.
  void
  Transform::pitch (float angleDegrees)
  {
    Matrix3 rotation(0,0,0);
    rotation.setToRotationX (angleDegrees);
    m_rotScale *= rotation;
  }

  /// \brief Rotates about the local Y axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post The orientation/scale matrix includes this rotation before whatever
  ///   transformations it already encoded.
  void
  Transform::yaw (float angleDegrees)
  {
    Matrix3 rotation(0,0,0);
    rotation.setToRotationY(angleDegrees);
    m_rotScale *= rotation;
  }

  /// \brief Rotates about the local Z axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post The orientation/scale matrix includes this rotation before whatever
  ///   transformations it already encoded.
  void
  Transform::roll (float angleDegrees)
  {
    Matrix3 rotation(0,0,0);
    rotation.setToRotationZ (angleDegrees);
    m_rotScale *= rotation;
  }

  /// \brief Rotates locally about an arbitrary local unit vector "axis".
  /// \param[in] angleDegrees How much to rotate.
  /// \param[in] axis The (local) vector to rotate around.
  /// \post The orientation/scale matrix includes this rotation before whatever
  ///   transformations it already encoded.
  void
  Transform::rotateLocal (float angleDegrees, const Vector3& axis)
  {
    Matrix3 rotation(0,0,0);
    rotation.setFromAngleAxis (angleDegrees, axis);
    m_rotScale = m_rotScale * rotation;
  }

  /// \brief Sets "up" to world Y, and adjusts "back" and "right"
  ///   to ensure the matrix is orthogonal.
  /// If "back" is pointing in the Y or -Y direction,
  ///   make it [ 0 0 1 ].
  /// This will override any scaling, shearing, pitching,
  ///   or rolling that existed, while leaving yawing and
  ///   movement.
  /// \post The up vector in the orientation/scale matrix is [0, 1, 0].
  /// \post The right and back vectors in the orientation/scale matrix are
  ///   perpendicular to the up vector and each other.
  void
  Transform::alignWithWorldY ()
  {
      m_rotScale.setUp(Vector3(0,1,0));
      Vector3 normback = m_rotScale.getRight().cross(m_rotScale.getUp());
      normback.normalize();
      m_rotScale.setBack(normback);
      m_rotScale.setRight(m_rotScale.getUp().cross(m_rotScale.getBack()));
  }
  
  /// \brief Rotates around the world unit vector "axis".
  /// \param[in] angleDegrees How much to rotate.
  /// \param[in] axis The (world) vector to rotate around.
  /// \post The orientation/scale matrix includes this rotation after whatever
  ///   transformations it already encoded.
  void
  Transform::rotateWorld (float angleDegrees, const Vector3& axis)
  {
    Matrix3 rotation(0,0,0);
    rotation.setFromAngleAxis (angleDegrees, axis);
    m_rotScale = rotation * m_rotScale;
    m_position = rotation * m_position;
  }

  /// \brief Scales locally using a uniform scale.
  /// \param[in] scale The scaling factor.
  /// \post The orientation/scale matrix includes this scale before whatever
  ///   transformations it already encoded.
  void
  Transform::scaleLocal (float scale)
  {
    Matrix3 rotation(0,0,0);
    rotation.setToScale(scale);
    m_rotScale = m_rotScale * rotation;
  }

  /// \brief Scales locally using a non-uniform scale.
  /// \param[in] scaleX The scaling factor for the X direction.
  /// \param[in] scaleY The scaling factor for the Y direction.
  /// \param[in] scaleZ The scaling factor for the Z direction.
  /// \post The orientation/scale matrix includes this scale before whatever
  ///   transformations it already encoded.
  void
  Transform::scaleLocal (float scaleX, float scaleY, float scaleZ)
  {
    Matrix3 rotation(0,0,0);
    rotation.setToScale(scaleX, scaleY, scaleZ);
    m_rotScale = m_rotScale * rotation;      
  }
    
  /// \brief Scales with regard to world using a uniform scale.
  /// \param[in] scale The scaling factor.
  /// \post The orientation/scale matrix includes this scale after whatever
  ///   transformations it already encoded.
  void
  Transform::scaleWorld (float scale)
  {
    Matrix3 rotation(0,0,0);
    rotation.setToScale(scale);
    m_rotScale = rotation * m_rotScale;    
    m_position = rotation * m_position;
  }

  /// \brief Scales with regard to world using a non-uniform scale.
  /// \param[in] scaleX The scaling factor for the X direction.
  /// \param[in] scaleY The scaling factor for the Y direction.
  /// \param[in] scaleZ The scaling factor for the Z direction.
  /// \post The orientation/scale matrix includes this scale after whatever
  ///   transformations it already encoded.
  void
  Transform::scaleWorld (float scaleX, float scaleY, float scaleZ)
  {
    Matrix3 rotation(0,0,0);
    rotation.setToScale(scaleX, scaleY, scaleZ);
    m_rotScale = rotation * m_rotScale;
    m_position = rotation * m_position;
  }

  /// \brief Shears local X by Y and Z.
  /// \param[in] shearY The factor of Y to shear X by.
  /// \param[in] shearZ The factor of Z to shear X by.
  /// \post The orientation/scale matrix includes this shear before whatever
  ///   transformations it already encoded.
  void
  Transform::shearLocalXByYz (float shearY, float shearZ)
  {
    Matrix3 rotation(0,0,0);
    rotation.setToShearXByYz(shearY, shearZ);
    m_rotScale = m_rotScale * rotation;     
  }

  /// \brief Shears local Y by X and Z.
  /// \param[in] shearX The factor of X to shear Y by.
  /// \param[in] shearZ The factor of Z to shear Y by.
  /// \post The orientation/scale matrix includes this shear before whatever
  ///   transformations it already encoded.
  void
  Transform::shearLocalYByXz (float shearX, float shearZ)
  {
    Matrix3 rotation(0,0,0);
    rotation.setToShearYByXz(shearX, shearZ);
    m_rotScale = m_rotScale * rotation;      
  }

  /// \brief Shears local Z by X and Y.
  /// \param[in] shearX The factor of X to shear Z by.
  /// \param[in] shearY The factor of Y to shear Z by.
  /// \post The orientation/scale matrix includes this shear before whatever
  ///   transformations it already encoded.
  void
  Transform::shearLocalZByXy (float shearX, float shearY)
  {
    Matrix3 rotation(0,0,0);
    rotation.setToShearZByXy(shearX, shearY);
    m_rotScale = m_rotScale * rotation;       
  }

  /// \brief Inverts this transform assuming it consists of a pure rotation
  ///   and a translation.
  /// This can be used to compute the view transform.
  /// \pre This transform consists of a pure rotation and translation.
  /// \post This transform has been inverted.
  void
  Transform::invertRt ()
  {
      m_rotScale.invertRotation();
      m_position = m_rotScale * (-1 * m_position);
  }
  
  /// \brief Combines this with "t" in the order this * t.
  /// \param[in] t Another transform that should be combined with this.
  /// \post This transform consists of itself times t.
  void
  Transform::combine (const Transform& t)
  {
      float rx = m_rotScale.getRight().m_x * t.getRight().m_x + m_rotScale.getUp().m_x * t.getRight().m_y + m_rotScale.getBack().m_x * t.getRight().m_z; 
      float ry = m_rotScale.getRight().m_y * t.getRight().m_x + m_rotScale.getUp().m_y * t.getRight().m_y + m_rotScale.getBack().m_y * t.getRight().m_z;
      float rz = m_rotScale.getRight().m_z * t.getRight().m_x + m_rotScale.getUp().m_z * t.getRight().m_y + m_rotScale.getBack().m_z * t.getRight().m_z;
      float ux = m_rotScale.getRight().m_x * t.getUp().m_x + m_rotScale.getUp().m_x * t.getUp().m_y + m_rotScale.getBack().m_x * t.getUp().m_z;
      float uy = m_rotScale.getRight().m_y * t.getUp().m_x + m_rotScale.getUp().m_y * t.getUp().m_y + m_rotScale.getBack().m_y * t.getUp().m_z;
      float uz = m_rotScale.getRight().m_z * t.getUp().m_x + m_rotScale.getUp().m_z * t.getUp().m_y + m_rotScale.getBack().m_z * t.getUp().m_z;
      float bx = m_rotScale.getRight().m_x * t.getBack().m_x + m_rotScale.getUp().m_x * t.getBack().m_y + m_rotScale.getBack().m_x * t.getBack().m_z; 
      float by = m_rotScale.getRight().m_y * t.getBack().m_x + m_rotScale.getUp().m_y * t.getBack().m_y + m_rotScale.getBack().m_y * t.getBack().m_z; 
      float bz = m_rotScale.getRight().m_z * t.getBack().m_x + m_rotScale.getUp().m_z * t.getBack().m_y + m_rotScale.getBack().m_z * t.getBack().m_z;
      float tx = m_rotScale.getRight().m_x * t.getPosition().m_x + m_rotScale.getUp().m_x * t.getPosition().m_y + m_rotScale.getBack().m_x * t.getPosition().m_z + m_position.m_x; 
      float ty = m_rotScale.getRight().m_y * t.getPosition().m_x + m_rotScale.getUp().m_y * t.getPosition().m_y + m_rotScale.getBack().m_y * t.getPosition().m_z + m_position.m_y; 
      float tz = m_rotScale.getRight().m_z * t.getPosition().m_x + m_rotScale.getUp().m_z * t.getPosition().m_y + m_rotScale.getBack().m_z * t.getPosition().m_z + m_position.m_z;
      m_rotScale.setRight(Vector3(rx,ry,rz));
      m_rotScale.setUp(Vector3(ux,uy,uz));
      m_rotScale.setBack(Vector3(bx,by,bz));
      m_position.m_x = tx;
      m_position.m_y = ty;
      m_position.m_z = tz;
  }


/// \brief Combines two transforms into their product.
/// \param[in] t1 A transform.
/// \param[in] t2 Another transform.
/// \return A new transform that is t1 * t2.
Transform
operator* (const Transform& t1, const Transform& t2)
{
      float rx = t1.getRight().m_x * t2.getRight().m_x + t1.getUp().m_x * t2.getRight().m_y + t1.getBack().m_x * t2.getRight().m_z; 
      float ry = t1.getRight().m_y * t2.getRight().m_x + t1.getUp().m_y * t2.getRight().m_y + t1.getBack().m_y * t2.getRight().m_z;
      float rz = t1.getRight().m_z * t2.getRight().m_x + t1.getUp().m_z * t2.getRight().m_y + t1.getBack().m_z * t2.getRight().m_z;
      float ux = t1.getRight().m_x * t2.getUp().m_x + t1.getUp().m_x * t2.getUp().m_y + t1.getBack().m_x * t2.getUp().m_z;
      float uy = t1.getRight().m_y * t2.getUp().m_x + t1.getUp().m_y * t2.getUp().m_y + t1.getBack().m_y * t2.getUp().m_z;
      float uz = t1.getRight().m_z * t2.getUp().m_x + t1.getUp().m_z * t2.getUp().m_y + t1.getBack().m_z * t2.getUp().m_z;
      float bx = t1.getRight().m_x * t2.getBack().m_x + t1.getUp().m_x * t2.getBack().m_y + t1.getBack().m_x * t2.getBack().m_z; 
      float by = t1.getRight().m_y * t2.getBack().m_x + t1.getUp().m_y * t2.getBack().m_y + t1.getBack().m_y * t2.getBack().m_z; 
      float bz = t1.getRight().m_z * t2.getBack().m_x + t1.getUp().m_z * t2.getBack().m_y + t1.getBack().m_z * t2.getBack().m_z;
      float tx = t1.getRight().m_x * t2.getPosition().m_x + t1.getUp().m_x * t2.getPosition().m_y + t1.getBack().m_x * t2.getPosition().m_z + t1.getPosition().m_x; 
      float ty = t1.getRight().m_y * t2.getPosition().m_x + t1.getUp().m_y * t2.getPosition().m_y + t1.getBack().m_y * t2.getPosition().m_z + t1.getPosition().m_y; 
      float tz = t1.getRight().m_z * t2.getPosition().m_x + t1.getUp().m_z * t2.getPosition().m_y + t1.getBack().m_z * t2.getPosition().m_z + t1.getPosition().m_z;
      return Transform(Matrix3(rx,ry,rz,ux,uy,uz,bx,by,bz),Vector3(tx,ty,tz));
}

/// \brief Prints the complete 4x4 matrix the Transform represents.
/// Each element of the matrix should have 2 digits of precision and a field
///   width of 10.  Elements should be in this order:
///      rx ux bx px
///      ry uy by py
///      rz uz bz pz
///      0  0  0  1
/// \param[inout] out An output stream.
/// \param[in] t A transform.
/// \return The output stream.
/// \post The transform has been inserted into the output stream.
std::ostream&
operator<< (std::ostream& out, const Transform& t)
{
      out << std::setw(10) << std::setprecision (2) << std::fixed << (t.getRight().m_x)
          << std::setw(10) << std::setprecision (2) << std::fixed << (t.getUp().m_x)
          << std::setw(10) << std::setprecision (2) << std::fixed << (t.getBack().m_x) 
          << std::setw(10) << std::setprecision (2) << std::fixed << (t.getPosition().m_x) << "\n"
          << std::setw(10) << std::setprecision (2) << std::fixed << (t.getRight().m_y)
          << std::setw(10) << std::setprecision (2) << std::fixed << (t.getUp().m_y)
          << std::setw(10) << std::setprecision (2) << std::fixed << (t.getBack().m_y) 
          << std::setw(10) << std::setprecision (2) << std::fixed << (t.getPosition().m_y) << "\n"
          << std::setw(10) << std::setprecision (2) << std::fixed << (t.getRight().m_z)
          << std::setw(10) << std::setprecision (2) << std::fixed << (t.getUp().m_z)
          << std::setw(10) << std::setprecision (2) << std::fixed << (t.getBack().m_z) 
          << std::setw(10) << std::setprecision (2) << std::fixed << (t.getPosition().m_z) << "\n"
          << std::setw(10) << std::setprecision (2) << std::fixed << (0.00)
          << std::setw(10) << std::setprecision (2) << std::fixed << (0.00)
          << std::setw(10) << std::setprecision (2) << std::fixed << (0.00) 
          << std::setw(10) << std::setprecision (2) << std::fixed << (1.00) << "\n";      
      return out;    
}

/// \brief Tests whether or not two transforms are equal.
/// Transforms are equal if their matrices and vectors are equal.
/// \param[in] t1 A transform.
/// \param[in] t2 Another transform.
/// \return Whether or not t1 and t2 are equal.
bool
operator== (const Transform& t1, const Transform& t2)
{
  return (t1.getOrientation() == t2.getOrientation()) && (t1.getPosition() == t2.getPosition());
}
