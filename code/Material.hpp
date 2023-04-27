#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Vector3.hpp"
#include "ShaderProgram.hpp"
#include <assimp/Importer.hpp>      
#include <assimp/scene.h>           
#include <assimp/postprocess.h>

class Material
{

private:
    
    Vector3  uAmbientReflection; 
    Vector3  uDiffuseReflection; 
    Vector3  uSpecularReflection; 
    float uSpecularPower; 
    Vector3  uEmissiveIntensity; 

public:
    
    Material(Vector3  AmbientReflection = {1,1,1}, Vector3  DiffuseReflection = {1,1,1}, Vector3  SpecularReflection = {1,1,1}, 
            float SpecularPower = 1, Vector3  EmissiveIntensity = {0,0,0});
    
    Material(aiMaterial material);

    ~Material();

    void
    setShader(ShaderProgram& program);

};

#endif