varying vec3 v;
varying vec3 lightvec;
varying vec3 normal;
varying vec4 FrontColor;

void main(void) {
  normal         = normalize(gl_NormalMatrix * gl_Normal);
  v              = vec3(gl_ModelViewMatrix * gl_Vertex);
  lightvec       = normalize(gl_LightSource[0].position.xyz - v);

  gl_TexCoord[0] = gl_MultiTexCoord0;
  FrontColor     = gl_Color;

  gl_Position    = gl_ModelViewProjectionMatrix * gl_Vertex;
}
