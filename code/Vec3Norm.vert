#version 330

/*
  Filename: Vec3Norm.vert
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg
  Course: CSCI375
  Assignment: A08Model
  Description: A vertex shader that determines vertex color based on normals.
*/

/*********************************************************/
// Vertex attributes
// Incoming position attribute for each vertex
layout (location = 0) in vec3 aPosition;
// Incoming normal attribute for each vertex
layout (location = 2) in vec3 aNormal;

/*********************************************************/
// Uniforms are constant for all vertices from a single
//   draw call.
// Specify world and view transform for object.
//   This matrix should contain View * World. 
uniform mat4 uModelView;
// Specify projection
uniform mat4 uProjection;

// We are using a single directional light to illuminate our scene. 
// You can modify these parameters for your model.
// "uLightDirection" MUST point TOWARD the light source.
// As we are currently using this it is in *eye space*, which means that no
//   matter how the camera moves / rotates, the light will be coming from
//   behind the camera.  It would be more common to have light source
//   directions to remain unchanged while the camera moves.
uniform vec3 uLightDirection = vec3 (0, 0, 1); 
// Color of the light
uniform vec3 uLightIntensity = vec3 (0.5, 0.2, 0.1);

/*********************************************************/
// Vertex color we will output
out vec3 vColor;

void
main ()
{
  // Transform the vertex from world space to clip space
  gl_Position = uProjection * uModelView * vec4 (aPosition, 1.0);

  // The upper 3x3 portion of the model-view matrix is used for
  //   transforming normals. 
  mat3 normalMatrix = mat3 (uModelView);
  // We need the inverse transpose of the upper 3x3 matrix
  //   to transform normals to eye space. 
  normalMatrix = transpose (inverse (normalMatrix));
  // Transform local/model normal to eye space. 
  vec3 normalEye = normalize (normalMatrix * aNormal);
  // How directly is the light shining on the surface?
  float brightness = dot (normalEye, normalize (uLightDirection));
  // Ensure brightness is between 0 and 1
  brightness = clamp (brightness, 0, 1);

  vColor = brightness * uLightIntensity;
}
