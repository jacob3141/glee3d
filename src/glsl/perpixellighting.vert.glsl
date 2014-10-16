///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of glee3d.                                           //
//    Copyright (C) 2012 Jacob Dawid, jacob.dawid@omg-it.works          //
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

void main(void) {
    normal         = normalize(gl_NormalMatrix * gl_Normal);
    v              = vec3(gl_ModelViewMatrix * gl_Vertex);
    lightvec       = normalize(gl_LightSource[0].position.xyz - v);

    gl_TexCoord[0] = gl_MultiTexCoord0;
    FrontColor     = gl_Color;

    gl_Position    = gl_ModelViewProjectionMatrix * gl_Vertex;
}
