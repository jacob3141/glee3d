///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of glee3d.                                           //
//    Copyright (C) 2012-2015 Jacob Dawid, jacob.dawid@omg-it.works          //
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

#ifndef G3D_PROGRAM_H
#define G3D_PROGRAM_H

// GL extension wrangler includes
#include "GL/glew.h"

// OpenGL includes
#include "GL/glext.h"

// Own includes
#include "g3d_logging.h"

// Qt includes
#include <QString>

#define GLSL(code) #code

namespace Glee3D {
/**
  * @class Program
  * @author Jacob Dawid (jacob.dawid@omg-it.works)
  * @date 02.12.2012
  * This class provides a simple interface for programming shaders
  * with the GL shading language (GLSL). Different types of shaders
  * can be rewritten, compiled and linked into a program.
  */
class Program : public Logging {
public:
    /** @enum ShaderType */
    enum ShaderType {
        Vertex,
        Fragment
    };

    /** Creates a new shading program. */
    Program();

    bool build(QString vertexShaderFileName, QString fragmentShaderFileName);

    /**
      * Compiles the given source code written in GLSL for the
      * given shader type.
      * @param shaderSource Source code for the shader in GLSL.
      * @param shaderType Target shader.
      * @returns true, if compilation succeded.
      */
    bool compile(QString shaderSource, ShaderType shaderType);

    /**
      * Links all compiled shaders to a program.
      * @returns true, if linking succeded.
      */
    bool link();

    /**
      * Inserts the program making it the active program.
      */
    void insert();

    /**
      * Ejects the program, leaving the default program.
      */
    void eject();

    /** @returns the current vertex shader source. */
    QString vertexShaderSource();

    /** @returns the current fragment shader source. */
    QString fragmentShaderSource();

    /** @returns the OpenGL program handle. */
    GLhandleARB glProgram();

    /** @returns the OpenGL vertex shader handle. */
    GLhandleARB glVertexShader();

    /** @returns the OpenGL fragment shader handle. */
    GLhandleARB glFragmentShader();

    /** @returns the OpenGL variable location for the given name. */
    GLhandleARB glUniformLocation(QString name);

private:
    GLhandleARB _glProgram;
    GLhandleARB _glVertexShader;
    GLhandleARB _glFragmentShader;

    QString _vertexShaderSource;
    QString _fragmentShaderSource;
};

} // namespace Glee3D

#endif // G3D_PROGRAM_H
