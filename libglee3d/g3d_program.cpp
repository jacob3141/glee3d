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

#include "g3d_program.h"
#include <QFile>
#include <iostream>
#include <QResource>

namespace Glee3D {

Program::Program() {
    _glProgram = 0;
    _glVertexShader = 0;
    _glFragmentShader = 0;
}

bool Program::compile(QString shaderSource, ShaderType shaderType) {
    if(!shaderSource.isEmpty()) {
        GLint success;
        GLchar buf[256];

        switch(shaderType) {
            case Vertex: {
                _vertexShaderSource = shaderSource;
                _glVertexShader = glCreateShader(GL_VERTEX_SHADER);
                const GLchar* shaderSourceArray[] = { _vertexShaderSource.toStdString().c_str() };
                glShaderSource(_glVertexShader, 1, shaderSourceArray, 0);
                glCompileShader(_glVertexShader);
                glGetShaderiv(_glVertexShader, GL_COMPILE_STATUS, &success);
                if(!success) {
                    glGetShaderInfoLog(_glVertexShader, sizeof(buf), 0, buf);
                    std::cout << "Error compiling vertex shader: " << buf << std::endl;
                    return false;
                } else {
                    std::cout << "Successfully compiled vertex shader." << std::endl;
                }
            } break;

            case Fragment: {
                _fragmentShaderSource = shaderSource;
                _glFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                const GLchar* shaderSourceArray[] = { _fragmentShaderSource.toStdString().c_str() };
                glShaderSource(_glFragmentShader, 1, shaderSourceArray, 0);
                glCompileShader(_glFragmentShader);
                glGetShaderiv(_glFragmentShader, GL_COMPILE_STATUS, &success);
                if(!success) {
                    glGetShaderInfoLog(_glFragmentShader, sizeof(buf), 0, buf);
                    std::cout << "Error compiling fragment shader: " << buf << std::endl;
                    return false;
                } else {
                    std::cout << "Successfully compiled fragment shader." << std::endl;
                }
            } break;
        }
    } else {
        return false;
    }
    return true;
}

bool Program::link() {
    GLint success;
    GLchar buf[256];
    _glProgram = glCreateProgram();
    if(_glVertexShader) {
        glAttachShader(_glProgram, _glVertexShader);
    }
    if(_glFragmentShader) {
        glAttachShader(_glProgram, _glFragmentShader);
    }
    glLinkProgram(_glProgram);
    glGetProgramiv(_glProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(_glProgram, sizeof(buf), 0, buf);
        std::cout << "Error linking shader program: " << buf << std::endl;
        return false;
    } else {
        std::cout << "Successfully linked shader program." << std::endl;
    }
    return true;
}

void Program::insert() {
    glUseProgram(_glProgram);
}

void Program::eject() {
    glUseProgram(0);
}

QString Program::vertexShaderSource() {
    return _vertexShaderSource;
}

QString Program::fragmentShaderSource() {
    return _fragmentShaderSource;
}

GLuint Program::glProgram() {
    return _glProgram;
}

GLuint Program::glVertexShader() {
    return _glVertexShader;
}

GLuint Program::glFragmentShader() {
    return _glFragmentShader;
}

GLint Program::glUniformLocation(QString name) {
    return glGetUniformLocation(_glProgram, (const GLchar*)name.toStdString().c_str());
}

} // namespace Glee3D
