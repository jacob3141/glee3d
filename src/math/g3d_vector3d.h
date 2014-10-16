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

#ifndef G3D_VECTOR3D_H
#define G3D_VECTOR3D_H

// Own includes
#include "io/g3d_serializable.h"

// Qt includes
#include <QDebug>

// C++ includes
#include <math.h>

namespace Glee3D {

/**
  * @class Vector3D
  * @author Jacob Dawid (jacob.dawid@omg-it.works)
  * @date 02.12.2012
  */
class Vector3D : public Serializable {
public:
    Vector3D() {
        _x = 0.0;
        _y = 0.0;
        _z = 0.0;
    }

    Vector3D(double x, double y, double z) {
        _x = x;
        _y = y;
        _z = z;
    }

    double _x;
    double _y;
    double _z;

    double length() const {
        return sqrt(_x * _x + _y * _y + _z *_z);
    }

    Vector3D& normalize() {
        double _length = length();
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

    double scalarProduct(const Vector3D& other) const {
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

    Vector3D operator* (double scalar) const {
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
                _x = (double)jsonObject["x"].toDouble();
                _y = (double)jsonObject["y"].toDouble();
                _z = (double)jsonObject["z"].toDouble();
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

} // namespace Glee3D

#endif // G3D_VECTOR3D_H
