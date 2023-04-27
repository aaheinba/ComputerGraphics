/// \file Camera.cpp
/// \brief Declaration of Camera class and any associated global functions.
/// \author Chad Hogg and Aaron Heinbaugh
/// \version A03


#include "Vector3.hpp"
#include "OpenGLContext.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.hpp"
#include "RealOpenGLContext.hpp"
#include <glm/gtx/rotate_vector.hpp>
#include "Matrix4.hpp" 


  /// \brief Constructs a new Camera.
  ///
  /// \param eyePosition The location (in world coordinates) where the camera
  ///   is located.
  /// \param localBackDirection A vector pointing backwards from the camera.
  /// \param nearClipPlaneDistance The distance to the closest things the
  ///   camera can "see".
  /// \param farClipPlaneDistance The distance to the farthest things the
  ///   camera can "see".
  /// \param aspectRatio The window's width divided by height.
  /// \param verticalFieldOfViewDegrees The angle determining how much the
  ///   camera "sees".
  /// \post The camera's pose has been set and a projection matrix generated.
  /// \post The three orientation vectors are orthonormal with each other.
  /// \post All of the parameters have been copied into their respective data
  ///   members, and the local right and up have been calculated to be
  ///   orthonormal to the local back.
  Camera::Camera (const Vector3& eyePosition, const Vector3& localBackDirection,
	  float nearClipPlaneDistance, float farClipPlaneDistance,
	  float aspectRatio, float verticalFieldOfViewDegrees)
    : 
      m_world(Matrix3(Vector3(0, 1.0f, 0), localBackDirection, true), Vector3(eyePosition)),
      m_starting_world(Matrix3(Vector3(0, 1.0f, 0), localBackDirection, true), Vector3(eyePosition)),
      m_update(false),
      m_viewMatrix(m_world)
    {
      m_viewMatrix.invertRt();
      m_projectionMatrix.setToPerspectiveProjection(verticalFieldOfViewDegrees, aspectRatio, nearClipPlaneDistance, farClipPlaneDistance);
    };
    
  /// \brief Destructs a Camera.
  Camera::~Camera (){

  };
  
  /// \brief Sets the position (eye point) of the camera.
  /// \param[in] position The new position of the camera.
  /// \post The camera's location has been changed.
  void
  Camera::setPosition (const Vector3& position){
    m_world.setPosition(position);
    m_update = true;
  };

  /// \brief Moves the position (eye point) of the camera right or left.
  /// \param[in] distance How far to move along the right vector.
  /// \post The camera's location has been changed.
  void
  Camera::moveRight (float distance){
    //m_world.setPosition(m_world.getPosition() + distance * m_world.getRight());
    //m_update = true;

    m_world.moveRight(distance);
    m_update = true;

  };

  /// \brief Moves the position (eye point) of the camera up or down.
  /// \param[in] distance How far to move along the up vector.
  /// \post The camera's location has been changed.
  void
  Camera::moveUp (float distance){
    //m_eyePosition = m_eyePosition + distance * m_camMatrix.getUp();
    //m_update = true;

    m_world.moveUp(distance);
    m_update = true;

  };

  /// \brief Moves the position (eye point) of the camera back or forward.
  /// \param[in] distance How far to move along the back vector.
  /// \post The camera's location has been changed.
  void
  Camera::moveBack (float distance){
    //m_eyePosition = m_eyePosition + distance * m_camMatrix.getBack();
    //m_update = true;

    m_world.moveBack(distance);
    m_update = true;

  };

  /// \brief Rotates the camera counterclockwise around the up vector.
  /// \param[in] degrees How far to rotate.
  /// \post The camera's orientation has been changed.
  void
  Camera::yaw (float degrees){
    
    //Matrix3 rotation(0,0,0);
    //rotation.setFromAngleAxis (degrees, m_camMatrix.getUp());
    //m_camMatrix = rotation * m_camMatrix;
    //m_update = true;

    m_world.yaw(degrees);
    m_update = true;

  };

  void 
  Camera::roll (float degrees){
    
    //Matrix3 rotation(0,0,0);
    //rotation.setFromAngleAxis (degrees, m_camMatrix.getBack());
    //m_camMatrix = rotation * m_camMatrix;
    //m_update = true;

    m_world.roll(degrees);
    m_update = true;

  };

  void
  Camera::pitch (float degrees){

    //Matrix3 rotation(0,0,0);
    //rotation.setFromAngleAxis (degrees, m_camMatrix.getRight());
    //m_camMatrix = rotation * m_camMatrix;
    //m_update = true;

    m_world.pitch(degrees);
    m_update = true;

  };

  /// \brief Gets the view matrix, recalculating it only if necessary.
  /// \return A view matrix based on the camera's location and axis vectors.
  Transform
  Camera::getViewMatrix (){
    if (m_update == false){
      return m_viewMatrix; 
    }
    m_update = false;
    m_viewMatrix.setOrientation(m_world.getOrientation());
    m_viewMatrix.setPosition(m_world.getPosition());
    m_viewMatrix.invertRt();
    return m_viewMatrix;  
  };

  /// \brief Recreates the projection matrix.
  /// \param[in] verticalFovDegrees The viewing angle.
  /// \param[in] aspectRatio The width / height.
  /// \param[in] nearZ The distance to closest visible objects.
  /// \param[in] farZ The distance to furthest visible objects.
  void
  Camera::setProjectionSymmetricPerspective (double verticalFovDegrees, double aspectRatio,
		  double nearZ, double farZ)
  {

    m_projectionMatrix.setToPerspectiveProjection(verticalFovDegrees, aspectRatio, nearZ, farZ);

  }; 

  void
  Camera::setProjectionAsymmetricPerspective(double left, double right, double bottom, double top,
			double nearPlaneZ, double farPlaneZ)
  {
    m_projectionMatrix.setToPerspectiveProjection(left, right, bottom, top, nearPlaneZ, farPlaneZ);
  }

  void
  Camera::setProjectionOrthographic(double left, double right, double bottom, double top,
			double nearPlaneZ, double farPlaneZ)
  {
    m_projectionMatrix.setToOrthographicProjection(left, right, bottom, top, nearPlaneZ, farPlaneZ);
  }

  /// \brief Gets the projection matrix.
  /// \return The projection matrix.
  Matrix4
  Camera::getProjectionMatrix (){
    return m_projectionMatrix;
  };

  /// \brief Resets the camera to its original pose.
  /// \post The position (eye point) is the same as what had been specified in
  ///   the constructor.
  /// \post The back vector is the same as what had been specified in the
  ///   constructor.
  /// \post The up and right vectors are computed as they had been in the
  ///   constructor.
  void
  Camera::resetPose (){
    m_update = true;
    m_world.setPosition(m_starting_world.getPosition());
    m_world.setOrientation(m_starting_world.getOrientation());
    
    //m_eyePosition = m_startingEyePosition;
    //m_camMatrix = m_startingCamMatrix;
  };

