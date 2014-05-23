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

#ifndef G3D_VECTOR3D_H
#define G3D_VECTOR3D_H

// Own includes
#include "g3d_configuration.h"
#include "g3d_serializable.h"

// Qt includes
#include <QDebug>

// C++ includes
#include <math.h>

namespace Glee3D {

/**
  * @class Vector3D
  * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
  * @date 02.12.2012
  */
template <typename NumberType>
class Vector3D : public Serializable {
public:
    Vector3D() {
        _x = 0.0;
        _y = 0.0;
        _z = 0.0;
    }

    Vector3D(NumberType x, NumberType y, NumberType z) {
        _x = x;
        _y = y;
        _z = z;
    }

    NumberType _x;
    NumberType _y;
    NumberType _z;

    NumberType length() const {
        return sqrt(_x * _x + _y * _y + _z *_z);
    }

    Vector3D& normalize() {
        NumberType _length = length();
        if(_length > 0) {
            _x /= _length;
            _y /= _length;
            _z /= _length;
        }
        return *this;
    }

    Vector3D crossProduct(const Vector3D& other) const {
        Vector3D result;
        result._x = this->_y * other._z - this->_z * other._y;
        result._y = this->_z * other._x - this->_x * other._z;
        result._z = this->_x * other._y - this->_y * other._x;
        return result;
    }

    NumberType scalarProduct(const Vector3D& other) const {
        return this->_x * other._x + this->_y * other._y + this->_z * other._z;
    }

    Vector3D& operator= (const Vector3D& other) {
      if(this != &other) {
          _x = other._x;
          _y = other._y;
          _z = other._z;
      }
      return *this;
    }

    Vector3D operator* (NumberType scalar) const {
        Vector3D result;
        result._x = this->_x * scalar;
        result._y = this->_y * scalar;
        result._z = this->_z * scalar;
        return result;
    }

    Vector3D operator+ (const Vector3D& other) const {
        Vector3D result;
        result._x = this->_x + other._x;
        result._y = this->_y + other._y;
        result._z = this->_z + other._z;
        return result;
    }

    Vector3D& operator+= (const Vector3D& other) {
        this->_x += other._x;
        this->_y += other._y;
        this->_z += other._z;
        return *this;
    }

    Vector3D operator- (const Vector3D& other) const {
        Vector3D result;
        result._x = this->_x - other._x;
        result._y = this->_y - other._y;
        result._z = this->_z - other._z;
        return result;
    }

    Vector3D operator- () const {
        Vector3D result;
        result._x = -this->_x;
        result._y = -this->_y;
        result._z = -this->_z;
        return result;
    }

    Vector3D& operator-= (const Vector3D& other) {
        _x -= other._x;
        _y -= other._y;
        _z -= other._z;
        return *this;
    }

    QString className() {
        return "Vector3D";
    }

    QJsonObject serialize() {
        QJsonObject jsonObject;
        jsonObject["class"] = className();
        jsonObject["x"] = (double)_x;
        jsonObject["y"] = (double)_y;
        jsonObject["z"] = (double)_z;
        return jsonObject;
    }

    bool deserialize(QJsonObject jsonObject) {
        if(!jsonObject.contains("class")) {
            _deserializationError = Serializable::NoClassSpecified;
            return false;
        }

        if(jsonObject.contains("x")
        && jsonObject.contains("y")
        && jsonObject.contains("z")) {
            if(jsonObject["class"] == className()) {
                _x = (NumberType)jsonObject["x"].toDouble();
                _y = (NumberType)jsonObject["y"].toDouble();
                _z = (NumberType)jsonObject["z"].toDouble();
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
};

/**
  * @class Line3D
  * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
  * @date 02.12.2012
  */
template <typename Type>
class Line3D {
public:
    Vector3D<Type> point(Type alpha) const {
        return _positionVector + _directionVector * alpha;
    }

    Vector3D<Type> _positionVector;
    Vector3D<Type> _directionVector;
};

/**
  * @class Plane3D
  * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
  * @date 02.12.2012
  */
template <typename Type>
class Plane3D {
public:
    enum ConstructionMode {
        ThreeVectors,
        PositionAndDirectionVectors
    };

    Plane3D(Vector3D<Type> v1,
            Vector3D<Type> v2,
            Vector3D<Type> v3,
            ConstructionMode constructionMode = ThreeVectors) {
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

    Vector3D<Type> point(Type alpha, Type beta) {
        return _positionVector + _directionVector1 * alpha + _directionVector2 * beta;
    }

    Vector3D<Type> intersection(Line3D<Type> line) {
        Vector3D<Type> planeNormal = _directionVector1.crossProduct(_directionVector2);
        Type numerator = planeNormal.scalarProduct(_positionVector) - planeNormal.scalarProduct(line._positionVector);
        Type denominator = planeNormal.scalarProduct(line._directionVector);
        if(denominator != 0.0) {
            Type alpha = numerator / denominator;
            return line.point(alpha);
        }
        return Vector3D<Type>();
    }

    Vector3D<Type> _positionVector;
    Vector3D<Type> _directionVector1;
    Vector3D<Type> _directionVector2;
};

typedef Vector3D<FLOATING_POINT_FORMAT> RealVector3D;
typedef Line3D<FLOATING_POINT_FORMAT> RealLine3D;
typedef Plane3D<FLOATING_POINT_FORMAT> RealPlane3D;

} // namespace Glee3D

#endif // G3D_VECTOR3D_H
