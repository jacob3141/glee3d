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

#ifndef G3D_MATRIXSTATE_H
#define G3D_MATRIXSTATE_H

// Qt includes
#include <QGLWidget>

namespace Glee3D {

    struct Matrix {
        double _data[16];
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
