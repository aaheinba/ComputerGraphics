/// \file LightSource.hpp
/// \brief Declaration of classes for light sources.
/// \author Chad Hogg
/// \version A09

#ifndef LIGHT_SOURCE_HPP
#define LIGHT_SOURCE_HPP

#include "Vector3.hpp"
#include "ShaderProgram.hpp"

enum LightType {
  DIRECTIONAL = 0,
  POINT = 1,
  SPOT = 2
};

class LightSource {
public:
  LightSource (const Vector3& diffuseIntensity, const Vector3& specularIntensity);
  virtual ~LightSource ();
  virtual void setUniforms (ShaderProgram* program, int lightNum);
private:
  Vector3 m_diffuseIntensity;
  Vector3 m_specularIntensity;
};

class DirectionalLightSource : public LightSource {
public:
  DirectionalLightSource (const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& direction);
  virtual ~DirectionalLightSource ();
  virtual void setUniforms (ShaderProgram* program, int lightNum);
private:
  Vector3 m_direction;
};

class LocationLightSource : public LightSource {
public:
  LocationLightSource (const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& position, const Vector3& attenuationCoefficients);
  virtual ~LocationLightSource ();
  virtual void setUniforms (ShaderProgram* program, int lightNum);
private:
  Vector3 m_position;
  Vector3 m_attenuationCoefficients;
};

class PointLightSource : public LocationLightSource {
public:
  PointLightSource (const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& position, const Vector3& attenuationCoefficients);
  virtual ~PointLightSource ();
  virtual void setUniforms (ShaderProgram* program, int lightNum);
};

class SpotLightSource : public LocationLightSource {
public:
  SpotLightSource (const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& position, const Vector3& attenuationCoefficients, const Vector3& direction, float cutoffCosAngle, float falloff);
  virtual ~SpotLightSource ();
  virtual void setUniforms (ShaderProgram* program, int lightNum);
private:
  Vector3 m_direction;
  float m_cutoffCosAngle;
  float m_falloff;
};

#endif//LIGHT_SOURCE_HPP
