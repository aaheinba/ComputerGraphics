/// \file Mesh.cpp
/// \brief Mesh class and any associated global functions.
/// \author Aaron Heinbaugh
/// \version A02

#include "Mesh.hpp"
#include <vector>

#include "OpenGLContext.hpp"
#include "ShaderProgram.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "RealOpenGLContext.hpp"
#include "Transform.hpp"
#include "Matrix4.hpp"
#include "Geometry.hpp"


Mesh::Mesh (OpenGLContext* context, ShaderProgram* shader){
  m_context = context;
  m_context->genVertexArrays (1, &m_vao);
  m_context->genBuffers (1, &m_vbo);
  m_context->genBuffers (1, &m_ibo);
  m_indices = new std::vector<unsigned int>;
  shape = new std::vector<float>;
  m_shaderProgram = shader;
};

Mesh::~Mesh (){
  m_context->deleteVertexArrays (1, &m_vao);
  m_context->deleteBuffers (1, &m_vbo );
  m_context->deleteBuffers (1, &m_ibo );
};

void
Mesh::setMaterial(Material material)
{
  m_material = material;
};

void
Mesh::addGeometry (const std::vector<float>& geometry){
  shape->insert(shape->end(), geometry.begin(), geometry.end());
};

void
Mesh::prepareVao(){

    // Set up triangle geometry
  m_context->bindVertexArray (m_vao);
  m_context->bindBuffer (GL_ARRAY_BUFFER, m_vbo);
  m_context->bufferData (GL_ARRAY_BUFFER, shape->size () * sizeof(float),
			 shape->data (), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices->size() * sizeof(unsigned int),
       m_indices->data(), GL_STATIC_DRAW);
  enableAttributes();
  m_context->bindVertexArray (0);

};

void 
Mesh::draw(const Transform& viewMatrix, const Matrix4& projectionMatrix){

  m_shaderProgram->enable ();
  m_shaderProgram->setUniformMatrix ("uModelView", (viewMatrix * m_world).getTransform());
  m_shaderProgram->setUniformMatrix ("uProjection", projectionMatrix);
  m_shaderProgram->setUniformMatrix ("uView", viewMatrix.getTransform());
  m_shaderProgram->setUniformMatrix ("uWorld", m_world.getTransform());
  /*
  m_shaderProgram->setUniformVec3 ("uAmbientReflection", Vector3(1,1,1));
  m_shaderProgram->setUniformVec3 ("uEmissiveIntensity", Vector3(0.0,0.0,0.0));
  m_shaderProgram->setUniformVec3 ("uDiffuseReflection", Vector3(0.7,0.7,0.7));
  m_shaderProgram->setUniformVec3 ("uSpecularReflection", Vector3(0.7,0.7,0.7));
  m_shaderProgram->setUniformFloat ("uSpecularPower", 0.5);
  */
  m_material.setShader(*m_shaderProgram);

  //m_shaderProgram->setUniformVec3 ("uEyePosition", Vector3(3.5,0,3.5));
    m_shaderProgram->setUniformVec3 ("uEyePosition", Vector3(3.5, 8, -5));

  m_context->bindVertexArray (m_vao);
  m_context->drawArrays (GL_TRIANGLES, 0, shape->size()/6);
  glDrawElements (GL_TRIANGLES, m_indices->size(), GL_UNSIGNED_INT,
      reinterpret_cast<void*> (0));
  //enableAttributes();
  m_context->bindVertexArray (0);
  m_shaderProgram->disable ();

};

  /// \brief Adds additional triangles to this Mesh.
  /// \param[in] indices A collection of indices into the vertex buffer for 1
  ///   or more triangles.  There must be 3 indices per triangle.
  /// \pre This Mesh has not yet been prepared.
  /// \post The indices have been appended to this Mesh's internal index store
  ///   for future use.
  void
  Mesh::addIndices (const std::vector<unsigned int>& indices)
  {
    m_indices->insert(m_indices->end(), indices.begin(), indices.end());
  }

  /// \brief Gets the mesh's world matrix.
  /// \return The world matrix.
  Transform
  Mesh::getWorld () const{
    return m_world;
  }

  /// \brief Moves the mesh right (locally).
  /// \param[in] distance The distance to move the mesh.
  /// \post The mesh has been moved.
  void
  Mesh::moveRight (float distance){
    m_world.moveRight(distance);
  }

  /// \brief Moves the mesh up (locally).
  /// \param[in] distance The distance to move the mesh.
  /// \post The mesh has been moved.
  void
  Mesh::moveUp (float distance){
    m_world.moveUp(distance);
  }

  /// \brief Moves the mesh back (locally).
  /// \param[in] distance The distance to move the mesh.
  /// \post The mesh has been moved.
  void
  Mesh::moveBack (float distance){
    m_world.moveBack(distance);
  }

  /// \brief Moves the mesh in some local direction.
  /// \param[in] distance How far to move the mesh.
  /// \param[localDirection] The (local) direction to move the mesh in.
  /// \post The mesh has been moved.
  void
  Mesh::moveLocal (float distance, const Vector3& localDirection){
    m_world.moveLocal(distance, localDirection);
  }

  /// \brief Moves the mesh in some world direction.
  /// \param[in] distance How far to move the mesh.
  /// \param[in] worldDirection The (world) direciton to move the mesh in.
  /// \post The mesh has been moved.
  void
  Mesh::moveWorld (float distance, const Vector3& worldDirection){
    m_world.moveWorld(distance, worldDirection);
  }

  /// \brief Rotates the mesh around its own local right axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post The mesh has been rotated.
  void
  Mesh::pitch (float angleDegrees){
    m_world.pitch(angleDegrees);
  }

  /// \brief Rotates the mesh around its own local up axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post The mesh has been rotated.
  void
  Mesh::yaw (float angleDegrees){
    m_world.yaw(angleDegrees);
  }

  /// \brief Rotates the mesh around its own local back axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post The mesh has been rotated.
  void
  Mesh::roll (float angleDegrees){
    m_world.roll(angleDegrees);
  }

  /// \brief Rotates the mesh around some local direction.
  /// \param[in] angleDegrees How much to rotate.
  /// \param[in] axis The (local) direction to rotate around.
  /// \post The mesh has been rotated.
  void
  Mesh::rotateLocal (float angleDegrees, const Vector3& axis){
    m_world.rotateLocal(angleDegrees, axis);
  }

  /// \brief Aligns the mesh with the world Y axis.
  /// \post The mesh's local up axis is (0, 1, 0).
  /// \post The mesh's local right and back axes perpendicular to each other
  ///   and to its local up axis.
  void
  Mesh::alignWithWorldY (){
    m_world.alignWithWorldY();
  }

  /// \brief Scales the mesh (locally).
  /// \param[in] scale The amount to scale.
  /// \post The mesh has been scaled.
  void
  Mesh::scaleLocal (float scale){
    m_world.scaleLocal(scale);
  }

  /// \brief Scales the mesh (locally).
  /// \param[in] scaleX the amount to scale in the local right direction.
  /// \param[in] scaleY The amount to scale in the local up direction.
  /// \param[in] scaleZ The amount to scale in the local back direction.
  /// \post The mesh has been scaled.
  void
  Mesh::scaleLocal (float scaleX, float scaleY, float scaleZ){
    m_world.scaleLocal(scaleX, scaleY, scaleZ);
  }
    
  /// \brief Scales the mesh (worldly).
  /// \param[in] scale The amount to scale.
  /// \post The mesh has been scaled.
  void
  Mesh::scaleWorld (float scale){
    m_world.scaleWorld(scale);
  }

  /// \brief Scales the mesh (worldly).
  /// \param[in] scaleX The amount to scale in the world right direction.
  /// \param[in] scaleY The amount to scale in the world up direction.
  /// \param[in] scaleZ The amount to scale in the world back direction.
  /// \post The mesh has been scaled.
  void
  Mesh::scaleWorld (float scaleX, float scaleY, float scaleZ){
    m_world.scaleWorld(scaleX, scaleY, scaleZ);
  }

  /// \brief Shears the mesh's local X by its local Y and local Z.
  /// \param[in] shearY How much local Y to add to X.
  /// \param[in] shearZ How much local Z to add to X.
  /// \post The mesh has been sheared.
  void
  Mesh::shearLocalXByYz (float shearY, float shearZ){
    m_world.shearLocalXByYz(shearY, shearZ);
  }

  /// \brief Shears the mesh's local Y by its local X and local Z.
  /// \param[in] shearX How much local X to add to Y.
  /// \param[in] shearZ How much local Z to add to Y.
  /// \post The mesh has been sheared.
  void
  Mesh::shearLocalYByXz (float shearX, float shearZ){
    m_world.shearLocalYByXz(shearX, shearZ);
  }

  /// \brief Shears the mesh's local Z by its local X and local Y.
  /// \param[in] shearX How much local X to add to Z.
  /// \param[in] shearY How much local Y to add to Z.
  /// \post The mesh has been sheared.
  void
  Mesh::shearLocalZByXy (float shearX, float shearY){
    m_world.shearLocalZByXy(shearX, shearY);
  }

  /// \brief Gets the number of floats used to represent each vertex.
  /// \return The number of floats used for each vertex.
  unsigned int
  Mesh::getFloatsPerVertex () const
  {
    return 3;
  }

  void
  Mesh::enableAttributes()
  {
    const GLint POSITION_ATTRIB_INDEX = 0;
    m_context->enableVertexAttribArray (POSITION_ATTRIB_INDEX);
    // Positions have 3 parts, each are floats, and start at beginning of array
    m_context->vertexAttribPointer (POSITION_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
				  reinterpret_cast<void*> (0));
  }
