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

// Own includes
#include "g3d_program.h"

// Qt includes
#include <QFile>
#include <QResource>

// Standard includes
#include <iostream>

namespace Glee3D {

Program::Program()
    : Logging("Program") {
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
            error("Failed to compile vertex shader.");
            return false;
        }

        vertexShaderFile.close();
    } else {
        error("Failed to open vertex shader file.");
        return false;
    }

    fragmentShaderFile.open(QFile::ReadOnly);
    if(fragmentShaderFile.isOpen()) {
        if(!compile(fragmentShaderFile.readAll(), Fragment)) {
            error("Failed to compile fragment shader.");
            return false;
        }

        fragmentShaderFile.close();
    } else {
        error("Failed to open fragment shader file.");
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
        GLchar errorInfo[2048];

        switch(shaderType) {
            case Vertex: {
                _vertexShaderSource = shaderSource;
                _glVertexShader = glCreateShaderObjectARB(GL_VERTEX_SHADER);

                QByteArray programBytes = _vertexShaderSource.toUtf8();
                const GLint programSize = (const GLint)programBytes.size();
                const GLcharARB* programData =  (const GLcharARB*)programBytes.data();

                glShaderSource(_glVertexShader, 1, &programData, &programSize);
                glCompileShader(_glVertexShader);
                glGetShaderiv(_glVertexShader, GL_COMPILE_STATUS, &success);
                if(!success) {
                    glGetShaderInfoLog(_glVertexShader, sizeof(errorInfo), 0, errorInfo);
                    error(errorInfo);
                    return false;
                }
            } break;

            case Fragment: {
                _fragmentShaderSource = shaderSource;
                _glFragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);

                QByteArray programBytes = _fragmentShaderSource.toUtf8();
                const GLint programSize = (const GLint)programBytes.size();
                const GLcharARB* programData =  (const GLcharARB*)programBytes.data();

                glShaderSource(_glFragmentShader, 1, &programData, &programSize);
                glCompileShader(_glFragmentShader);
                glGetShaderiv(_glFragmentShader, GL_COMPILE_STATUS, &success);
                if(!success) {
                    glGetShaderInfoLog(_glFragmentShader, sizeof(errorInfo), 0, errorInfo);
                    error(errorInfo);
                    return false;
                }
            } break;
        }
    } else {
        warning("Warning: No shader source provided for compilation.");
        return false;
    }

    information("Successfully compiled shader source.");
    return true;
}

bool Program::link() {
    GLint success;
    GLchar errorInfo[256];
    _glProgram = glCreateProgramObjectARB();

    // REVIEW: Does a values >= 0 really mean the shader is valid? Probably be
    // more verbose on that here.
    if(_glVertexShader) {
        glAttachObjectARB(_glProgram, _glVertexShader);
    }
    if(_glFragmentShader) {
        glAttachObjectARB(_glProgram, _glFragmentShader);
    }
    glLinkProgram(_glProgram);
    glGetProgramiv(_glProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(_glProgram, sizeof(errorInfo), 0, errorInfo);
        error(errorInfo);
        return false;
    }
    information("Successfully linked shader program.");
    return true;
}

void Program::insert() {
    glUseProgram(_glProgram);
    _projectionMatrixUniformLocation = glUniformLocation("g3d_ProjectionMatrix");
    _modelViewMatrixUniformLocation = glUniformLocation("g3d_ModelViewMatrix");
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

int Program::glProgram() {
    return _glProgram;
}

int Program::glVertexShader() {
    return _glVertexShader;
}

int Program::glFragmentShader() {
    return _glFragmentShader;
}

int Program::glUniformLocation(QString name) {
    return glGetUniformLocation(_glProgram, (const GLchar*)name.toStdString().c_str());
}

void Program::setModelViewMatrix(Matrix4x4 modelViewMatrix) {
    glUniformMatrix4fv(_modelViewMatrixUniformLocation, 1, GL_FALSE, modelViewMatrix.asGlFloatPointer());
}

void Program::setProjectionMatrix(Matrix4x4 projectionMatrix) {
    glUniformMatrix4fv(_projectionMatrixUniformLocation, 1, GL_FALSE, projectionMatrix.asGlFloatPointer());
}

} // namespace Glee3D
