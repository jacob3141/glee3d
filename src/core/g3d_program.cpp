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

// Own includes
#include "g3d_program.h"

// Qt includes
#include <QFile>
#include <QResource>

// Standard includes
#include <iostream>

namespace Glee3D {

Program::Program() {
    _glProgram = 0;
    _glVertexShader = 0;
    _glFragmentShader = 0;
}

bool Program::build(QString vertexShaderFileName, QString fragmentShaderFileName) {
    QFile vertexShaderFile, fragmentShaderFile;
    vertexShaderFile.setFileName(vertexShaderFileName);
    fragmentShaderFile.setFileName(fragmentShaderFileName);

    vertexShaderFile.open(QFile::ReadOnly);
    if(vertexShaderFile.isOpen()) {
        if(!compile(vertexShaderFile.readAll(), Vertex)) {
            return false;
        }

        vertexShaderFile.close();
    } else {
        return false;
    }

    fragmentShaderFile.open(QFile::ReadOnly);
    if(fragmentShaderFile.isOpen()) {
        if(!compile(fragmentShaderFile.readAll(), Fragment)) {
            return false;
        }

        fragmentShaderFile.close();
    } else {
        return false;
    }

    if(!link()) {
        return false;
    }
    return true;
}

bool Program::compile(QString shaderSource, ShaderType shaderType) {
    if(!shaderSource.isEmpty()) {
        GLint success;
        GLchar buf[2048];

        switch(shaderType) {
            case Vertex: {
                _vertexShaderSource = shaderSource;
                _glVertexShader = glCreateShaderObjectARB(GL_VERTEX_SHADER);

                QByteArray programBytes = _vertexShaderSource.toUtf8();
                const GLint programSize = (const GLint)programBytes.size();
                const GLcharARB* programData =  (const GLcharARB*)programBytes.data();

                glShaderSourceARB(_glVertexShader, 1, &programData, &programSize);
                glCompileShaderARB(_glVertexShader);
                glGetShaderiv(_glVertexShader, GL_COMPILE_STATUS, &success);
                if(!success) {
                    glGetShaderInfoLog(_glVertexShader, sizeof(buf), 0, buf);
                    std::cout << "Error compiling vertex shader: " << buf << std::endl;
                    return false;
                }
            } break;

            case Fragment: {
                _fragmentShaderSource = shaderSource;
                _glFragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);

                QByteArray programBytes = _fragmentShaderSource.toUtf8();
                const GLint programSize = (const GLint)programBytes.size();
                const GLcharARB* programData =  (const GLcharARB*)programBytes.data();

                glShaderSourceARB(_glFragmentShader, 1, &programData, &programSize);
                glCompileShaderARB(_glFragmentShader);
                glGetShaderiv(_glFragmentShader, GL_COMPILE_STATUS, &success);
                if(!success) {
                    glGetShaderInfoLog(_glFragmentShader, sizeof(buf), 0, buf);
                    std::cout << "Error compiling fragment shader: " << buf << std::endl;
                    return false;
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
    _glProgram = glCreateProgramObjectARB();
    if(_glVertexShader) {
        glAttachObjectARB(_glProgram, _glVertexShader);
    }
    if(_glFragmentShader) {
        glAttachObjectARB(_glProgram, _glFragmentShader);
    }
    glLinkProgramARB(_glProgram);
    glGetProgramiv(_glProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(_glProgram, sizeof(buf), 0, buf);
        std::cout << "Error linking shader program: " << buf << std::endl;
        return false;
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

GLhandleARB Program::glProgram() {
    return _glProgram;
}

GLhandleARB Program::glVertexShader() {
    return _glVertexShader;
}

GLhandleARB Program::glFragmentShader() {
    return _glFragmentShader;
}

GLhandleARB Program::glUniformLocation(QString name) {
    return glGetUniformLocation(_glProgram, (const GLchar*)name.toStdString().c_str());
}

} // namespace Glee3D
