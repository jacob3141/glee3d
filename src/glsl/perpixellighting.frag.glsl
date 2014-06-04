///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of glee3d.                                           //
//    Copyright (C) 2012 Jacob Dawid, jacob.dawid@cybercatalyst.net          //
//                                                                           //
//    glee3d is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by   //
//    the Free Software Foundation, either version 3 of the License, or      //
//    (at your option) any later version.                                    //
//                                                                           //
//    glee3d is distributed in the hope that it will be useful,              //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of         //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                           //
//                                                                           //
//    You should have received a copy of the GNU General Public License      //
//    along with glee3d.  If not, see <http://www.gnu.org/licenses/>.        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

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
