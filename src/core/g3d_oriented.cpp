///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of glee3d.                                           //
//    Copyright (C) 2015 Jacob Dawid, jacob.dawid@omg-it.works          //
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
#include "g3d_oriented.h"
#include "g3d_matrixstate.h"

// Qt includes
#include <QGLWidget>

namespace Glee3D {
    Oriented::Oriented() {
        _rotation = Vector3D(0.0, 0.0, 0.0);
    }

    Oriented::~Oriented() {
    }

    void Oriented::setRotation(Vector3D value) {
        _rotation = value;
    }

    void Oriented::rotate(Vector3D delta) {
        // Rescue the modelview matrix, so we can restore it after we're done
        MatrixState matrixState;
        matrixState.save();

        // Rotate identity with the current rotation values
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotated(_rotation.x(), 1.0, 0.0, 0.0);
        glRotated(_rotation.y(), 0.0, 1.0, 0.0);
        glRotated(_rotation.z(), 0.0, 0.0, 1.0);

        // Apply new rotation
        glRotated(delta.x(), 1.0, 0.0, 0.0);
        glRotated(delta.y(), 0.0, 1.0, 0.0);
        glRotated(delta.z(), 0.0, 0.0, 1.0);

        // Extract results back into our rotation values
        float m[16];
        glGetFloatv(GL_MODELVIEW_MATRIX , m);

        _rotation.setY(asin(m[8]) * 180.0 / M_PI);
        if( _rotation.y() < 90.0 ) {
            if( _rotation.y() > -90.0 ) {
                _rotation.setX(atan2(-m[9], m[10]) * 180.0 / M_PI);
                _rotation.setZ(atan2(-m[4], m[0]) * 180.0 / M_PI);
            } else {
                _rotation.setX(-atan2(m[1], m[5]) * 180.0 / M_PI);
                _rotation.setZ(0.0);
            }
        } else {
            _rotation.setX(atan2(m[1], m[5])*180.0 / M_PI);
            _rotation.setZ(0.0);
        }

        // Restore modelview matrix state
        matrixState.restore();
    }

    Vector3D Oriented::rotation() {
        return _rotation;
    }

    Vector3D Oriented::sideVector() {
        // TODO: This method is broken and needs a rewrite.
        return Vector3D();
    }

    Vector3D Oriented::frontVector() {
        // TODO: This method is broken and needs a rewrite.
        Vector3D result;
        double rot_x = _rotation.x() * 2 * M_PI / 360.0;
        double rot_y = _rotation.y() * 2 * M_PI / 360.0;

        result.setX(sin(rot_y));
        result.setY(- sin(rot_x) * cos(rot_y));
        result.setZ(cos(rot_x) * cos(rot_y));
        return result;
    }

    Vector3D Oriented::upVector() {
        // TODO: This method is broken and needs a rewrite.
        Vector3D result;
        double rot_x = _rotation.x() * 2 * M_PI / 360.0;
        double rot_y = _rotation.y() * 2 * M_PI / 360.0;
        double rot_z = _rotation.z() * 2 * M_PI / 360.0;

        result.setX(- cos(rot_y) * sin(rot_z));
        result.setY(- sin(rot_z) * sin(rot_y) * sin(rot_x) + cos(rot_x) * cos(rot_z));
        result.setZ(cos(rot_x) * sin(rot_y) * sin(rot_z) + cos(rot_z) * sin(rot_x));
        return result;
    }

    void Oriented::applyRotation() {
        glRotated(_rotation.x(), 1.0, 0.0, 0.0);
        glRotated(_rotation.y(), 0.0, 1.0, 0.0);
        glRotated(_rotation.z(), 0.0, 0.0, 1.0);
    }

} // namespace Glee3D
