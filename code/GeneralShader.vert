#version 330

/*
  Filename: GeneralShader.vert
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg
  Course: CSCI375
  Assignment: A09Project
  Description: A vertex shader that demonstrates how up to 8 light sources of a
    variety of types could be provided.
*/

// By default, all float variables will use high precision.
precision highp float;

// Inputs from the VBO.

in vec3 aPosition;
layout(location = 2) in vec3 aNormal;

// Output to the fragment shader.

out vec3 vNormal;
out vec3 vPosition;

// Transformation matrices, provided by C++ code.

uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uWorld;

void
main (void)
{
  mat4 worldViewProjection = uProjection * uView * uWorld;
  // Transform vertex into clip space
  gl_Position = worldViewProjection * vec4 (aPosition, 1);
  // Transform vertex into world space for lighting
  
  //old uncomment to restore
  vec3 positionEye = vec3 (uView * (uWorld * vec4 (aPosition, 1)));
  
  //new delete to restore
  //vec3 positionEye = vec3 (inverse(uView) * (uWorld * vec4 (aPosition, 1)));
  
  vPosition = positionEye;


  
  // We're doing lighting in world space for this example!
  mat3 normalTransform = mat3 (uWorld);
  normalTransform = transpose (inverse (normalTransform));
  mat3 normaluViewInv = mat3 (uView);
  
  //old line uncomment to restore
  normaluViewInv = transpose (inverse (normaluViewInv));

//new line delete to restore
  //normaluViewInv = inverse (normaluViewInv);

  // Normal matrix is world inverse transpose



  
 
  vec3 normalWorld = normalize (normaluViewInv * normalize (normalTransform * aNormal));
  vNormal = normalWorld;
  
}

