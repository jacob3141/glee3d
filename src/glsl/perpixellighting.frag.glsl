varying vec3 v;
varying vec3 lightvec;
varying vec3 normal;
varying vec4 FrontColor;

uniform sampler2D Texture0;

void main(void) {
  vec3 Eye       = normalize(-v);
  vec3 Reflected = normalize(reflect( -lightvec, normal));

  vec4 IAmbient  = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;
  vec4 IDiffuse  = gl_LightSource[0].diffuse * max(dot(normal, lightvec), 0.0) * gl_FrontMaterial.diffuse;
  vec4 ISpecular = gl_LightSource[0].specular * pow(max(dot(Reflected, Eye), 0.0), gl_FrontMaterial.shininess) * gl_FrontMaterial.specular;

  gl_FragColor   = vec4((gl_FrontLightModelProduct.sceneColor + IAmbient + IDiffuse) * texture2D(Texture0, vec2(gl_TexCoord[0])) + ISpecular);
}
