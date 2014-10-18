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
#include "g3d_utilities.h"
#include "math/g3d_vector4d.h"

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
        _rotation += delta;
        _rotation.setX(Utilities::limitDegrees(_rotation.x()));
        _rotation.setY(Utilities::limitDegrees(_rotation.y()));
        _rotation.setZ(Utilities::limitDegrees(_rotation.z()));
    }

    void Oriented::rotateAroundXAxis(double delta) {
        _rotation.setX(Utilities::limitDegrees(_rotation.x() + delta));
    }

    void Oriented::rotateAroundYAxis(double delta) {
        _rotation.setY(Utilities::limitDegrees(_rotation.y() + delta));
    }

    void Oriented::rotateAroundZAxis(double delta) {
        _rotation.setZ(Utilities::limitDegrees(_rotation.z() + delta));
    }

    void Oriented::setRotationAroundXAxis(double rotationAroundXAxis) {
        _rotation.setX(Utilities::limitDegrees(rotationAroundXAxis));
    }

    void Oriented::setRotationAroundYAxis(double rotationAroundYAxis) {
        _rotation.setY(Utilities::limitDegrees(rotationAroundYAxis));
    }

    void Oriented::setRotationAroundZAxis(double rotationAroundZAxis) {
        _rotation.setZ(Utilities::limitDegrees(rotationAroundZAxis));
    }

    Vector3D Oriented::rotation() {
        return _rotation;
    }

    double Oriented::rotationAroundXAxis() {
        return _rotation.x();
    }

    double Oriented::rotationAroundYAxis() {
        return _rotation.y();
    }

    double Oriented::rotationAroundZAxis() {
        return _rotation.z();
    }

    Vector3D Oriented::side() {
        return rotationMatrix().multiplicate(Vector4D(1.0, 0.0, 0.0, 1.0)).toVector3D();
    }

    Vector3D Oriented::up() {
        return rotationMatrix().multiplicate(Vector4D(0.0, 1.0, 0.0, 1.0)).toVector3D();
    }

    Vector3D Oriented::front() {
        return rotationMatrix().multiplicate(Vector4D(0.0, 0.0, 1.0, 1.0)).toVector3D();
    }

    Matrix4x4 Oriented::rotationMatrix() {
        return Matrix4x4()
            .withRotation(_rotation.x(), Vector3D(1.0, 0.0, 0.0))
            .withRotation(_rotation.y(), Vector3D(0.0, 1.0, 0.0))
            .withRotation(_rotation.z(), Vector3D(0.0, 0.0, 1.0));
    }

} // namespace Glee3D
