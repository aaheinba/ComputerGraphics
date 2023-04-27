#version 330

precision highp float;

uniform int uNumLights;

struct Light
{
  // 0 if directional, 1 if point, 2 if spot -- other values illegal.
  int type;

  // All lights have these parameters.
  vec3 diffuseIntensity;
  vec3 specularIntensity;

  // Point and spot light parameters.
  vec3 position;
  vec3 attenuationCoefficients;

  // Directional and spot light parameter.
  vec3 direction;

  // Spot light parameters.
  float cutoffCosAngle;
  float falloff;
};

const int MAX_LIGHTS = 8;
uniform Light uLights[MAX_LIGHTS];

uniform vec3  uAmbientIntensity; 

uniform vec3  uAmbientReflection; 
uniform vec3  uDiffuseReflection; 
uniform vec3  uSpecularReflection; 
uniform float uSpecularPower; 
uniform vec3  uEmissiveIntensity; 

uniform vec3 uEyePosition;

uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uWorld;

out vec4 fColor;
in vec3 vNormal;
in vec3 vPosition;



vec3
calculateLighting (Light light, vec3 vertexPosition, vec3 vertexNormal);



void
main (void)
{

    vec3 nColor = uAmbientReflection * uAmbientIntensity + uEmissiveIntensity;


    for (int i = 0; i < uNumLights; ++i)
    {
        nColor += calculateLighting (uLights[i], vPosition, vNormal);
    }
    
    // Stay in bounds [0, 1]
    nColor = clamp (nColor, 0.0, 1.0);
    fColor = vec4 (nColor, 1.0);
}



vec3
calculateLighting (Light light, vec3 vertexPosition, vec3 vertexNormal)
{
  // Light vector points toward the light
  vec3 lightVector;
  if (light.type == 0)
  { // Directional
    mat3 normaluViewInv = mat3 (uView);
    normaluViewInv = transpose (inverse (normaluViewInv));

    //remove next two lines if fail
    //mat3 normalTransform = mat3 (uWorld);
    //normalTransform = transpose (inverse (normalTransform));
 

    //new line remove to restore
    //lightVector = normalize (normaluViewInv * normalize (normalTransform * -light.direction));

    //old line keep and uncomment to restore
    lightVector = normalize (normaluViewInv * -light.direction);
  }
  else
  { // Point or spot
    //restore
    lightVector = normalize ((mat3 (uView) * light.position) - vertexPosition);
        //change attempt
        //lightVector = normalize (light.position - vertexPosition);

  }
  // Light intensity is proportional to angle between light vector
  //   and vertex normal
  float lambertianCoef = max (dot (lightVector, vertexNormal), 0.0);
  vec3 diffuseAndSpecular = vec3 (0.0);
  if (lambertianCoef > 0.0)
  {
    // Light is incident on vertex, not shining on its edge or back
    vec3 diffuseColor = uDiffuseReflection * light.diffuseIntensity;
    diffuseColor *= lambertianCoef;

    vec3 specularColor = uSpecularReflection * light.specularIntensity;
    // See how light reflects off of vertex
    vec3 reflectionVector = reflect (-lightVector, vertexNormal);
    // Compute view vector, which points toward the eye
    vec3 eyeVector = normalize (uEyePosition - vertexPosition);
    // Light intensity is proportional to angle between reflection vector
    //   and eye vector
    float specularCoef = max (dot (eyeVector, reflectionVector), 0.0);
    // Material's specular power determines size of bright spots
    specularColor *= pow (specularCoef, uSpecularPower);

    float attenuation = 1.0;
    if (light.type != 0)
    { // Non-directional, so light attenuates
      float distance = length (vec4 (vertexPosition, 1) - (uView * vec4 (light.position, 1)));
      attenuation = 1.0 / (light.attenuationCoefficients.x
          + light.attenuationCoefficients.y * distance
          + light.attenuationCoefficients.z * distance * distance);
    }
    float spotFactor = 1.0f;
    if (light.type == 2)
    { // Spot light
      mat3 normaluViewInv = mat3 (uView);
      normaluViewInv = transpose (inverse (normaluViewInv));

  mat3 normalTransform = mat3 (uWorld);
  normalTransform = transpose (inverse (normalTransform));


      //restore value
      float cosTheta = dot (-lightVector, (normaluViewInv * light.direction));
       //change
       //float cosTheta = dot (-lightVector, light.direction);
      cosTheta = max (cosTheta, 0.0f);
      spotFactor = (cosTheta >= light.cutoffCosAngle) ? cosTheta : 0.0f;
      spotFactor = pow (spotFactor, light.falloff);
    }
    diffuseAndSpecular = spotFactor * attenuation * (diffuseColor
        + specularColor);
  }

  return diffuseAndSpecular;
}