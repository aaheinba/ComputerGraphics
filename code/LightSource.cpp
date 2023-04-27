/// \file LightSource.cpp
/// \brief classes for light sources.
/// \author Chad Hogg & Aaron Heinbugh
/// \version A09
#include "Vector3.hpp"
#include "ShaderProgram.hpp"
#include "LightSource.hpp"

  LightSource::LightSource (const Vector3& diffuseIntensity, const Vector3& specularIntensity)
  {
      m_diffuseIntensity = diffuseIntensity;
      m_specularIntensity = specularIntensity;
  }

  LightSource::~LightSource (){}

  void 
  LightSource::setUniforms (ShaderProgram* program, int lightNum)
  {
      program->setUniformVec3("uLights[" + std::to_string(lightNum) + "].diffuseIntensity", m_diffuseIntensity);
      program->setUniformVec3("uLights[" + std::to_string(lightNum) + "].specularIntensity", m_specularIntensity);
  }





  DirectionalLightSource::DirectionalLightSource (const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& direction):
  LightSource::LightSource(diffuseIntensity, specularIntensity)
  {
      m_direction = direction;
  }
  
  DirectionalLightSource::~DirectionalLightSource (){}
  
  void 
  DirectionalLightSource::setUniforms (ShaderProgram* program, int lightNum)
  {
      LightSource::setUniforms(program, lightNum);
      program->setUniformVec3("uLights[" + std::to_string(lightNum) + "].direction", m_direction);
      program->setUniformInt("uLights[" + std::to_string(lightNum) + "].type", 0);
  }





  LocationLightSource::LocationLightSource (const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& position, const Vector3& attenuationCoefficients):
  LightSource::LightSource(diffuseIntensity, specularIntensity)
  {
      m_position = position;
      m_attenuationCoefficients = attenuationCoefficients;
  }
  
  LocationLightSource::~LocationLightSource (){}
  
  void 
  LocationLightSource::setUniforms (ShaderProgram* program, int lightNum)
  {
      LightSource::setUniforms(program, lightNum);
      program->setUniformVec3("uLights[" + std::to_string(lightNum) + "].position", m_position);
      program->setUniformVec3("uLights[" + std::to_string(lightNum) + "].attenuationCoefficients", m_attenuationCoefficients);
  }





  PointLightSource::PointLightSource (const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& position, const Vector3& attenuationCoefficients):
  LocationLightSource::LocationLightSource(diffuseIntensity, specularIntensity, position, attenuationCoefficients)
  {}
  
  PointLightSource::~PointLightSource (){}
  
  void 
  PointLightSource::setUniforms (ShaderProgram* program, int lightNum){
      LocationLightSource::setUniforms(program, lightNum);
      program->setUniformInt("uLights[" + std::to_string(lightNum) + "].type", 1);

  }





  SpotLightSource::SpotLightSource (const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& position, const Vector3& attenuationCoefficients, const Vector3& direction, float cutoffCosAngle, float falloff)
  :LocationLightSource::LocationLightSource(diffuseIntensity, specularIntensity, position, attenuationCoefficients)
  {
      m_direction = direction;
      m_cutoffCosAngle = cutoffCosAngle;
      m_falloff = falloff;
  }
  
  SpotLightSource::~SpotLightSource (){}
  
  void 
  SpotLightSource::setUniforms (ShaderProgram* program, int lightNum)
  {
      LocationLightSource::setUniforms(program, lightNum);
      program->setUniformVec3("uLights[" + std::to_string(lightNum) + "].direction", m_direction);
      program->setUniformFloat("uLights[" + std::to_string(lightNum) + "].cutoffCosAngle", m_cutoffCosAngle);
      program->setUniformFloat("uLights[" + std::to_string(lightNum) + "].falloff", m_falloff);
      program->setUniformInt("uLights[" + std::to_string(lightNum) + "].type", 2);

  }