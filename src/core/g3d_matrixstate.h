///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of glee3d.                                           //
//    Copyright (C) 2012-2014 Jacob Dawid, jacob.dawid@cybercatalyst.net     //
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

#ifndef G3D_MATRIXSTATE_H
#define G3D_MATRIXSTATE_H

// Own includes
#include "math/g3d_vector4d.h"

// Qt includes
#include <QGLWidget>

namespace Glee3D {

    struct Matrix {
        /**
         * @attention data is order column-wise, which can lead to confusion
         * when operating on this with OpenGL function, ie. index 0-3 represent
         * the first column, not the first row.
         */
        double _data[16];

        static Matrix identity() {
            Matrix m;
            // First column
            m._data[0]  = 1.0;
            m._data[1]  = 0.0;
            m._data[2]  = 0.0;
            m._data[3]  = 0.0;

            // Second column
            m._data[4]  = 0.0;
            m._data[5]  = 1.0;
            m._data[6]  = 0.0;
            m._data[7]  = 0.0;

            // Third column
            m._data[8]  = 0.0;
            m._data[9]  = 0.0;
            m._data[10] = 1.0;
            m._data[11] = 0.0;

            // Fourth column
            m._data[12] = 0.0;
            m._data[13] = 0.0;
            m._data[14] = 0.0;
            m._data[15] = 1.0;
            return m;
        }

        Matrix multiplicate(Matrix with) {
            Matrix result;
            int i, j;

            for(i = 0; i < 4; i++) {
                for(j = 0; j < 4; j++) {
                    result._data[i*4+j] =
                    _data[i*4+0]*with._data[0*4+j] +
                    _data[i*4+1]*with._data[1*4+j] +
                    _data[i*4+2]*with._data[2*4+j] +
                    _data[i*4+3]*with._data[3*4+j];
                 }
            }
            return result;
        }

        RealVector4D multiplicate(RealVector4D with) {
            RealVector4D result;

            result._x = with._x * _data[0] + with._y * _data[4] + with._z * _data[8] + with._w * _data[12];
            result._y = with._x * _data[1] + with._y * _data[5] + with._z * _data[9] + with._w * _data[13];
            result._z = with._x * _data[2] + with._y * _data[6] + with._z * _data[10] + with._w * _data[14];
            result._w = with._x * _data[3] + with._y * _data[7] + with._z * _data[11] + with._w * _data[15];

            return result;
        }

        bool invert(Matrix *result = 0) {
            double inverse[16], determinant;
            inverse[0] =  _data[5]*_data[10]*_data[15] - _data[5]*_data[11]*_data[14] - _data[9]*_data[6]*_data[15]
                     + _data[9]*_data[7]*_data[14] + _data[13]*_data[6]*_data[11] - _data[13]*_data[7]*_data[10];
            inverse[4] =  -_data[4]*_data[10]*_data[15] + _data[4]*_data[11]*_data[14] + _data[8]*_data[6]*_data[15]
                     - _data[8]*_data[7]*_data[14] - _data[12]*_data[6]*_data[11] + _data[12]*_data[7]*_data[10];
            inverse[8] =   _data[4]*_data[9]*_data[15] - _data[4]*_data[11]*_data[13] - _data[8]*_data[5]*_data[15]
                     + _data[8]*_data[7]*_data[13] + _data[12]*_data[5]*_data[11] - _data[12]*_data[7]*_data[9];
            inverse[12] = -_data[4]*_data[9]*_data[14] + _data[4]*_data[10]*_data[13] + _data[8]*_data[5]*_data[14]
                     - _data[8]*_data[6]*_data[13] - _data[12]*_data[5]*_data[10] + _data[12]*_data[6]*_data[9];
            inverse[1] =  -_data[1]*_data[10]*_data[15] + _data[1]*_data[11]*_data[14] + _data[9]*_data[2]*_data[15]
                     - _data[9]*_data[3]*_data[14] - _data[13]*_data[2]*_data[11] + _data[13]*_data[3]*_data[10];
            inverse[5] =   _data[0]*_data[10]*_data[15] - _data[0]*_data[11]*_data[14] - _data[8]*_data[2]*_data[15]
                     + _data[8]*_data[3]*_data[14] + _data[12]*_data[2]*_data[11] - _data[12]*_data[3]*_data[10];
            inverse[9] =  -_data[0]*_data[9]*_data[15] + _data[0]*_data[11]*_data[13] + _data[8]*_data[1]*_data[15]
                     - _data[8]*_data[3]*_data[13] - _data[12]*_data[1]*_data[11] + _data[12]*_data[3]*_data[9];
            inverse[13] =  _data[0]*_data[9]*_data[14] - _data[0]*_data[10]*_data[13] - _data[8]*_data[1]*_data[14]
                     + _data[8]*_data[2]*_data[13] + _data[12]*_data[1]*_data[10] - _data[12]*_data[2]*_data[9];
            inverse[2] =   _data[1]*_data[6]*_data[15] - _data[1]*_data[7]*_data[14] - _data[5]*_data[2]*_data[15]
                     + _data[5]*_data[3]*_data[14] + _data[13]*_data[2]*_data[7] - _data[13]*_data[3]*_data[6];
            inverse[6] =  -_data[0]*_data[6]*_data[15] + _data[0]*_data[7]*_data[14] + _data[4]*_data[2]*_data[15]
                     - _data[4]*_data[3]*_data[14] - _data[12]*_data[2]*_data[7] + _data[12]*_data[3]*_data[6];
            inverse[10] =  _data[0]*_data[5]*_data[15] - _data[0]*_data[7]*_data[13] - _data[4]*_data[1]*_data[15]
                     + _data[4]*_data[3]*_data[13] + _data[12]*_data[1]*_data[7] - _data[12]*_data[3]*_data[5];
            inverse[14] = -_data[0]*_data[5]*_data[14] + _data[0]*_data[6]*_data[13] + _data[4]*_data[1]*_data[14]
                     - _data[4]*_data[2]*_data[13] - _data[12]*_data[1]*_data[6] + _data[12]*_data[2]*_data[5];
            inverse[3] =  -_data[1]*_data[6]*_data[11] + _data[1]*_data[7]*_data[10] + _data[5]*_data[2]*_data[11]
                     - _data[5]*_data[3]*_data[10] - _data[9]*_data[2]*_data[7] + _data[9]*_data[3]*_data[6];
            inverse[7] =   _data[0]*_data[6]*_data[11] - _data[0]*_data[7]*_data[10] - _data[4]*_data[2]*_data[11]
                     + _data[4]*_data[3]*_data[10] + _data[8]*_data[2]*_data[7] - _data[8]*_data[3]*_data[6];
            inverse[11] = -_data[0]*_data[5]*_data[11] + _data[0]*_data[7]*_data[9] + _data[4]*_data[1]*_data[11]
                     - _data[4]*_data[3]*_data[9] - _data[8]*_data[1]*_data[7] + _data[8]*_data[3]*_data[5];
            inverse[15] =  _data[0]*_data[5]*_data[10] - _data[0]*_data[6]*_data[9] - _data[4]*_data[1]*_data[10]
                     + _data[4]*_data[2]*_data[9] + _data[8]*_data[1]*_data[6] - _data[8]*_data[2]*_data[5];

            determinant = _data[0] * inverse[0] + _data[1] * inverse[4] + _data[2] * inverse[8] + _data[3] * inverse[12];
            if(determinant == 0) {
                return false;
            }

            determinant = 1.0 / determinant;

            if(result) {
                for(int i = 0; i < 16; i++)
                    result->_data[i] = inverse[i] * determinant;
            }

            return true;
        }
    };

    /**
      * @class MatrixState
      * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
      * @date 02.12.2012
      * Helper class for saving and loading matrix states. The usual
      * calls to glPush and glPopMatrix are not portable and not very
      * flexible.
      */
    class MatrixState {
    public:
        /**
         * Describes the different data fields that can be backed up or
         * restored.
         */
        enum DataType {
            Modelview   = 1 << 0,
            Projection  = 1 << 1,
            Texture     = 1 << 2,
            Color       = 1 << 3,
            Mode        = 1 << 4
        };

        /**
         * Automatic save and restore behaviour options.
         */
        enum Behaviour {
            AutomaticSave       = 1 << 0,
            AutomaticRestore    = 1 << 1
        };

        /**
         * Creates a new matrix state.
         * @param behaviour Save and restore behaviour.
         */
        MatrixState(int behaviour = AutomaticSave);

        /** Copy constructor. */
        MatrixState(const MatrixState &other);

        /**
         * Destructor. If behaviour is AutomaticRestore, this will restore
         * the matrices to the saved state.
         */
        ~MatrixState();

        /** Saves the current GL matrix state. */
        void save(int dataType = Modelview | Projection | Texture | Color | Mode);

        /** Restores the current GL matrix state. */
        void restore(int dataType = Modelview | Projection | Texture | Color | Mode);

        void setModelviewMatrix(Matrix matrix);
        void setProjectionMatrix(Matrix matrix);
        void setTextureMatrix(Matrix matrix);
        void setColorMatrix(Matrix matrix);
        void setMatrixMode(GLint mode);

        Matrix modelviewMatrix();
        Matrix projectionMatrix();
        Matrix textureMatrix();
        Matrix colorMatrix();
        GLint  matrixMode();

    private:
        int _behaviour;

        Matrix _modelviewMatrix;
        Matrix _projectionMatrix;
        Matrix _textureMatrix;
        Matrix _colorMatrix;

        GLint _matrixMode;
    };

} // namespace Glee3D

#endif // G3D_MATRIXSTATE_H
