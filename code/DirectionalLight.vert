#version 330

/*
  Filename: DirectionalLight.vert
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg
  Course: CSCI375
  Assignment: A09Project
  Description: A vertex shader that demonstrates how a scene could be lit with
    a single, hard-coded directional light source and all objects made of the
    same material.
  You can use shdr.bkcore.com to test vertex shaders and see what they do.
*/

// By default, all float variables will use high precision.
precision highp float;

// We should be getting a position (X,Y,Z) from the VBO.
attribute vec3 position;
// We should be getting a normal (X,Y,Z) from the VBO.
attribute vec3 normal;

// We should be getting a uniform matrix for converting normals to eye space.
uniform mat3 normalMatrix;
// We should be getting a uniform matrix for converting positions to eye space.
uniform mat4 modelViewMatrix;
// We should be getting a uniform matrix for converting eye to clip space.
uniform mat4 projectionMatrix;

// We are going to output a color (R,G,B) for later use in fragment shader.
varying vec3 vOutColor;

// Represents a directional light.
struct Light
{
  // The intensity of the ambient light in the scene (R,G,B).  This doesn't actually relate to the light source, but since we only have one we will put it here for convenience.
  vec3 ambient;
  // The diffuse intensity of the light source (R,G,B).
  vec3 diffuse;
  // The specular intensity of the light source (R,G,B).
  vec3 specular;
  // Points toward the light source (which is infinitely far away), should be normalized.
  vec3 direction;
};

// Create a single directional light for testing.
Light light = Light (vec3 (0.2, 0.1, 0.6),
                     vec3 (0.1, 0.5, 0.7),
		     vec3 (0.1, 0.5, 0.7),
		     vec3 (0, 0, 1));

// Represents the reflectance of a surface.
struct Material
{
  // These are reflectances
  vec3 ambientRefl;
  vec3 diffuseRefl;
  vec3 specularRefl;
  // Used in Phong lighting.
  float shininess;
};

// Create a single material for testing.
Material material = Material (vec3 (0.1, 0.1, 0.1),
        	              vec3 (0.75, 0.75, 0.8),
                 	      vec3 (0.75, 0.75, 0.8), 16.0);

void
main ()
{
  // Compute the vertex position, in eye space (used for lighting).
  vec4 positionEye = modelViewMatrix * vec4 (position, 1.0);
  // Compute the vertex position, in clip space (required output).
  gl_Position = projectionMatrix * positionEye;

  // Compute intensity of ambient light.
  vec3 ambientColor = light.ambient * material.ambientRefl;

  // Compute the vertex normal, in eye space.
  vec3 normalEye = normalize (normalMatrix * normal);
  // Compute now similar normal and light direction are.
  float diffuseCoeff = dot (normalEye, normalize (light.direction));
  // It will be negative if the light is shining on the back side.
  diffuseCoeff = max (diffuseCoeff, 0.0);
  // Compute intensity of diffuse light.
  vec3 diffuseColor = diffuseCoeff * light.diffuse * material.diffuseRefl;

  // If light is facing away from surface, no specular intensity at all.
  vec3 specularColor = vec3 (0.0);
  if (diffuseCoeff > 0.0)
  {
    // Reflect incidence vector wrt normal.
    vec3 reflection = reflect (-light.direction, normalEye);
    // Vector pointing toward the eye (0, 0, 0).
    vec3 viewDir = normalize (-positionEye.xyz);
    // Will be negative if eye is looking at the back side.
    float specularCoeff = max (dot (reflection, viewDir), 0.0);
    specularCoeff = pow (specularCoeff, material.shininess);
    // Compute intensity of specular light.
    specularColor = specularCoeff * light.specular * material.specularRefl;
  }

  // Compute complete intensity of light to send to fragment shader.
  vOutColor = ambientColor + diffuseColor + specularColor;
}
