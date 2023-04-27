/// \file Transform.hpp
/// \brief Declaration of Transform class and any associated global functions.
/// \author Gary M. Zoppetti, Ph.D. & Chad Hogg
/// \version A06

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <iostream>

// We won't need this after we write our own Matrix4 class.
#include <glm/mat4x4.hpp>
#include "Matrix4.hpp"
#include "Matrix3.hpp"
#include "Vector3.hpp"

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
class Transform
{
public:
  /// \brief Initializes a new transform to the identity transform: one that
  ///   represents no scale, rotation, shear, reflection, translation, or
  ///   other change.
  /// \post The Matrix3 component is the identity matrix, while the Vector3
  ///   component is the zero vector.
  Transform ();

  /// \brief Initializes a new transform from its orientation and position.
  /// \param[in] orientation The orientation of the new transform.
  /// \param[in] position The position of the new transform.
  /// \post The components have been copied from the parameters.
  Transform (const Matrix3& orientation, const Vector3& position);
  
  /// \brief Orthonormalizes the Matrix3 component.
  /// \post The Matrix3 component contains three perpendicular unit vectors.
  void
  orthonormalize ();
  
  /// \brief Resets to the identity transform.
  /// \post The Matrix3 component is the identity matrix, while the Vector3
  ///   component is the zero vector.
  void
  reset ();
  
  /// \brief Converts this to a 4x4 GLM matrix, so that it can be passed to our
  ///   shader program.
  /// \return A glm::mat4 containing the numbers of this matrix.
  Matrix4
  getTransform () const;
  
  /// \brief Copies the elements of this transform into an array, in column-
  ///   major order.
  /// \param[out] array The array to fill up.
  /// \post The array contains rx, ry, rz, 0, ux, ... px, py, pz, 1.
  void
  getTransform (float array[16]) const;

  /// \brief Gets the position component.
  /// \return A copy of the position in this transformation.
  Vector3
  getPosition () const;
  
  /// \brief Sets the position component.
  /// \param[in] position The new position component.
  /// \post The position in this transformation has been set to position.
  void
  setPosition (const Vector3& position);

  /// \brief Sets the position component.
  /// \param[in] x The new x-coordinate of the position.
  /// \param[in] y The new y-coordinate of the position.
  /// \param[in] z The new z-coordinate of the position.
  /// \post The position in this transformation has been set to [x, y, z].
  void
  setPosition (float x, float y, float z);

  /// \brief Gets the right basis vector.
  /// \return A copy of the right basis vector.
  Vector3
  getRight () const;
  
  /// \brief Gets the up basis vector.
  /// \return A copy of the up basis vector.
  Vector3
  getUp () const;
  
  /// \brief Gets the back basis vector.
  /// \return A copy of the back basis vector.
  Vector3
  getBack () const;

  /// \brief Gets the orientation/scale matrix.
  /// \return A copy of the orientation/scale matrix.
  Matrix3
  getOrientation () const;

  /// \brief Sets the orientation/scale matrix.
  /// \param[in] orientation The new orientation/scale matrix.
  /// \post The orientation/scale matrix has been set to the parameter.
  void
  setOrientation (const Matrix3& orientation);

  /// \brief Sets the orientation/scale matrix.
  /// \param[in] right The new right vector.
  /// \param[in] up The new up vector.
  /// \param[in] The new back vector.
  /// \post The orientation/scale matrix has been set to [right, up, back].
  void
  setOrientation (const Vector3& right, const Vector3& up,
		  const Vector3& back);

  /// \brief Moves "distance" units along the right vector.
  /// \param[in] distance How far to move.
  /// \post The position has been moved that far in the local right direction.
  void
  moveRight (float distance);

  /// \brief Moves "distance" units along the up vector.
  /// \param[in] distance How far to move.
  /// \post The position has been moved that far in the local up direction.
  void
  moveUp (float distance);

  /// \brief Moves "distance" units along the back vector.
  /// \param[in] distance How far to move.
  /// \post The position has been moved that far in the local back direction.
  void
  moveBack (float distance);

  /// \brief Moves "distance" units in "localDirection", which is relative
  ///   to the coordinate system defined by this transform.
  /// \param[in] distance How far to move.
  /// \param[in] localDirection The (local) direction to move in.
  /// \post The position has been moved that far in that direction.
  void
  moveLocal (float distance, const Vector3& localDirection);

  /// \brief Moves "distance" units in "worldDirection", which is relative
  ///   to the world coodinate system.
  /// \param[in] distance How far to move.
  /// \param[in] worldDirection The (world) direction to move in.
  /// \post The position has been moved that far in that direction.
  void
  moveWorld (float distance, const Vector3& worldDirection);

  /// \brief Rotates about the local X axis.
  /// \param[in] angleDegrees how much to rotate.
  /// \post The orientation/scale matrix includes this rotation before whatever
  ///   transformations it already encoded.
  void
  pitch (float angleDegrees);

  /// \brief Rotates about the local Y axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post The orientation/scale matrix includes this rotation before whatever
  ///   transformations it already encoded.
  void
  yaw (float angleDegrees);

  /// \brief Rotates about the local Z axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post The orientation/scale matrix includes this rotation before whatever
  ///   transformations it already encoded.
  void
  roll (float angleDegrees);

  /// \brief Rotates locally about an arbitrary local unit vector "axis".
  /// \param[in] angleDegrees How much to rotate.
  /// \param[in] axis The (local) vector to rotate around.
  /// \post The orientation/scale matrix includes this rotation before whatever
  ///   transformations it already encoded.
  void
  rotateLocal (float angleDegrees, const Vector3& axis);

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
  alignWithWorldY ();

  /// \brief Rotates around the world unit vector "axis".
  /// \param[in] angleDegrees How much to rotate.
  /// \param[in] axis The (world) vector to rotate around.
  /// \post The orientation/scale matrix includes this rotation after whatever
  ///   transformations it already encoded.
  void
  rotateWorld (float angleDegrees, const Vector3& axis);

  /// \brief Scales locally using a uniform scale.
  /// \param[in] scale The scaling factor.
  /// \post The orientation/scale matrix includes this scale before whatever
  ///   transformations it already encoded.
  void
  scaleLocal (float scale);

  /// \brief Scales locally using a non-uniform scale.
  /// \param[in] scaleX The scaling factor for the X direction.
  /// \param[in] scaleY The scaling factor for the Y direction.
  /// \param[in] scaleZ The scaling factor for the Z direction.
  /// \post The orientation/scale matrix includes this scale before whatever
  ///   transformations it already encoded.
  void
  scaleLocal (float scaleX, float scaleY, float scaleZ);
    
  /// \brief Scales with regard to world using a uniform scale.
  /// \param[in] scale The scaling factor.
  /// \post The orientation/scale matrix includes this scale after whatever
  ///   transformations it already encoded.
  void
  scaleWorld (float scale);

  /// \brief Scales with regard to world using a non-uniform scale.
  /// \param[in] scaleX The scaling factor for the X direction.
  /// \param[in] scaleY The scaling factor for the Y direction.
  /// \param[in] scaleZ The scaling factor for the Z direction.
  /// \post The orientation/scale matrix includes this scale after whatever
  ///   transformations it already encoded.
  void
  scaleWorld (float scaleX, float scaleY, float scaleZ);

  /// \brief Shears local X by Y and Z.
  /// \param[in] shearY The factor of Y to shear X by.
  /// \param[in] shearZ The factor of Z to shear X by.
  /// \post The orientation/scale matrix includes this shear before whatever
  ///   transformations it already encoded.
  void
  shearLocalXByYz (float shearY, float shearZ);

  /// \brief Shears local Y by X and Z.
  /// \param[in] shearX The factor of X to shear Y by.
  /// \param[in] shearZ The factor of Z to shear Y by.
  /// \post The orientation/scale matrix includes this shear before whatever
  ///   transformations it already encoded.
  void
  shearLocalYByXz (float shearX, float shearZ);

  /// \brief Shears local Z by X and Y.
  /// \param[in] shearX The factor of X to shear Z by.
  /// \param[in] shearY The factor of Y to shear Z by.
  /// \post The orientation/scale matrix includes this shear before whatever
  ///   transformations it already encoded.
  void
  shearLocalZByXy (float shearX, float shearY);

  /// \brief Inverts this transform assuming it consists of a pure rotation
  ///   and a translation.
  /// This can be used to compute the view transform.
  /// \pre This transform consists of a pure rotation and translation.
  /// \post This transform has been inverted.
  void
  invertRt ();
  
  /// \brief Combines this with "t" in the order this * t.
  /// \param[in] t Another transform that should be combined with this.
  /// \post This transform consists of itself times t.
  void
  combine (const Transform& t);

private:
  /// \brief A 3x3 matrix that stores the right, up, and back vectors.
  Matrix3 m_rotScale;
  /// \brief A 3D vector that stores the position/translation vector.
  Vector3 m_position;
};

/// \brief Combines two transforms into their product.
/// \param[in] t1 A transform.
/// \param[in] t2 Another transform.
/// \return A new transform that is t1 * t2.
Transform
operator* (const Transform& t1, const Transform& t2);

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
operator<< (std::ostream& out, const Transform& t);

/// \brief Tests whether or not two transforms are equal.
/// Transforms are equal if their matrices and vectors are equal.
/// \param[in] t1 A transform.
/// \param[in] t2 Another transform.
/// \return Whether or not t1 and t2 are equal.
bool
operator== (const Transform& t1, const Transform& t2);

#endif//TRANSFORM_HPP
