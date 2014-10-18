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

// Standard includes
#include <math.h>

namespace Glee3D {

Vector3D::Vector3D() {
    _data[0] = 0.0;
    _data[1] = 0.0;
    _data[2] = 0.0;
}

Vector3D::Vector3D(double x, double y, double z) {
    _data[0] = x;
    _data[1] = y;
    _data[2] = z;
}


Vector3D::Vector3D(Vector2D v2d, double z) {
    _data[0] = v2d.x();
    _data[1] = v2d.y();
    _data[2] = z;
}

double Vector3D::length() const {
    return sqrt(_data[0] * _data[0] + _data[1] * _data[1] + _data[2] *_data[2]);
}

Vector3D& Vector3D::normalize() {
    double _length = length();
    if(_length > 0) {
        _data[0] /= _length;
        _data[1] /= _length;
        _data[2] /= _length;
    }
    return *this;
}

Vector3D Vector3D::crossProduct(const Vector3D& other) const {
    Vector3D result;
    result._data[0] = this->_data[1] * other._data[2] - this->_data[2] * other._data[1];
    result._data[1] = this->_data[2] * other._data[0] - this->_data[0] * other._data[2];
    result._data[2] = this->_data[0] * other._data[1] - this->_data[1] * other._data[0];
    return result;
}

double Vector3D::scalarProduct(const Vector3D& other) const {
    return this->_data[0] * other._data[0] + this->_data[1] * other._data[1] + this->_data[2] * other._data[2];
}

Vector3D& Vector3D::operator= (const Vector3D& other) {
  if(this != &other) {
      _data[0] = other._data[0];
      _data[1] = other._data[1];
      _data[2] = other._data[2];
  }
  return *this;
}

Vector3D Vector3D::operator* (double scalar) const {
    Vector3D result;
    result._data[0] = this->_data[0] * scalar;
    result._data[1] = this->_data[1] * scalar;
    result._data[2] = this->_data[2] * scalar;
    return result;
}

Vector3D Vector3D::operator+ (const Vector3D& other) const {
    Vector3D result;
    result._data[0] = this->_data[0] + other._data[0];
    result._data[1] = this->_data[1] + other._data[1];
    result._data[2] = this->_data[2] + other._data[2];
    return result;
}

Vector3D& Vector3D::operator+= (const Vector3D& other) {
    this->_data[0] += other._data[0];
    this->_data[1] += other._data[1];
    this->_data[2] += other._data[2];
    return *this;
}

Vector3D Vector3D::operator- (const Vector3D& other) const {
    Vector3D result;
    result._data[0] = this->_data[0] - other._data[0];
    result._data[1] = this->_data[1] - other._data[1];
    result._data[2] = this->_data[2] - other._data[2];
    return result;
}

Vector3D Vector3D::operator- () const {
    Vector3D result;
    result._data[0] = -this->_data[0];
    result._data[1] = -this->_data[1];
    result._data[2] = -this->_data[2];
    return result;
}

Vector3D& Vector3D::operator-= (const Vector3D& other) {
    _data[0] -= other._data[0];
    _data[1] -= other._data[1];
    _data[2] -= other._data[2];
    return *this;
}

QString Vector3D::className() {
    return "Vector3D";
}

QJsonObject Vector3D::serialize() {
    QJsonObject jsonObject;
    jsonObject["class"] = className();
    jsonObject["x"] = (double)_data[0];
    jsonObject["y"] = (double)_data[1];
    jsonObject["z"] = (double)_data[2];
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
            _data[0] = (double)jsonObject["x"].toDouble();
            _data[1] = (double)jsonObject["y"].toDouble();
            _data[2] = (double)jsonObject["z"].toDouble();
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

double *Vector3D::glDataPointer() {
    return _data;
}

double Vector3D::x() {
    return _data[0];
}

double Vector3D::y() {
    return _data[1];
}

double Vector3D::z() {
    return _data[2];
}

void Vector3D::setX(double x) {
    _data[0] = x;
}

void Vector3D::setY(double y) {
    _data[1] = y;
}

void Vector3D::setZ(double z) {
    _data[2] = z;
}

} // namespace Glee3D
