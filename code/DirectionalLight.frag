#version 330

/*
  Filename: DirectionalLight.frag
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg
  Course: CSCI375
  Assignment: A09Project
  Description: A fragment shader that assumes that all lighting calculations
    were done in the vertex shader, and just adds an alpha component.
  You can use shdr.bkcore.com to test the pair of shaders and see what they do.
*/

// By default, all float variables will use high precision.
precision highp float;

// Unused
uniform float time;
uniform vec2 resolution;

// We should be getting a color (R,G,B) from the vertex shader.
varying vec3 vOutColor;

void
main()
{
  // Just use the result calculated by the vertex shader and interpolated to this fragment.
  gl_FragColor = vec4 (vOutColor, 1.0);
}
