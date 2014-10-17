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

Matrix4x4 Utilities::perspective(
    double fieldOfView,
    double aspectRatio,
    double near,
    double far) {

    double xmin, xmax, ymin, ymax;
    ymax = near * tan(fieldOfView * M_PI / 360.0);
    ymin = -ymax;
    xmin = ymin * aspectRatio;
    xmax = ymax * aspectRatio;

    return frustum(xmin, xmax, ymin, ymax, near, far);
}

Matrix4x4 Utilities::frustum(
    double left,
    double right,
    double bottom,
    double top,
    double near,
    double far) {
    Matrix4x4 perspectiveMatrix;
    double *data = perspectiveMatrix.data();
    data[0]  = 2.0 * near / (right - left);
    data[5]  = 2.0 * near / (top - bottom);
    data[8]  = (right + left) / (right - left);
    data[9]  = (top + bottom) / (top - bottom);
    data[10] = - (far + near) / (far - near);
    data[11] = -1.0;
    data[14] = - (2.0 * far * near) / (far - near);
    data[15] = 0.0;
    return perspectiveMatrix;
}

Matrix4x4 Utilities::ortho(
    double left,
    double right,
    double bottom,
    double top,
    double near,
    double far) {
    Matrix4x4 perspectiveMatrix;
    double *data = perspectiveMatrix.data();
    data[0]  = 2.0 / (right - left);
    data[5]  = 2.0 / (top - bottom);
    data[10] = -2.0 / (far - near);
    data[12] = - (right + left) / (right - left);
    data[13] = - (top + bottom) / (top - bottom);
    data[14] = - (far + near) / (far - near);
    data[15] = 1.0;
    return perspectiveMatrix;
}

Matrix4x4 Utilities::lookAt(
    Vector3D eye,
    Vector3D center,
    Vector3D up) {

    Vector3D forward = (center - eye).normalize();
    Vector3D left = forward.crossProduct(up).normalize();
    up = left.crossProduct(forward);

    return Matrix4x4().withTranslation(-eye).withRotation(left, up, -forward);
}

bool Utilities::unproject(Vector3D window,
    Matrix4x4 modelMatrix,
    Matrix4x4 projectionMatrix,
    const int viewport[],
    Vector3D &result) {

    Matrix4x4 finalMatrix = modelMatrix.multiplicate(projectionMatrix);
    Matrix4x4 invertedMatrix;
    if(!finalMatrix.invert(&invertedMatrix)) {
        return false;
    }

    Vector4D in(window, 1.0);

    /* Map x and y from window coordinates */
    in.setX((in.x() - viewport[0]) / viewport[2]);
    in.setY((in.y() - viewport[1]) / viewport[3]);

    /* Map to range -1 to 1 */
    in.setX(in.x() * 2.0 - 1.0);
    in.setY(in.y() * 2.0 - 1.0);
    in.setZ(in.z() * 2.0 - 1.0);

    Vector4D out = invertedMatrix.multiplicate(in);

    if(out.w() == 0.0) {
        return false;
    }

    result = out.toVector3D();
    return true;
}

} // namespace Glee3D
