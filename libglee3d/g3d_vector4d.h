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

#ifndef G3D_VECTOR4D_H
#define G3D_VECTOR4D_H

// C++ includes
#include <math.h>

namespace Glee3D {

/**
  * @class Vector4D
  * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
  * @date 02.12.2012
  */
template <typename Type>
class Vector4D {
public:
    Vector4D() {
        _x = 0.0;
        _y = 0.0;
        _z = 0.0;
        _w = 0.0;
    }

    Vector4D(Type x, Type y, Type z, Type w) {
        _x = x;
        _y = y;
        _z = z;
        _w = w;
    }

    Type _x;
    Type _y;
    Type _z;
    Type _w;

    Type length() const {
        return sqrt(_x * _x + _y * _y + _z *_z + _w * _w);
    }

    Vector4D& normalize() {
        Type _length = length();
        if(_length > 0) {
            _x /= _length;
            _y /= _length;
            _z /= _length;
            _w /= _length;
        }
        return *this;
    }


    Vector4D& operator= (const Vector4D& other) {
      if(this != &other) {
          _x = other._x;
          _y = other._y;
          _z = other._z;
          _w = other._w;
      }
      return *this;
    }

    Vector4D operator* (Type scalar) const {
        Vector4D result;
        result._x = this->_x * scalar;
        result._y = this->_y * scalar;
        result._z = this->_z * scalar;
        result._w = this->_w * scalar;
        return result;
    }

    Vector4D operator+ (const Vector4D& other) const {
        Vector4D result;
        result._x = this->_x + other._x;
        result._y = this->_y + other._y;
        result._z = this->_z + other._z;
        result._w = this->_w + other._w;
        return result;
    }

    Vector4D& operator+= (const Vector4D& other) {
        this->_x += other._x;
        this->_y += other._y;
        this->_z += other._z;
        this->_w += other._w;
        return *this;
    }

    Vector4D operator- (const Vector4D& other) const {
        Vector4D result;
        result._x = this->_x - other._x;
        result._y = this->_y - other._y;
        result._z = this->_z - other._z;
        result._w = this->_w - other._w;
        return result;
    }

    Vector4D operator- () const {
        Vector4D result;
        result._x = -this->_x;
        result._y = -this->_y;
        result._z = -this->_z;
        result._w = -this->_w;
        return result;
    }

    Vector4D& operator-= (const Vector4D& other) {
        _x -= other._x;
        _y -= other._y;
        _z -= other._z;
        _w -= other._w;
        return *this;
    }
};

typedef Vector4D<FLOATING_POINT_FORMAT> RealVector4D;

} // namespace Glee3D

#endif // G3D_VECTOR4D_H
