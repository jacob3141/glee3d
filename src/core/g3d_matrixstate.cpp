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
#include "g3d_matrixstate.h"

namespace Glee3D {

    MatrixState::MatrixState(int behaviour)
        : _modelviewMatrix(),
          _projectionMatrix(),
          _textureMatrix(),
          _colorMatrix() {
        _behaviour = behaviour;
        if(_behaviour & AutomaticSave) {
            save();
        }
    }

    MatrixState::MatrixState(const MatrixState &other) {
        _modelviewMatrix    = other._modelviewMatrix;
        _projectionMatrix   = other._projectionMatrix;
        _textureMatrix      = other._textureMatrix;
        _colorMatrix        = other._colorMatrix;
        _behaviour          = other._behaviour;
    }

    MatrixState::~MatrixState() {
        if(_behaviour & AutomaticRestore) {
            restore();
        }
    }

    void MatrixState::save(int dataType) {
        if(dataType & Modelview) {
            glGetDoublev(GL_MODELVIEW_MATRIX, _modelviewMatrix.glDataPointer());
        }

        if(dataType & Projection) {
            glGetDoublev(GL_PROJECTION_MATRIX, _projectionMatrix.glDataPointer());
        }

        if(dataType & Texture) {
            glGetDoublev(GL_TEXTURE_MATRIX, _textureMatrix.glDataPointer());
        }

        if(dataType & Color) {
            glGetDoublev(GL_COLOR_MATRIX, _colorMatrix.glDataPointer());
        }

        if(dataType & Mode) {
            glGetIntegerv(GL_MATRIX_MODE, &_matrixMode);
        }
    }

    void MatrixState::restore(int dataType) {
        GLint previousMatrixMode;
        glGetIntegerv(GL_MATRIX_MODE, &previousMatrixMode);

        if(dataType & Modelview) {
            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixd(_modelviewMatrix.glDataPointer());
        }

        if(dataType & Projection) {
            glMatrixMode(GL_PROJECTION);
            glLoadMatrixd(_projectionMatrix.glDataPointer());
        }

        if(dataType & Texture) {
            glMatrixMode(GL_TEXTURE);
            glLoadMatrixd(_textureMatrix.glDataPointer());
        }

        if(dataType & Color) {
            glMatrixMode(GL_COLOR);
            glLoadMatrixd(_colorMatrix.glDataPointer());
        }

        if(dataType & Mode) {
            glMatrixMode(_matrixMode);
        } else {
            glMatrixMode(previousMatrixMode);
        }
    }

    void MatrixState::setModelviewMatrix(Matrix4x4 matrix) {
        _modelviewMatrix = matrix;
    }

    void MatrixState::setProjectionMatrix(Matrix4x4 matrix) {
        _projectionMatrix = matrix;
    }

    void MatrixState::setTextureMatrix(Matrix4x4 matrix) {
        _textureMatrix = matrix;
    }

    void MatrixState::setColorMatrix(Matrix4x4 matrix) {
        _colorMatrix = matrix;
    }

    void MatrixState::setMatrixMode(GLint mode) {
        _matrixMode = mode;
    }

    Matrix4x4 MatrixState::modelviewMatrix() {
        return _modelviewMatrix;
    }

    Matrix4x4 MatrixState::projectionMatrix() {
        return _projectionMatrix;
    }

    Matrix4x4 MatrixState::textureMatrix() {
        return _textureMatrix;
    }

    Matrix4x4 MatrixState::colorMatrix() {
        return _colorMatrix;
    }

    GLint MatrixState::matrixMode() {
        return _matrixMode;
    }

} // namespace Glee3D
