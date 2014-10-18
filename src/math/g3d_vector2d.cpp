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
#include "g3d_vector2d.h"

// Standard includes
#include <math.h>

namespace Glee3D {

Vector2D::Vector2D() {
    _data[0] = 0.0;
    _data[1] = 0.0;
}

Vector2D::Vector2D(double x, double y) {
    _data[0] = x;
    _data[1] = y;
}

double Vector2D::length() const {
    return sqrt(_data[0] * _data[0] + _data[1] * _data[1]);
}

Vector2D& Vector2D::normalize() {
    double _length = length();
    if(_length > 0) {
        _data[0] /= _length;
        _data[1] /= _length;
    }
    return *this;
}

Vector2D& Vector2D::limit(Vector2D lower, Vector2D upper) {
    if(_data[0] < lower._data[0])
        _data[0] = lower._data[0];
    if(_data[1] < lower._data[1])
        _data[1] = lower._data[1];
    if(_data[0] > upper._data[0])
        _data[0] = upper._data[0];
    if(_data[1] > upper._data[1])
        _data[1] = upper._data[1];
    return *this;
}

Vector2D& Vector2D::operator= (const Vector2D& other) {
  if(this != &other) {
      _data[0] = other._data[0];
      _data[1] = other._data[1];
  }
  return *this;
}

Vector2D Vector2D::operator* (double scalar) const {
    Vector2D result;
    result._data[0] = this->_data[0] * scalar;
    result._data[1] = this->_data[1] * scalar;
    return result;
}

Vector2D Vector2D::operator/ (double scalar) const {
    Vector2D result;
    result._data[0] = this->_data[0] / scalar;
    result._data[1] = this->_data[1] / scalar;
    return result;
}

Vector2D Vector2D::operator+ (const Vector2D& other) const {
    Vector2D result;
    result._data[0] = this->_data[0] + other._data[0];
    result._data[1] = this->_data[1] + other._data[1];
    return result;
}

Vector2D& Vector2D::operator+= (const Vector2D& other) {
    this->_data[0] += other._data[0];
    this->_data[1] += other._data[1];
    return *this;
}

Vector2D Vector2D::operator- (const Vector2D& other) const {
    Vector2D result;
    result._data[0] = this->_data[0] - other._data[0];
    result._data[1] = this->_data[1] - other._data[1];
    return result;
}

Vector2D Vector2D::operator- () const {
    Vector2D result;
    result._data[0] = -this->_data[0];
    result._data[1] = -this->_data[1];
    return result;
}

Vector2D& Vector2D::operator-= (const Vector2D& other) {
    _data[0] -= other._data[0];
    _data[1] -= other._data[1];
    return *this;
}

bool Vector2D::operator== (const Vector2D& other) {
    return (_data[0] == other._data[0]) && (_data[1] == other._data[1]);
}

QString Vector2D::className() {
    return "Vector2D";
}

QJsonObject Vector2D::serialize() {
    QJsonObject jsonObject;
    jsonObject["class"] = className();
    jsonObject["x"] = (double)_data[0];
    jsonObject["y"] = (double)_data[1];
    return jsonObject;
}

bool Vector2D::deserialize(QJsonObject jsonObject) {
    if(!jsonObject.contains("class")) {
        _deserializationError = Serializable::NoClassSpecified;
        return false;
    }

    if(jsonObject.contains("x")
    && jsonObject.contains("y")) {
        if(jsonObject["class"] == className()) {
            _data[0] = (double)jsonObject["x"].toDouble();
            _data[1] = (double)jsonObject["y"].toDouble();
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

double *Vector2D::glDataPointer() {
    return _data;
}

double Vector2D::x() {
    return _data[0];
}

double Vector2D::y() {
    return _data[1];
}

void Vector2D::setX(double x) {
    _data[0] = x;
}

void Vector2D::setY(double y) {
    _data[1] = y;
}

} // namespace Glee3D
