// This file contains even more functions that should be added to your Mesh class.
// Don't actually put this file into your project -- just copy from it.


// This one is for part 1, and should be public:


  /// \brief Adds additional triangles to this Mesh.
  /// \param[in] indices A collection of indices into the vertex buffer for 1
  ///   or more triangles.  There must be 3 indices per triangle.
  /// \pre This Mesh has not yet been prepared.
  /// \post The indices have been appended to this Mesh's internal index store
  ///   for future use.
  void
  addIndices (const std::vector<unsigned int>& indices);


// This one is for part 2, and should be public:


  /// \brief Gets the number of floats used to represent each vertex.
  /// \return The number of floats used for each vertex.
  virtual unsigned int
  getFloatsPerVertex () const;


// This one is for part 2, and should be protected:


  /// \brief Enables VAO attributes.
  /// \pre This Mesh's VAO has been bound.
  /// \post Any attributes (positions, colors, normals, texture coordinates)
  ///   have been enabled and configured.
  /// This should only be called from the middle of prepareVao().
  virtual void
  enableAttributes();

