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
#include "g3d_camera.h"

// Qt includes
#include <QGLWidget>

// GL utilities includes
#include "GL/glu.h"

namespace Glee3D {
    Camera::Camera()
        : Anchored(),
          Oriented() {
        _near = 0.1;
        _far = 100000.0;
        _fieldOfView = 45.0;
        _aspectRatio = 0.75;

        _lookAt = RealVector3D(0.0, 0.0, 0.0);
    }

    void Camera::applyCameraMatrix() {
        // Generate camera matrices.
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(_fieldOfView, _aspectRatio, _near, _far);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(_position._x, _position._y, _position._z,
                  _lookAt._x, _lookAt._y, _lookAt._z,
                  upVector()._x, upVector()._y, upVector()._z);
    }

    MatrixState Camera::cameraMatrixState() {
        MatrixState matrixState(MatrixState::AutomaticSave | MatrixState::AutomaticRestore);
        applyCameraMatrix();
        return MatrixState();
    }

    void Camera::setAspectRatio(int width, int height) {
        _aspectRatio = (double)width / (double)height;
    }

    void Camera::setFieldOfView(double fieldOfView) {
        _fieldOfView = fieldOfView;
    }

    void Camera::setLookAt(RealVector3D target) {
        _lookAt = target;
    }

    RealVector3D Camera::lookAt() {
        return _lookAt;
    }

    void Camera::moveForward(double units) {
        RealVector3D direction = _lookAt - _position;
        direction.normalize();
        _position += direction * units;
        _lookAt += direction * units;
    }
} // namespace Glee3D
