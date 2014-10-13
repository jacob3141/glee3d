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

#ifndef G3D_UTILITIES_H
#define G3D_UTILITIES_H

// Own includes
#include "math/g3d_vector3d.h"
#include "math/g3d_vector4d.h"
#include "core/g3d_matrixstate.h"

// Qt includes
#include <QGLWidget>

namespace Glee3D {

/**
 * Utility class.
 */
class Utilities {
public:
    /**
     * Reimplementation of gluPerspective.
     * @param fieldOfView
     * @param aspectRatio
     * @param near
     * @param far
     */
    static void perspective(
        double fieldOfView,
        double aspectRatio,
        double near,
        double far) {

        double xmin, xmax, ymin, ymax;
        ymax = near * tan(fieldOfView * M_PI / 360.0);
        ymin = -ymax;
        xmin = ymin * aspectRatio;
        xmax = ymax * aspectRatio;

        glFrustum(xmin, xmax, ymin, ymax, near, far);
    }

    /**
     * Reimplementation of gluLookAt.
     * @param eye
     * @param center
     * @param up
     */
    static void lookAt(
        RealVector3D eye,
        RealVector3D center,
        RealVector3D up) {

        RealVector3D forward = center - eye;
        forward.normalize();
        RealVector3D side = forward.crossProduct(up);
        side.normalize();
        up = side.crossProduct(forward);

        Matrix matrix = Matrix::identity();

        matrix._data[0]  = side._x;
        matrix._data[4]  = side._y;
        matrix._data[8]  = side._z;

        matrix._data[1]  = up._x;
        matrix._data[5]  = up._y;
        matrix._data[9]  = up._z;

        matrix._data[2]  = -forward._x;
        matrix._data[6]  = -forward._y;
        matrix._data[10] = -forward._z;

        glMultMatrixd(&matrix._data[0]);
        glTranslated(-eye._x, -eye._y, -eye._z);
    }

    static bool unproject(
        RealVector3D window,
        Matrix modelMatrix,
        Matrix projectionMatrix,
        const GLint viewport[4],
        RealVector3D &result) {
        Matrix finalMatrix = modelMatrix.multiplicate(projectionMatrix);
        Matrix invertedMatrix;
        if(!finalMatrix.invert(&invertedMatrix)) {
            return false;
        }

        RealVector4D in;

        in._x = window._x;
        in._y = window._y;
        in._z = window._z;
        in._w = 1.0;

        /* Map x and y from window coordinates */
        in._x = (in._x - viewport[0]) / viewport[2];
        in._y = (in._y - viewport[1]) / viewport[3];

        /* Map to range -1 to 1 */
        in._x = in._x * 2.0 - 1.0;
        in._y = in._y * 2.0 - 1.0;
        in._z = in._z * 2.0 - 1.0;

        RealVector4D out = invertedMatrix.multiplicate(in);

        if(out._w == 0.0) {
            return false;
        }

        result._x = out._x / out._w;
        result._y = out._y / out._w;
        result._z = out._z / out._w;

        return true;
    }
};

} // namespace Glee3D

#endif // G3D_UTILITIES_H
