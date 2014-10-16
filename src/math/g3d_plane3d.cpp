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
#include "g3d_plane3d.h"

namespace Glee3D {

Plane3D::Plane3D(Vector3D v1,
        Vector3D v2,
        Vector3D v3,
        ConstructionMode constructionMode) {
    switch(constructionMode) {
    case ThreeVectors:
        _positionVector = v1;
        _directionVector1 = v2 - v1;
        _directionVector2 = v3 - v1;
        break;
    case PositionAndDirectionVectors:
        _positionVector = v1;
        _directionVector1 = v2;
        _directionVector2 =  v3;
        break;
    }
}

Vector3D Plane3D::point(double alpha, double beta) {
    return _positionVector + _directionVector1 * alpha + _directionVector2 * beta;
}

Vector3D Plane3D::intersection(Line3D line, bool *exists) {
    Vector3D planeNormal = _directionVector1.crossProduct(_directionVector2);
    double numerator = planeNormal.scalarProduct(_positionVector) - planeNormal.scalarProduct(line._positionVector);
    double denominator = planeNormal.scalarProduct(line._directionVector);
    if(denominator != 0.0) {
        double alpha = numerator / denominator;
        if(exists) {
            (*exists) = true;
        }
        return line.point(alpha);
    }
    if(exists) {
        (*exists) = false;
    }
    return Vector3D();
}

Vector3D Plane3D::normal() {
    return _directionVector1.crossProduct(_directionVector2).normalize();
}

QString Plane3D::className() {
    return "Plane3D";
}

QJsonObject Plane3D::serialize() {
    QJsonObject jsonObject;
    jsonObject["class"] = className();
    jsonObject["positionVector"] = _positionVector.serialize();
    jsonObject["directionVector1"] = _directionVector1.serialize();
    jsonObject["directionVector2"] = _directionVector2.serialize();
    return jsonObject;
}

bool Plane3D::deserialize(QJsonObject jsonObject) {
    if(!jsonObject.contains("class")) {
        _deserializationError = Serializable::NoClassSpecified;
        return false;
    }

    if(jsonObject.contains("positionVector")
    && jsonObject.contains("directionVector")) {
        if(jsonObject["class"] == className()) {
            if(!_positionVector.deserialize(jsonObject.value("positionVector").toObject())) {
                _deserializationError = _positionVector.deserializationError();
                return false;
            }

            if(!_directionVector1.deserialize(jsonObject.value("directionVector1").toObject())) {
                _deserializationError = _directionVector1.deserializationError();
                return false;
            }

            if(!_directionVector2.deserialize(jsonObject.value("directionVector2").toObject())) {
                _deserializationError = _directionVector2.deserializationError();
                return false;
            }

            _deserializationError = Serializable::NoError;
            return true;
        } else {
            _deserializationError = Serializable::WrongClass;
            return false;
        }
    } else {
        _deserializationError = Serializable::MissingElements;
        return false;
    }
}

} // namespace Glee3D
