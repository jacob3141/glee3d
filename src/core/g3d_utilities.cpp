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
#include "core/g3d_utilities.h"
#include "math/g3d_vector4d.h"

// Qt includes
#include <QGLWidget>

namespace Glee3D {

void Utilities::perspective(
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

Matrix4x4 Utilities::lookAt(
    Vector3D eye,
    Vector3D center,
    Vector3D up) {

    Vector3D forward = (center - eye).normalize();
    Vector3D left = forward.crossProduct(up).normalize();
    up = left.crossProduct(forward);

    Matrix4x4 modelViewMatrix;
    modelViewMatrix.addRotation(left, up, -forward);
    modelViewMatrix.addTranslation(-eye);

    return modelViewMatrix;
}

bool Utilities::unproject(Vector3D window,
    Matrix4x4 modelMatrix,
    Matrix4x4 projectionMatrix,
    const int viewport[],
    Vector3D &result) {

    Matrix4x4 finalMatrix = projectionMatrix.multiplicate(modelMatrix);
    Matrix4x4 invertedMatrix;
    if(!finalMatrix.invert(&invertedMatrix)) {
        return false;
    }

    Vector4D in;

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

    Vector4D out = invertedMatrix.multiplicate(in);

    if(out._w == 0.0) {
        return false;
    }

    result._x = out._x / out._w;
    result._y = out._y / out._w;
    result._z = out._z / out._w;

    return true;
}

} // namespace Glee3D
