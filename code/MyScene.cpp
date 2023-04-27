/// \file MyScene.cpp
/// \brief MyScene class and any associated global functions.
/// \author Aaron Heinbaugh
/// \version A02
#include <vector>
#include "Scene.hpp"
#include "MyScene.hpp"
#include "Mesh.hpp"
#include "OpenGLContext.hpp"
#include <glm/mat4x4.hpp>
#include "ShaderProgram.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "RealOpenGLContext.hpp"
#include <string>
#include <utility>
#include "Geometry.hpp"
#include "ColorMesh.hpp"
#include "NormalsMesh.hpp"
#include <assimp/Importer.hpp>      
#include <assimp/scene.h>           
#include <assimp/postprocess.h>
#include <array>
#include "Material.hpp"
#include "LightSource.hpp"

MyScene::MyScene (OpenGLContext* context, ShaderProgram* shader, ShaderProgram* shaderNorm){
  
  std::vector<float> triVertices {
    5.0f, 5.0f, 0.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    1.0f, 0.0f, 0.0f,   // color of first vertex (R, G, B)
    3.0f, 3.0f, 0.0f, // 3-d coordinates of second vertex (X, Y, Z)
    0.0f, 1.0f, 0.0f,   // color of second vertex (R, G, B)
    7.0f, 3.0f, 0.0f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,    // color of third vertex (R, G, B)
  }; 

  std::vector<float> bigtriangle {
    20,20,-4,
    1.0,0,0,
    -20,-20,-4,
    0,1,0,
    20,-20,-4,
    0,0,1
  };

    std::vector<float> bigtriangle2 {
    20,-4,20,
    1.0,0,0,
    -20,-4,-20,
    0,1,0,
    -20,-4,20,
    0,0,1
  };

  std::vector<float> ChessSquare {
     0,0,0,
     0,0,0,
     0,0,1,
     0,0,0,
     1,0,0,
     0,0,0,
     1,0,0,
     0,0,0,
     0,0,1,
     0,0,0,
     1,0,1,
     0,0,0
  };

   std::vector<float> ChessSquare2 {
     0,0,0,
     1,1,1,
     0,0,1,
          1,1,1,

     1,0,0,
          1,1,1,

     1,0,0,
          1,1,1,

     0,0,1,
          1,1,1,

     1,0,1,
          1,1,1,

  };

std::vector<float> chesboard {
   -4.000000, 0.000000, -4.00000,
   1,1,1,
 -3.000000, 0.000000, -4.00000,
    1,1,1,
 -2.000000, 0.000000, -4.00000,
    1,1,1,
 -1.000000, 0.000000, -4.00000,
    0,0,0,
 0.000000 ,0.000000 ,-4.000000,
     0,0,0,
 1.000000 ,0.000000 ,-4.000000,
     0,0,0,
 2.000000 ,0.000000 ,-4.000000,
    1,1,1,
 3.000000 ,0.000000 ,-4.000000,
    1,1,1,
 4.000000 ,0.000000 ,-4.000000,
    1,1,1,
 -4.000000, 0.000000, -3.00000,
     0,0,0,
 -3.000000, 0.000000, -3.00000,
     0,0,0,
 -2.000000, 0.000000, -3.00000,
     0,0,0,
 -1.000000, 0.000000, -3.00000,
    1,1,1,
 0.000000 ,0.000000 ,-3.000000,
    1,1,1,
 1.000000 ,0.000000 ,-3.000000,
    1,1,1,
 2.000000 ,0.000000 ,-3.000000,
     0,0,0,
 3.000000 ,0.000000 ,-3.000000,
     0,0,0,
 4.000000 ,0.000000 ,-3.000000,
     0,0,0,
 -4.000000, 0.000000, -2.00000,
    1,1,1,
 -3.000000, 0.000000, -2.00000,
    1,1,1,
 -2.000000, 0.000000, -2.00000,
    1,1,1,
 -1.000000, 0.000000, -2.00000,
     0,0,0,
 0.000000 ,0.000000 ,-2.000000,
     0,0,0,
 1.000000 ,0.000000 ,-2.000000,
     0,0,0,
 2.000000 ,0.000000 ,-2.000000,
    1,1,1,
 3.000000 ,0.000000 ,-2.000000,
    1,1,1,
 4.000000 ,0.000000 ,-2.000000,
    1,1,1,
 -4.000000, 0.000000, -1.00000,
     0,0,0,
 -3.000000, 0.000000, -1.00000,
     0,0,0,
 -2.000000, 0.000000, -1.00000,
     0,0,0,
 -1.000000, 0.000000, -1.00000,
    1,1,1,
 0.000000 ,0.000000 ,-1.000000,
    1,1,1,
 1.000000 ,0.000000 ,-1.000000,
    1,1,1,
 2.000000 ,0.000000 ,-1.000000,
     0,0,0,
 3.000000 ,0.000000 ,-1.000000,
     0,0,0,
 4.000000 ,0.000000 ,-1.000000,
     0,0,0,
 -4.000000, 0.000000, 0.000000,
    1,1,1,
 -3.000000, 0.000000, 0.000000,
    1,1,1,
 -2.000000, 0.000000, 0.000000,
    1,1,1,
 -1.000000, 0.000000, 0.000000,
     0,0,0,
 0.000000 ,0.000000, 0.000000,
     0,0,0,
 1.000000 ,0.000000 ,0.000000,
     0,0,0,
 2.000000 ,0.000000 ,0.000000,
    1,1,1,
 3.000000 ,0.000000 ,0.000000,
    1,1,1,
 4.000000 ,0.000000 ,0.000000,
    1,1,1,
 -4.000000, -0.000000, 1.00000,
     0,0,0,
 -3.000000, -0.000000, 1.00000,
     0,0,0,
 -2.000000, -0.000000, 1.00000,
     0,0,0,
 -1.000000, -0.000000, 1.00000,
    1,1,1,
 0.000000 ,-0.000000 ,1.000000,
    1,1,1,
 1.000000 ,-0.000000 ,1.000000,
    1,1,1,
 2.000000 ,-0.000000 ,1.000000,
     0,0,0,
 3.000000 ,-0.000000 ,1.000000,
     0,0,0,
 4.000000 ,-0.000000 ,1.000000,
     0,0,0,
 -4.000000, -0.000000, 2.00000,
    1,1,1,
 -3.000000, -0.000000, 2.00000,
    1,1,1,
 -2.000000, -0.000000, 2.00000,
    1,1,1,
 -1.000000, -0.000000, 2.00000,
     0,0,0,
 0.000000 ,-0.000000 ,2.000000,
     0,0,0,
 1.000000 ,-0.000000 ,2.000000,
     0,0,0,
 2.000000 ,-0.000000 ,2.000000,
    1,1,1,
 3.000000 ,-0.000000 ,2.000000,
    1,1,1,
 4.000000 ,-0.000000 ,2.000000,
    1,1,1,
 -4.000000, -0.000000, 3.00000,
     0,0,0,
 -3.000000, -0.000000, 3.00000,
     0,0,0,
 -2.000000, -0.000000, 3.00000,
     0,0,0,
 -1.000000, -0.000000, 3.00000,
    1,1,1,
 0.000000 ,-0.000000 ,3.000000,
    1,1,1,
 1.000000 ,-0.000000 ,3.000000,
    1,1,1,
 2.000000 ,-0.000000 ,3.000000,
     0,0,0,
 3.000000 ,-0.000000 ,3.000000,
     0,0,0,
 4.000000 ,-0.000000 ,3.000000,
     0,0,0,
 -4.000000, -0.000000, 4.00000,
    1,1,1,
 -3.000000, -0.000000, 4.00000,
    1,1,1,
 -2.000000, -0.000000, 4.00000,
    1,1,1,
 -1.000000, -0.000000, 4.00000,
     0,0,0,
 0.000000 ,-0.000000 ,4.000000,
     0,0,0,
 1.000000 ,-0.000000 ,4.000000,
     0,0,0,
 2.000000 ,-0.000000 ,4.000000,
    1,1,1,
 3.000000 ,-0.000000 ,4.000000,
    1,1,1,
 4.000000 ,-0.000000 ,4.000000,
    1,1,1
};

  std::vector<float> triVertices2 {
    -1.0f,-1.0f,-1.0f,
    1.0f, 0.5f, 0.0f,
    -1.0f,-1.0f, 1.0f,
    0.5f, 0.5f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    0.24f, 0.65f, 0.05f,
    1.0f, 1.0f,-1.0f,
    0.21f, 0.5f, 0.89f,
    -1.0f,-1.0f,-1.0f,
    0.12f, 0.99f, 0.5f,
    -1.0f, 1.0f,-1.0f,
    0.65f, 0.12f, 0.54f,
    1.0f,-1.0f, 1.0f,
    0.98f, 0.5f, 0.85f,
    -1.0f,-1.0f,-1.0f,
    0.87f, 0.54f, 0.55f,
    1.0f,-1.0f,-1.0f,
    0.2f, 0.4f, 0.1f,
    1.0f, 1.0f,-1.0f,
    0.99f, 0.3f, 0.8f,
    1.0f,-1.0f,-1.0f,
    0.5f, 0.5f, 0.5f,
    -1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    0.4f, 0.87f, 0.5f,
    -1.0f, 1.0f, 1.0f,
    0.10f, 0.89f, 0.65f,
    -1.0f, 1.0f,-1.0f,
    0.25f, 0.26f, 0.24f,
    1.0f,-1.0f, 1.0f,
    0.1f, 0.9f, 0.8f,
    -1.0f,-1.0f, 1.0f,
    0.2f, 0.3f, 0.7f,
    -1.0f,-1.0f,-1.0f,
    0.6f, 0.9f, 0.5f,
    -1.0f, 1.0f, 1.0f,
    0.5f, 0.7f, 0.5f,
    -1.0f,-1.0f, 1.0f,
    0.5f, 0.6f, 0.5f,
    1.0f,-1.0f, 1.0f,
    0.5f, 0.7f, 0.8f,
    1.0f, 1.0f, 1.0f,
    0.1f, 0.5f, 0.6f,
    1.0f,-1.0f,-1.0f,
    0.1f, 0.2f, 0.3f,
    1.0f, 1.0f,-1.0f,
    0.7f, 0.8f, 0.9f,
    1.0f,-1.0f,-1.0f,
    0.5f, 0.2f, 0.9f,
    1.0f, 1.0f, 1.0f,
    0.4f, 0.5f, 0.6f,
    1.0f,-1.0f, 1.0f,
    0.8f, 0.5f, 0.7f,
    1.0f, 1.0f, 1.0f,
    0.4f, 0.4f, 0.1f,
    1.0f, 1.0f,-1.0f,
    0.9f, 0.1f, 0.1f,
    -1.0f, 1.0f,-1.0f,
    0.8f, 0.7f, 0.1f,
    1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f,
    -1.0f, 1.0f,-1.0f,
    0.2f, 0.7f, 0.6f,
    -1.0f, 1.0f, 1.0f,
    0.8f, 0.4f, 0.9f,
    1.0f, 1.0f, 1.0f,
    0.4f, 0.1f, 0.8f,
    -1.0f, 1.0f, 1.0f,
    0.8f, 0.6f, 0.2f,
    1.0f,-1.0f, 1.0f,
    0.8f, 0.1f, 0.6f,
};
  
  shaderNorm->enable();
  shaderNorm->setUniformInt("uNumLights", 4);
  shaderNorm->setUniformVec3("uAmbientIntensity", Vector3(0.1,0.1,0.1));
  //LightSource a1 = LightSource(Vector3(0.6,0.6,0.6), Vector3(0.6,0.6,0.6));
  //DirectionalLightSource sun (Vector3(0.5, 0.5, 0.5), Vector3(0.5,0.5,0.5), Vector3(0,-1,0));
  //SpotLightSource spotlight (Vector3())
  //sun.setUniforms(shaderNorm, 0);

//Lights
  
///// Light 0 /////

  //type  0 if directional, 1 if point, 2 if spot
  shaderNorm->setUniformInt("uLights[0].type", 0);  
  
  // All lights have these parameters
  shaderNorm->setUniformVec3("uLights[0].diffuseIntensity", Vector3(0.5,0.5,0.5));
  shaderNorm->setUniformVec3("uLights[0].specularIntensity", Vector3(0.5,0.5,0.5));

  // Point and spot light parameters.
  //shaderNorm->setUniformVec3("uLights[0].position", Vector3(1,2,1));
  //shaderNorm->setUniformVec3("uLights[0].attenuationCoefficients", Vector3(0.1,0.1,0.1));

  // Directional and spot light parameter.
  shaderNorm->setUniformVec3("uLights[0].direction", Vector3(0,-1,0));

  // Spot light parameters.
  //shaderNorm->setUniformFloat("uLights[0].cutoffCosAngle", 45);
  //shaderNorm->setUniformFloat("uLights[0].falloff", 0.5);

//////Light 1////////

  //type  0 if directional, 1 if point, 2 if spot
  shaderNorm->setUniformInt("uLights[1].type", 0);  
  
  // All lights have these parameters.
  shaderNorm->setUniformVec3("uLights[1].diffuseIntensity", Vector3(0.3,0.3,0.3));
  shaderNorm->setUniformVec3("uLights[1].specularIntensity", Vector3(0.3,0.3,0.3));

  // Point and spot light parameters.
  //shaderNorm->setUniformVec3("uLights[1].position", Vector3(6,2,6));
  //shaderNorm->setUniformVec3("uLights[1].attenuationCoefficients", Vector3(0.1,0.1,0.1));

  // Directional and spot light parameter.
  shaderNorm->setUniformVec3("uLights[1].direction", Vector3(-1,0,0));

  // Spot light parameters.
  //shaderNorm->setUniformFloat("uLights[1].cutoffCosAngle", XXXX);
  //shaderNorm->setUniformFloat("uLights[1].falloff", XXXX);
/*
Note: this is intended to be a spot light to illuminate where each move ends
but my spot lights are not functional
light type should be 2 but again not functional
*/
//Light 2
  //type  0 if directional, 1 if point, 2 if spot
  shaderNorm->setUniformInt("uLights[2].type", 1);  
  
  // All lights have these parameters.
  shaderNorm->setUniformVec3("uLights[2].diffuseIntensity", Vector3(0.7,.7,0.7));
  shaderNorm->setUniformVec3("uLights[2].specularIntensity", Vector3(0.7,.7,.7));

  // Point and spot light parameters.
  shaderNorm->setUniformVec3("uLights[2].position", Vector3(4,2,4));
  shaderNorm->setUniformVec3("uLights[2].attenuationCoefficients", Vector3(0.1,0.1,0.1));

  // Directional and spot light parameter.
  shaderNorm->setUniformVec3("uLights[2].direction", Vector3(0,1,0));

  // Spot light parameters.
  shaderNorm->setUniformFloat("uLights[2].cutoffCosAngle", 10);
  shaderNorm->setUniformFloat("uLights[2].falloff", 100);

//blue point light to illuminate if a king is in check
//Light 3
  //type  0 if directional, 1 if point, 2 if spot
  shaderNorm->setUniformInt("uLights[3].type", 1);  
  
  // All lights have these parameters.
  shaderNorm->setUniformVec3("uLights[3].diffuseIntensity", Vector3(0,0,1));
  shaderNorm->setUniformVec3("uLights[3].specularIntensity", Vector3(0,0,1));

  // Point and spot light parameters.
  shaderNorm->setUniformVec3("uLights[3].position", Vector3(3,100,7));
  shaderNorm->setUniformVec3("uLights[3].attenuationCoefficients", Vector3(0.1,0.1,0.1));

  // Directional and spot light parameter.
  //shaderNorm->setUniformVec3("uLights[3].direction", Vector3(0,-1,0));

  // Spot light parameters.
  //shaderNorm->setUniformFloat("uLights[3].cutoffCosAngle", XXXX);
  //shaderNorm->setUniformFloat("uLights[3].falloff", XXXX);
/*
//Light 4
  //type  0 if directional, 1 if point, 2 if spot
  shaderNorm->setUniformInt("uLights[4].type", XXXXX);  
  
  // All lights have these parameters.
  shaderNorm->setUniformVec3("uLights[4].diffuseIntensity", Vector3(XXXXX));
  shaderNorm->setUniformVec3("uLights[4].specularIntensity", Vector3(XXXX));

  // Point and spot light parameters.
  shaderNorm->setUniformVec3("uLights[4].position", Vector3(XXXX));
  shaderNorm->setUniformVec3("uLights[4].attenuationCoefficients", Vector3(XXXXX));

  // Directional and spot light parameter.
  shaderNorm->setUniformVec3("uLights[4].direction", Vector3(XXXX));

  // Spot light parameters.
  shaderNorm->setUniformFloat("uLights[4].cutoffCosAngle", XXXX);
  shaderNorm->setUniformFloat("uLights[4].falloff", XXXX);

//Light 5
  //type  0 if directional, 1 if point, 2 if spot
  shaderNorm->setUniformInt("uLights[5].type", XXXXX);  
  
  // All lights have these parameters.
  shaderNorm->setUniformVec3("uLights[5].diffuseIntensity", Vector3(XXXXX));
  shaderNorm->setUniformVec3("uLights[5].specularIntensity", Vector3(XXXX));

  // Point and spot light parameters.
  shaderNorm->setUniformVec3("uLights[5].position", Vector3(XXXX));
  shaderNorm->setUniformVec3("uLights[5].attenuationCoefficients", Vector3(XXXXX));

  // Directional and spot light parameter.
  shaderNorm->setUniformVec3("uLights[5].direction", Vector3(XXXX));

  // Spot light parameters.
  shaderNorm->setUniformFloat("uLights[5].cutoffCosAngle", XXXX);
  shaderNorm->setUniformFloat("uLights[5].falloff", XXXX);

//Light 6
  //type  0 if directional, 1 if point, 2 if spot
  shaderNorm->setUniformInt("uLights[6].type", XXXXX);  
  
  // All lights have these parameters.
  shaderNorm->setUniformVec3("uLights[6].diffuseIntensity", Vector3(XXXXX));
  shaderNorm->setUniformVec3("uLights[6].specularIntensity", Vector3(XXXX));

  // Point and spot light parameters.
  shaderNorm->setUniformVec3("uLights[6].position", Vector3(XXXX));
  shaderNorm->setUniformVec3("uLights[6].attenuationCoefficients", Vector3(XXXXX));

  // Directional and spot light parameter.
  shaderNorm->setUniformVec3("uLights[6].direction", Vector3(XXXX));

  // Spot light parameters.
  shaderNorm->setUniformFloat("uLights[6].cutoffCosAngle", XXXX);
  shaderNorm->setUniformFloat("uLights[6].falloff", XXXX);

//Light 7
  //type  0 if directional, 1 if point, 2 if spot
  shaderNorm->setUniformInt("uLights[7].type", XXXXX);  
  
  // All lights have these parameters.
  shaderNorm->setUniformVec3("uLights[7].diffuseIntensity", Vector3(XXXXX));
  shaderNorm->setUniformVec3("uLights[7].specularIntensity", Vector3(XXXX));

  // Point and spot light parameters.
  shaderNorm->setUniformVec3("uLights[7].position", Vector3(XXXX));
  shaderNorm->setUniformVec3("uLights[7].attenuationCoefficients", Vector3(XXXXX));

  // Directional and spot light parameter.
  shaderNorm->setUniformVec3("uLights[7].direction", Vector3(XXXX));

  // Spot light parameters.
  shaderNorm->setUniformFloat("uLights[7].cutoffCosAngle", XXXX);
  shaderNorm->setUniformFloat("uLights[7].falloff", XXXX);
*/
   
  Material *cyan = new Material(Vector3(0,0.05,0.05), Vector3(0.4,0.5,0.5), Vector3(0.04, 0.7, 0.7), 0.078125f, Vector3(0,0,0));
  //green
  Material *green = new Material(Vector3(0,0,0), Vector3(0.1,0.35,0.1),Vector3(0.45,0.55,0.45), 0.25f, Vector3(0,0,0));
  
  //bronze
  Material *bronze = new Material(Vector3(0.2125, 	0.1275, 	0.054), Vector3(0.714 ,	0.4284, 	0.18144), Vector3(0.393548 ,	0.271906 ,	0.166721), 0.2, Vector3(0,0,0));
 
  Material *blackplastic = new Material(Vector3(0.0 	,0.0, 	0.0), Vector3(.01 ,	0.01 	,0.01), Vector3(0.50 ,	0.50 ,	0.50), .25,Vector3(0,0,0) );
  Material *whiteplastic = new Material(Vector3(0.0 	,0.0 ,	0.0),Vector3(0.55 	,0.55 ,	0.55),Vector3(0.70 ,	0.70 ,	0.70),.25,Vector3(0.0 ,	0.0 ,	0.0));
  Material *obsidian = new Material(Vector3(0.05375, 	0.05 ,	0.06625),Vector3(0.18275 	,0.17 	,0.22525),Vector3(.332741 ,	0.328634 ,	0.346435),0.3,Vector3(0,0,0));
    Material *silver = new Material(Vector3(0.19225, 	0.19225 ,	0.19225),Vector3(0.50754 	,0.50754 ,	0.50754),Vector3( 	0.508273 	,0.508273 ,	0.508273),.4,Vector3(0,0,0));
   
   //emerald
   Material *emerald = new Material(Vector3(0.0215 ,	0.1745 ,	0.0215),Vector3(.07568 ,	0.61424, 	0.07568),Vector3(0.633 ,	0.727811 ,	0.633),.6,Vector3(0,0,0));
/*
  NormalsMesh* bigT = new NormalsMesh(context, shaderNorm);
  std::vector<unsigned int> indices3;
  std::vector<float> geo3;
  indexData(bigtriangle, 6, geo3, indices3);
  bigT->addGeometry(geo3);
  bigT->addIndices(indices3);
  bigT->prepareVao();
  bigT->setMaterial(*bronze);
  add("bigT", bigT);

  NormalsMesh* bigT2 = new NormalsMesh(context, shaderNorm);
  indexData(bigtriangle2, 6, geo3, indices3);
  bigT2->addGeometry(geo3);
  bigT2->addIndices(indices3);
  bigT2->prepareVao();
  bigT2->setMaterial(*bronze);
  add("bigT2", bigT2);
*/

  NormalsMesh* square = new NormalsMesh(context, shaderNorm);
  std::vector<unsigned int> indices3;
  std::vector<float> geo3;
  indexData(ChessSquare2, 6, geo3, indices3);
  square->addGeometry(geo3);
  square->addIndices(indices3);
  square->setMaterial(*blackplastic);
  square->moveBack(-0.5);
  square->moveRight(-0.5);
  square->prepareVao();
  square->scaleLocal(8);
  add("square", square);





/*
  ColorMesh* cube = new ColorMesh(context, shader);
  std::vector<unsigned int> indices;
  std::vector<float> geo;
  indexData(triVertices2, 6, geo, indices);
  cube->addGeometry(geo);
  cube->addIndices(indices);

  cube->moveUp(1);
  cube->scaleLocal(.1);
  cube->prepareVao();
  add("cube", cube);

   ColorMesh* cube2 = new ColorMesh(context, shader);
  cube2->addGeometry(geo);
  cube2->addIndices(indices);
  cube2->moveRight(6);
  cube2->moveBack(6);
  cube2->moveUp(1);
  cube2->scaleLocal(.1);
  cube2->prepareVao();
  add("cube2", cube2);
*/
/*
  ColorMesh* triangle = new ColorMesh(context, shader);
  std::vector<unsigned int> indices2;
  std::vector<float> geo2;
  indexData(triVertices, 6, geo2, indices2);
  triangle->addGeometry(geo2);
  triangle->addIndices(indices2);
  triangle->shearLocalZByXy(0.75, 1.25);
  triangle->moveUp(-1.0);
  triangle->prepareVao();

  add("triangle", triangle);
  add("cube", cube);

  NormalsMesh* cube1 = new NormalsMesh(context, shaderNorm);
  std::vector<Triangle> cube1tri = buildCube();
  std::vector<float> cubeVertexNorm = dataWithVertexNormals(cube1tri, computeVertexNormals(cube1tri, computeFaceNormals(cube1tri)));
  std::vector<unsigned int> cube1indices;
  std::vector<float> cube1geo;
  indexData(cubeVertexNorm, 6, cube1geo, cube1indices);
  cube1->addGeometry(cube1geo);
  cube1->addIndices(cube1indices);
  cube1->moveRight(-1.0);
  cube1->prepareVao();
  cube1->setMaterial(*emerald);
  add("cube1", cube1);

  NormalsMesh* cube2 = new NormalsMesh(context, shaderNorm);
  std::vector<float> cubeFaceNorm = dataWithFaceNormals(cube1tri, computeFaceNormals(cube1tri));
  std::vector<unsigned int> cube2indices;
  std::vector<float> cube2geo;
  indexData(cubeFaceNorm, 6, cube2geo, cube2indices);
  cube2->addGeometry(cube2geo);
  cube2->addIndices(cube2indices);
  cube2->moveRight(-1.0);
  cube2->moveUp(1.5);
  cube2->setMaterial(*bronze);
  cube2->prepareVao();
  add("cube2", cube2);

  ColorMesh* cube3 = new ColorMesh(context, shader);
  std::vector<float> cubeVertColor = dataWithVertexColors(cube1tri, generateRandomVertexColors(cube1tri));
  std::vector<unsigned int> cube3indices;
  std::vector<float> cube3geo;
  indexData(cubeVertColor, 6, cube3geo, cube3indices);
  cube3->addGeometry(cube3geo);
  cube3->addIndices(cube3indices);
  cube3->moveRight(-1.0);
  cube3->moveUp(-1.5);
  cube3->prepareVao();
  add("cube3", cube3);

  ColorMesh* cube4 = new ColorMesh(context, shader);
  std::vector<float> cubeFaceColor = dataWithFaceColors(cube1tri, generateRandomFaceColors(cube1tri));
  std::vector<unsigned int> cube4indices;
  std::vector<float> cube4geo;
  indexData(cubeFaceColor, 6, cube4geo, cube4indices);
  cube4->addGeometry(cube4geo);
  cube4->addIndices(cube4indices);
  cube4->moveRight(-1.0);
  cube4->moveUp(-3.0);
  cube4->prepareVao();
  add("cube4", cube4);

  NormalsMesh* bear = new NormalsMesh(context, shaderNorm, "models/bear.obj", 0);
  bear->scaleWorld(0.25);
  bear->moveRight(14.0);
  bear->moveUp(-10.0);
  bear->setMaterial(*bronze);
  bear->prepareVao();
  add("bear", bear);
*/

  NormalsMesh* checkers = new NormalsMesh(context, shaderNorm, "models/checkers.obj", 0);
  checkers->setMaterial(*whiteplastic);
  checkers->moveUp(0.002);
  checkers->prepareVao();
  add("checkers", checkers);


  NormalsMesh* rook = new NormalsMesh(context, shaderNorm, "models/rook2.obj", 0);
  rook->setMaterial(*bronze);
  //rook2->moveBack(1);
  rook->scaleLocal(0.1);
  rook->prepareVao();
  add("rook", rook);

   NormalsMesh* rook2 = new NormalsMesh(context, shaderNorm, "models/rook2.obj", 0);
  rook2->setMaterial(*bronze);
  rook2->moveRight(7);
  rook2->scaleLocal(0.1);
  rook2->prepareVao();
  add("rook2", rook2);

  NormalsMesh* brook1 = new NormalsMesh(context, shaderNorm, "models/rook2.obj", 0);
  brook1->setMaterial(*emerald);
  brook1->moveRight(7);
  brook1->moveBack(7);
  brook1->scaleLocal(0.1);
  brook1->prepareVao();
  add("brook1", brook1);

  NormalsMesh* brook2 = new NormalsMesh(context, shaderNorm, "models/rook2.obj", 0);
  brook2->setMaterial(*emerald);
  brook2->moveBack(7);
  brook2->scaleLocal(0.1);
  brook2->prepareVao();
  add("brook2", brook2);

  NormalsMesh* queen = new NormalsMesh(context, shaderNorm, "models/queen.obj", 0);
  queen->setMaterial(*bronze);
  queen->moveRight(4);
  queen->scaleLocal(0.25);
  queen->prepareVao();
  add("queen", queen);

  NormalsMesh* bqueen = new NormalsMesh(context, shaderNorm, "models/queen.obj", 0);
  bqueen->setMaterial(*emerald);
  bqueen->moveRight(4);
  bqueen->moveBack(7);
  bqueen->scaleLocal(0.25);
  bqueen->prepareVao();
  add("bqueen", bqueen);

  NormalsMesh* pawn = new NormalsMesh(context, shaderNorm, "models/pawn.obj", 0);
  pawn->setMaterial(*bronze);
  pawn->moveBack(1);
  pawn->scaleLocal(0.1);
  pawn->prepareVao();
  add("pawn", pawn);

  NormalsMesh* pawn2 = new NormalsMesh(context, shaderNorm, "models/pawn.obj", 0);
  pawn2->setMaterial(*bronze);
  pawn2->moveBack(1);
  pawn2->moveRight(1);
  pawn2->scaleLocal(0.1);
  pawn2->prepareVao();
  add("pawn2", pawn2);

    NormalsMesh* pawn3 = new NormalsMesh(context, shaderNorm, "models/pawn.obj", 0);
  pawn3->setMaterial(*bronze);
  pawn3->moveBack(1);
  pawn3->moveRight(2);
  pawn3->scaleLocal(0.1);
  pawn3->prepareVao();
  add("pawn3", pawn3);

    NormalsMesh* pawn4 = new NormalsMesh(context, shaderNorm, "models/pawn.obj", 0);
  pawn4->setMaterial(*bronze);
  pawn4->moveBack(1);
  pawn4->moveRight(3);
  pawn4->scaleLocal(0.1);
  pawn4->prepareVao();
  add("pawn4", pawn4);

    NormalsMesh* pawn5 = new NormalsMesh(context, shaderNorm, "models/pawn.obj", 0);
  pawn5->setMaterial(*bronze);
  pawn5->moveBack(1);
  pawn5->moveRight(4);
  pawn5->scaleLocal(0.1);
  pawn5->prepareVao();
  add("pawn5", pawn5);

    NormalsMesh* pawn6 = new NormalsMesh(context, shaderNorm, "models/pawn.obj", 0);
  pawn6->setMaterial(*bronze);
  pawn6->moveBack(1);
  pawn6->moveRight(5);
  pawn6->scaleLocal(0.1);
  pawn6->prepareVao();
  add("pawn6", pawn6);

    NormalsMesh* pawn7 = new NormalsMesh(context, shaderNorm, "models/pawn.obj", 0);
  pawn7->setMaterial(*bronze);
  pawn7->moveBack(1);
  pawn7->moveRight(6);
  pawn7->scaleLocal(0.1);
  pawn7->prepareVao();
  add("pawn7", pawn7);

    NormalsMesh* pawn8 = new NormalsMesh(context, shaderNorm, "models/pawn.obj", 0);
  pawn8->setMaterial(*bronze);
  pawn8->moveBack(1);
  pawn8->moveRight(7);
  pawn8->scaleLocal(0.1);
  pawn8->prepareVao();
  add("pawn8", pawn8);

  NormalsMesh* bpawn = new NormalsMesh(context, shaderNorm, "models/pawn.obj", 0);
  bpawn->setMaterial(*emerald);
  bpawn->moveBack(6);
  bpawn->scaleLocal(0.1);
  bpawn->prepareVao();
  add("bpawn", bpawn);

  NormalsMesh* bpawn2 = new NormalsMesh(context, shaderNorm, "models/pawn.obj", 0);
  bpawn2->setMaterial(*emerald);
  bpawn2->moveBack(6);
  bpawn2->moveRight(1);
  bpawn2->scaleLocal(0.1);
  bpawn2->prepareVao();
  add("bpawn2", bpawn2);

    NormalsMesh* bpawn3 = new NormalsMesh(context, shaderNorm, "models/pawn.obj", 0);
  bpawn3->setMaterial(*emerald);
  bpawn3->moveBack(6);
  bpawn3->moveRight(2);
  bpawn3->scaleLocal(0.1);
  bpawn3->prepareVao();
  add("bpawn3", bpawn3);

    NormalsMesh* bpawn4 = new NormalsMesh(context, shaderNorm, "models/pawn.obj", 0);
  bpawn4->setMaterial(*emerald);
  bpawn4->moveBack(6);
  bpawn4->moveRight(3);
  bpawn4->scaleLocal(0.1);
  bpawn4->prepareVao();
  add("bpawn4", bpawn4);

    NormalsMesh* bpawn5 = new NormalsMesh(context, shaderNorm, "models/pawn.obj", 0);
  bpawn5->setMaterial(*emerald);
  bpawn5->moveBack(6);
  bpawn5->moveRight(4);
  bpawn5->scaleLocal(0.1);
  bpawn5->prepareVao();
  add("bpawn5", bpawn5);

    NormalsMesh* bpawn6 = new NormalsMesh(context, shaderNorm, "models/pawn.obj", 0);
  bpawn6->setMaterial(*emerald);
  bpawn6->moveBack(6);
  bpawn6->moveRight(5);
  bpawn6->scaleLocal(0.1);
  bpawn6->prepareVao();
  add("bpawn6", bpawn6);

    NormalsMesh* bpawn7 = new NormalsMesh(context, shaderNorm, "models/pawn.obj", 0);
  bpawn7->setMaterial(*emerald);
  bpawn7->moveBack(6);
  bpawn7->moveRight(6);
  bpawn7->scaleLocal(0.1);
  bpawn7->prepareVao();
  add("bpawn7", bpawn7);

    NormalsMesh* bpawn8 = new NormalsMesh(context, shaderNorm, "models/pawn.obj", 0);
  bpawn8->setMaterial(*emerald);
  bpawn8->moveBack(6);
  bpawn8->moveRight(7);
  bpawn8->scaleLocal(0.1);
  bpawn8->prepareVao();
  add("bpawn8", bpawn8);

  NormalsMesh* bishop = new NormalsMesh(context, shaderNorm, "models/bishop.obj", 0);
  bishop->setMaterial(*bronze);
  bishop->moveRight(2);
  bishop->scaleLocal(0.1);
  bishop->prepareVao();
  add("bishop", bishop);

  NormalsMesh* bishop2 = new NormalsMesh(context, shaderNorm, "models/bishop.obj", 0);
  bishop2->setMaterial(*bronze);
  bishop2->moveRight(5);
  bishop2->scaleLocal(0.1);
  bishop2->prepareVao();
  add("bishop2", bishop2);

  NormalsMesh* bbishop2 = new NormalsMesh(context, shaderNorm, "models/bishop.obj", 0);
  bbishop2->setMaterial(*emerald);
  bbishop2->moveRight(5);
  bbishop2->moveBack(7);
  bbishop2->scaleLocal(0.1);
  bbishop2->prepareVao();
  add("bbishop2", bbishop2);

  NormalsMesh* bbishop = new NormalsMesh(context, shaderNorm, "models/bishop.obj", 0);
  bbishop->setMaterial(*emerald);
  bbishop->moveRight(2);
  bbishop->moveBack(7);
  bbishop->scaleLocal(0.1);
  bbishop->prepareVao();
  add("bbishop", bbishop);

  NormalsMesh* king = new NormalsMesh(context, shaderNorm, "models/king.obj", 0);
  king->setMaterial(*bronze);
  king->moveRight(3);
  king->scaleLocal(0.1);
  king->prepareVao();
  add("king", king);

  NormalsMesh* bking = new NormalsMesh(context, shaderNorm, "models/king.obj", 0);
  bking->setMaterial(*emerald);
  bking->moveRight(3);
  bking->moveBack(7);
  bking->scaleLocal(0.1);
  bking->prepareVao();
  add("bking", bking);

  NormalsMesh* knight = new NormalsMesh(context, shaderNorm, "models/knight.obj", 0);
  knight->setMaterial(*bronze);
  knight->moveRight(1);
  knight->scaleLocal(.2);
  knight->prepareVao();
  add("knight", knight);

  NormalsMesh* knight2 = new NormalsMesh(context, shaderNorm, "models/knight.obj", 0);
  knight2->setMaterial(*bronze);
  knight2->moveRight(6);
  knight2->scaleLocal(.2);
  knight2->prepareVao();
  add("knight2", knight2);

  NormalsMesh* bknight2 = new NormalsMesh(context, shaderNorm, "models/knight.obj", 0);
  bknight2->setMaterial(*emerald);
  bknight2->moveRight(6);
  bknight2->moveBack(7);
  bknight2->scaleLocal(.2);
  bknight2->rotateLocal(180, Vector3(0,1,0));
  bknight2->prepareVao();
  add("bknight2", bknight2);

   NormalsMesh* bknight1 = new NormalsMesh(context, shaderNorm, "models/knight.obj", 0);
  bknight1->setMaterial(*emerald);
  bknight1->moveRight(1);
  bknight1->moveBack(7);
  bknight1->scaleLocal(.2);
  bknight1->rotateLocal(180, Vector3(0,1,0));
  bknight1->prepareVao();
  add("bknight1", bknight1);


/*
  NormalsMesh* chess = new NormalsMesh(context, shaderNorm, "models/model.obj", 0);
  chess->prepareVao();
  add("chess", chess);

  NormalsMesh* chess1 = new NormalsMesh(context, shaderNorm, "models/model.obj", 1);
  chess1->prepareVao();
  add("chess1", chess1);

  NormalsMesh* board = new NormalsMesh(context, shaderNorm, "models/Board.obj", 0);
  board->prepareVao();
  add("board", board);
*/
/*
  NormalsMesh* bear1 = new NormalsMesh(context, shaderNorm, "models/bear.obj", 1);
  bear1->moveRight(14.0);
  bear1->moveUp(-10.0);
  bear1->prepareVao();
  add("bear1", bear1);

  NormalsMesh* bear2 = new NormalsMesh(context, shaderNorm, "models/bear.obj", 2);
  bear2->moveRight(14.0);
  bear2->moveUp(-10.0);
  bear2->prepareVao();
  add("bear2", bear2);
*/
};