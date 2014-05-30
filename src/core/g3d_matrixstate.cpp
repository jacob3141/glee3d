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
#include "g3d_matrixstate.h"

// Qt includes
#include <QGLWidget>

namespace Glee3D {

    MatrixState::MatrixState()
        : _modelviewMatrix(),
          _projectionMatrix(),
          _textureMatrix(),
          _colorMatrix() {
    }

    MatrixState::MatrixState(const MatrixState &other) {
        _modelviewMatrix    = other._modelviewMatrix;
        _projectionMatrix   = other._projectionMatrix;
        _textureMatrix      = other._textureMatrix;
        _colorMatrix        = other._colorMatrix;
    }

    MatrixState::~MatrixState() {
    }

    void MatrixState::save(int matrixType) {
        if(matrixType & Modelview) {
            glGetDoublev(GL_MODELVIEW_MATRIX, _modelviewMatrix._data);
        }

        if(matrixType & Projection) {
            glGetDoublev(GL_PROJECTION_MATRIX, _projectionMatrix._data);
        }

        if(matrixType & Texture) {
            glGetDoublev(GL_TEXTURE_MATRIX, _textureMatrix._data);
        }

        if(matrixType & Color) {
            glGetDoublev(GL_COLOR_MATRIX, _colorMatrix._data);
        }
    }

    void MatrixState::load(int matrixType) {
        GLint matrixMode;
        glGetIntegerv(GL_MATRIX_MODE, &matrixMode);

        if(matrixType & Modelview) {
            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixd(_modelviewMatrix._data);
        }

        if(matrixType & Projection) {
            glMatrixMode(GL_PROJECTION);
            glLoadMatrixd(_projectionMatrix._data);
        }

        if(matrixType & Texture) {
            glMatrixMode(GL_TEXTURE);
            glLoadMatrixd(_textureMatrix._data);
        }

        if(matrixType & Color) {
            glMatrixMode(GL_COLOR);
            glLoadMatrixd(_colorMatrix._data);
        }

        glMatrixMode(matrixMode);
    }

    void MatrixState::setModelviewMatrix(Matrix matrix) {
        _modelviewMatrix = matrix;
    }

    void MatrixState::setProjectionMatrix(Matrix matrix) {
        _projectionMatrix = matrix;
    }

    void MatrixState::setTextureMatrix(Matrix matrix) {
        _textureMatrix = matrix;
    }

    void MatrixState::setColorMatrix(Matrix matrix) {
        _colorMatrix = matrix;
    }

    Matrix MatrixState::modelviewMatrix() {
        return _modelviewMatrix;
    }

    Matrix MatrixState::projectionMatrix() {
        return _projectionMatrix;
    }

    Matrix MatrixState::textureMatrix() {
        return _textureMatrix;
    }

    Matrix MatrixState::colorMatrix() {
        return _colorMatrix;
    }

} // namespace Glee3D
