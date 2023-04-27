// This file contains functions that should be added to your Mesh class.
// Don't actually put this file into your project -- just copy from it.

  /// \brief Gets the mesh's world matrix.
  /// \return The world matrix.
  Transform
  getWorld () const;

  /// \brief Moves the mesh right (locally).
  /// \param[in] distance The distance to move the mesh.
  /// \post The mesh has been moved.
  void
  moveRight (float distance);

  /// \brief Moves the mesh up (locally).
  /// \param[in] distance The distance to move the mesh.
  /// \post The mesh has been moved.
  void
  moveUp (float distance);

  /// \brief Moves the mesh back (locally).
  /// \param[in] distance The distance to move the mesh.
  /// \post The mesh has been moved.
  void
  moveBack (float distance);

  /// \brief Moves the mesh in some local direction.
  /// \param[in] distance How far to move the mesh.
  /// \param[localDirection] The (local) direction to move the mesh in.
  /// \post The mesh has been moved.
  void
  moveLocal (float distance, const Vector3& localDirection);

  /// \brief Moves the mesh in some world direction.
  /// \param[in] distance How far to move the mesh.
  /// \param[in] worldDirection The (world) direciton to move the mesh in.
  /// \post The mesh has been moved.
  void
  moveWorld (float distance, const Vector3& worldDirection);

  /// \brief Rotates the mesh around its own local right axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post The mesh has been rotated.
  void
  pitch (float angleDegrees);

  /// \brief Rotates the mesh around its own local up axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post The mesh has been rotated.
  void
  yaw (float angleDegrees);

  /// \brief Rotates the mesh around its own local back axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post The mesh has been rotated.
  void
  roll (float angleDegrees);

  /// \brief Rotates the mesh around some local direction.
  /// \param[in] angleDegrees How much to rotate.
  /// \param[in] axis The (local) direction to rotate around.
  /// \post The mesh has been rotated.
  void
  rotateLocal (float angleDegrees, const Vector3& axis);

  /// \brief Aligns the mesh with the world Y axis.
  /// \post The mesh's local up axis is (0, 1, 0).
  /// \post The mesh's local right and back axes perpendicular to each other
  ///   and to its local up axis.
  void
  alignWithWorldY ();

  /// \brief Scales the mesh (locally).
  /// \param[in] scale The amount to scale.
  /// \post The mesh has been scaled.
  void
  scaleLocal (float scale);

  /// \brief Scales the mesh (locally).
  /// \param[in] scaleX the amount to scale in the local right direction.
  /// \param[in] scaleY The amount to scale in the local up direction.
  /// \param[in] scaleZ The amount to scale in the local back direction.
  /// \post The mesh has been scaled.
  void
  scaleLocal (float scaleX, float scaleY, float scaleZ);
    
  /// \brief Scales the mesh (worldly).
  /// \param[in] scale The amount to scale.
  /// \post The mesh has been scaled.
  void
  scaleWorld (float scale);

  /// \brief Scales the mesh (worldly).
  /// \param[in] scaleX The amount to scale in the world right direction.
  /// \param[in] scaleY The amount to scale in the world up direction.
  /// \param[in] scaleZ The amount to scale in the world back direction.
  /// \post The mesh has been scaled.
  void
  scaleWorld (float scaleX, float scaleY, float scaleZ);

  /// \brief Shears the mesh's local X by its local Y and local Z.
  /// \param[in] shearY How much local Y to add to X.
  /// \param[in] shearZ How much local Z to add to X.
  /// \post The mesh has been sheared.
  void
  shearLocalXByYz (float shearY, float shearZ);

  /// \brief Shears the mesh's local Y by its local X and local Z.
  /// \param[in] shearX How much local X to add to Y.
  /// \param[in] shearZ How much local Z to add to Y.
  /// \post The mesh has been sheared.
  void
  shearLocalYByXz (float shearX, float shearZ);

  /// \brief Shears the mesh's local Z by its local X and local Y.
  /// \param[in] shearX How much local X to add to Z.
  /// \param[in] shearY How much local Y to add to Z.
  /// \post The mesh has been sheared.
  void
  shearLocalZByXy (float shearX, float shearY);
