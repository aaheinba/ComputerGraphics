/// \file Mesh.hpp
/// \brief Declaration of Mesh class and any associated global functions.
/// \author Chad Hogg, Aaron Heinbaugh
/// \version A02

#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include "Transform.hpp"
#include "OpenGLContext.hpp"
#include "ShaderProgram.hpp"
#include "Matrix4.hpp"
#include "Material.hpp"

/// \brief An object that exists in the world, which consists of one or more
///   3-D triangles.
class Mesh
{
public:

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


  /// \brief Constructs an empty Mesh with no triangles.
  /// \param context A pointer to an object through which the Mesh will be able
  ///   to make OpenGL calls.
  /// \post A unique VAO and VBO have been generated for this Mesh and stored
  ///   for later use.
  Mesh (OpenGLContext* context, ShaderProgram* shader);

  /// \brief Destructs this Mesh.
  /// \post The VAO and VBO associated with this Mesh have been deleted.
  virtual
  ~Mesh ();

  /// \brief Copy constructor removed because you shouldn't be copying Meshes.
  Mesh (const Mesh&) = delete;

  /// \brief Assignment operator removed because you shouldn't be assigning
  ///   Meshes.
  Mesh&
  operator= (const Mesh&) = delete;

  /// \brief Adds the geometry of [additional] triangles to this Mesh.
  /// \param[in] geometry A collection of vertex data for 1 or more triangles.
  ///   Each vertex must contain interleaved 3-D position and 3-D color data
  ///   (X, Y, Z, R, G, B) and the vector must contain complete triangles (3
  ///   vertices each).
  /// \pre This Mesh has not yet been prepared.
  /// \post The geometry has been appended to this Mesh's internal geometry
  ///   store for future use.
  void
  setMaterial (Material material);

  void
  addGeometry (const std::vector<float>& geometry);

  /// \brief Copies this Mesh's geometry into this Mesh's VBO and sets up its
  ///   VAO.
  /// \pre This Mesh has not yet been prepared.
  /// \post The first two vertex attributes have been enabled, with
  ///   interleaved 3-part positions and 3-part colors.
  /// \post This Mesh's geometry has been copied to its VBO.
  void
  prepareVao ();

  /// \brief Draws this Mesh in OpenGL.
  /// \param[in] shaderProgram A pointer to the ShaderProgram that should
  ///   be used.
  /// \param[in] viewMatrix The view matrix that should be used by itself as
  ///   the model-view matrix (there is not yet any model part).
  /// \pre This Mesh has been prepared.
  /// \post While the ShaderProgram was enabled, the viewMatrix has been set as
  ///   the "uModelView" uniform matrix and the geometry has been drawn.
  void
  draw (const Transform& viewMatrix, const Matrix4& projectionMatrix);
  
  
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

protected:
// This one is for part 2, and should be protected:


  /// \brief Enables VAO attributes.
  /// \pre This Mesh's VAO has been bound.
  /// \post Any attributes (positions, colors, normals, texture coordinates)
  ///   have been enabled and configured.
  /// This should only be called from the middle of prepareVao().
  virtual void
  enableAttributes();

  OpenGLContext* m_context;

private:

  /// A pointer to the object through which this Mesh will make OpenGL calls.
  // TODO: Add the other data members you think you will need here.
  GLuint m_vao;
  GLuint m_vbo;
  GLuint m_ibo;
  std::vector<float>* shape;
  Transform m_world;
  std::vector<unsigned int>* m_indices;
  ShaderProgram* m_shaderProgram;
  Material m_material;

};

#endif//MESH_HPP
