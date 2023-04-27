// This file contains functions that should be added to your Scene class.
// Don't actually put this file into your project -- just copy from it.

  /// \brief Sets the active mesh to the mesh named "meshName".
  /// The active mesh is the one affected by transforms.
  /// \param[in] meshName The name of the mesh that should be active.
  /// \pre The scene contains a mesh with that name.
  /// \post The mesh with that name becomes the active mesh.
  void
  setActiveMesh (const std::string& meshName);

  /// \brief Gets the active mesh.
  /// \pre The scene has at least one mesh.
  /// \return The active mesh.
  Mesh*
  getActiveMesh ();

  /// \brief Switches active meshes in the forward direction.
  /// \pre The scene has at least one mesh.
  /// \post The next mesh becomes active.  If the last mesh was active, the
  ///   first mesh becomes active.
  void
  activateNextMesh ();

  /// \brief Switches active meshes in the backward direction.
  /// \pre The scene has at least one mesh.
  /// \post The previous mesh becomes active.  If the first mesh was active,
  ///   the last mesh becomes active.
  void
  activatePreviousMesh ();
