#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Vector3.hpp"
#include "ShaderProgram.hpp"
#include "Material.hpp"
#include <assimp/Importer.hpp>      
#include <assimp/scene.h>           
#include <assimp/postprocess.h>

Material::Material(Vector3  AmbientReflection, Vector3 DiffuseReflection, Vector3  SpecularReflection, 
            float SpecularPower, Vector3 EmissiveIntensity)
            :uAmbientReflection(AmbientReflection), uDiffuseReflection(DiffuseReflection),
            uSpecularReflection(SpecularReflection), uSpecularPower(SpecularPower), uEmissiveIntensity(EmissiveIntensity)
            {};

Material::Material(aiMaterial material)
            {

                aiColor3D color;
                float number;
                if (material.Get (AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS) {
                    uAmbientReflection.m_x = color.r;
                    uAmbientReflection.m_y = color.g;
                    uAmbientReflection.m_z = color.b;
                }
                if (material.Get (AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS) {
                    uDiffuseReflection.m_x = color.r;
                    uDiffuseReflection.m_y = color.g;
                    uDiffuseReflection.m_z = color.b;
                }
                if (material.Get (AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS) {
                    uSpecularReflection.m_x = color.r;
                    uSpecularReflection.m_y = color.g;
                    uSpecularReflection.m_z = color.b;
                }
                if (material.Get (AI_MATKEY_COLOR_EMISSIVE, color) == AI_SUCCESS) {
                    uEmissiveIntensity.m_x = color.r;
                    uEmissiveIntensity.m_y = color.g;
                    uEmissiveIntensity.m_z = color.b;
                }
                if (material.Get (AI_MATKEY_SHININESS, number) == AI_SUCCESS) {
                    uSpecularPower = number;
                }
            }

Material::~Material(){};

void
Material::setShader(ShaderProgram& program)
{
  program.setUniformVec3 ("uAmbientReflection", uAmbientReflection);
  program.setUniformVec3 ("uEmissiveIntensity", uEmissiveIntensity);
  program.setUniformVec3 ("uDiffuseReflection", uDiffuseReflection);
  program.setUniformVec3 ("uSpecularReflection", uSpecularReflection);
  program.setUniformFloat ("uSpecularPower", uSpecularPower);
}


