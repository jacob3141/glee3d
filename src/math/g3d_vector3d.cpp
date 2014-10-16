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
#include "g3d_vector3d.h"

namespace Glee3D {

Vector3D::Vector3D() {
    _x = 0.0;
    _y = 0.0;
    _z = 0.0;
}

Vector3D::Vector3D(double x, double y, double z) {
    _x = x;
    _y = y;
    _z = z;
}

double Vector3D::length() const {
    return sqrt(_x * _x + _y * _y + _z *_z);
}

Vector3D& Vector3D::normalize() {
    double _length = length();
    if(_length > 0) {
        _x /= _length;
        _y /= _length;
        _z /= _length;
    }
    return *this;
}

Vector3D Vector3D::crossProduct(const Vector3D& other) const {
    Vector3D result;
    result._x = this->_y * other._z - this->_z * other._y;
    result._y = this->_z * other._x - this->_x * other._z;
    result._z = this->_x * other._y - this->_y * other._x;
    return result;
}

double Vector3D::scalarProduct(const Vector3D& other) const {
    return this->_x * other._x + this->_y * other._y + this->_z * other._z;
}

Vector3D& Vector3D::operator= (const Vector3D& other) {
  if(this != &other) {
      _x = other._x;
      _y = other._y;
      _z = other._z;
  }
  return *this;
}

Vector3D Vector3D::operator* (double scalar) const {
    Vector3D result;
    result._x = this->_x * scalar;
    result._y = this->_y * scalar;
    result._z = this->_z * scalar;
    return result;
}

Vector3D Vector3D::operator+ (const Vector3D& other) const {
    Vector3D result;
    result._x = this->_x + other._x;
    result._y = this->_y + other._y;
    result._z = this->_z + other._z;
    return result;
}

Vector3D& Vector3D::operator+= (const Vector3D& other) {
    this->_x += other._x;
    this->_y += other._y;
    this->_z += other._z;
    return *this;
}

Vector3D Vector3D::operator- (const Vector3D& other) const {
    Vector3D result;
    result._x = this->_x - other._x;
    result._y = this->_y - other._y;
    result._z = this->_z - other._z;
    return result;
}

Vector3D Vector3D::operator- () const {
    Vector3D result;
    result._x = -this->_x;
    result._y = -this->_y;
    result._z = -this->_z;
    return result;
}

Vector3D& Vector3D::operator-= (const Vector3D& other) {
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;
    return *this;
}

QString Vector3D::className() {
    return "Vector3D";
}

QJsonObject Vector3D::serialize() {
    QJsonObject jsonObject;
    jsonObject["class"] = className();
    jsonObject["x"] = (double)_x;
    jsonObject["y"] = (double)_y;
    jsonObject["z"] = (double)_z;
    return jsonObject;
}

bool Vector3D::deserialize(QJsonObject jsonObject) {
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

} // namespace Glee3D
