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
#include "g3d_vector4d.h"

namespace Glee3D {

Vector4D::Vector4D() {
    _data[0] = 0.0;
    _data[1] = 0.0;
    _data[2] = 0.0;
    _data[3] = 0.0;
}

Vector4D::Vector4D(double x, double y, double z, double w) {
    _data[0] = x;
    _data[1] = y;
    _data[2] = z;
    _data[3] = w;
}

Vector4D::Vector4D(Vector3D v3d, double w) {
    _data[0] = v3d.x();
    _data[1] = v3d.y();
    _data[2] = v3d.z();
    _data[3] = w;
}

Vector4D::Vector4D(Vector2D v2d, double z, double w) {
    _data[0] = v2d.x();
    _data[1] = v2d.y();
    _data[2] = z;
    _data[3] = w;
}

double Vector4D::length() const {
    return sqrt(_data[0] * _data[0] + _data[1] * _data[1] + _data[2] *_data[2] + _data[3] * _data[3]);
}

Vector4D& Vector4D::normalize() {
    double _length = length();
    if(_length > 0) {
        _data[0] /= _length;
        _data[1] /= _length;
        _data[2] /= _length;
        _data[3] /= _length;
    }
    return *this;
}

Vector4D& Vector4D::operator= (const Vector4D& other) {
  if(this != &other) {
      _data[0] = other._data[0];
      _data[1] = other._data[1];
      _data[2] = other._data[2];
      _data[3] = other._data[3];
  }
  return *this;
}

Vector4D Vector4D::operator* (double scalar) const {
    Vector4D result;
    result._data[0] = this->_data[0] * scalar;
    result._data[1] = this->_data[1] * scalar;
    result._data[2] = this->_data[2] * scalar;
    result._data[3] = this->_data[3] * scalar;
    return result;
}

Vector4D Vector4D::operator+ (const Vector4D& other) const {
    Vector4D result;
    result._data[0] = this->_data[0] + other._data[0];
    result._data[1] = this->_data[1] + other._data[1];
    result._data[2] = this->_data[2] + other._data[2];
    result._data[3] = this->_data[3] + other._data[3];
    return result;
}

Vector4D& Vector4D::operator+= (const Vector4D& other) {
    this->_data[0] += other._data[0];
    this->_data[1] += other._data[1];
    this->_data[2] += other._data[2];
    this->_data[3] += other._data[3];
    return *this;
}

Vector4D Vector4D::operator- (const Vector4D& other) const {
    Vector4D result;
    result._data[0] = this->_data[0] - other._data[0];
    result._data[1] = this->_data[1] - other._data[1];
    result._data[2] = this->_data[2] - other._data[2];
    result._data[3] = this->_data[3] - other._data[3];
    return result;
}

Vector4D Vector4D::operator- () const {
    Vector4D result;
    result._data[0] = -this->_data[0];
    result._data[1] = -this->_data[1];
    result._data[2] = -this->_data[2];
    result._data[3] = -this->_data[3];
    return result;
}

Vector4D& Vector4D::operator-= (const Vector4D& other) {
    _data[0] -= other._data[0];
    _data[1] -= other._data[1];
    _data[2] -= other._data[2];
    _data[3] -= other._data[3];
    return *this;
}


Vector3D Vector4D::toVector3D(bool divideByW) {
    if(divideByW) {
        return Vector3D(_data[0] / _data[3], _data[1] / _data[3], _data[2] / _data[3]);
    } else {
        return Vector3D(_data[0], _data[1], _data[2]);
    }
}

QString Vector4D::className() {
    return "Vector4D";
}

QJsonObject Vector4D::serialize() {
    QJsonObject jsonObject;
    jsonObject["class"] = className();
    jsonObject["x"] = (double)_data[0];
    jsonObject["y"] = (double)_data[1];
    jsonObject["z"] = (double)_data[2];
    jsonObject["w"] = (double)_data[3];
    return jsonObject;
}

bool Vector4D::deserialize(QJsonObject jsonObject) {
    if(!jsonObject.contains("class")) {
        _deserializationError = Serializable::NoClassSpecified;
        return false;
    }

    if(jsonObject.contains("x")
    && jsonObject.contains("y")
    && jsonObject.contains("z")
    && jsonObject.contains("w")) {
        if(jsonObject["class"] == className()) {
            _data[0] = (double)jsonObject["x"].toDouble();
            _data[1] = (double)jsonObject["y"].toDouble();
            _data[2] = (double)jsonObject["z"].toDouble();
            _data[3] = (double)jsonObject["w"].toDouble();
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

double *Vector4D::data() {
    return _data;
}

double Vector4D::x() {
    return _data[0];
}

double Vector4D::y() {
    return _data[1];
}

double Vector4D::z() {
    return _data[2];
}

double Vector4D::w() {
    return _data[3];
}

void Vector4D::setX(double x) {
    _data[0] = x;
}

void Vector4D::setY(double y) {
    _data[1] = y;
}

void Vector4D::setZ(double z) {
    _data[2] = z;
}

void Vector4D::setW(double w) {
    _data[3] = w;
}

} // namespace Glee3D
