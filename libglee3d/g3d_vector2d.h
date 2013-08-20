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

#ifndef G3D_VECTOR2D_H
#define G3D_VECTOR2D_H

// Own includes
#include "g3d_configuration.h"

// C++ includes
#include <math.h>

namespace Glee3D {

/**
  * @class Vector2D
  * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
  * @date 02.12.2012
  */
template <typename Type>
class Vector2D {
public:
    Vector2D() {
        _x = 0.0;
        _y = 0.0;
    }

    Vector2D(Type x, Type y) {
        _x = x;
        _y = y;
    }

    Type _x;
    Type _y;

    Type length() const {
        return sqrt(_x * _x + _y * _y);
    }

    Vector2D& normalize() {
        Type _length = length();
        if(_length > 0) {
            _x /= _length;
            _y /= _length;
        }
        return *this;
    }

    Vector2D& limit(Vector2D lower, Vector2D upper) {
        if(_x < lower._x)
            _x = lower._x;
        if(_y < lower._y)
            _y = lower._y;
        if(_x > upper._x)
            _x = upper._x;
        if(_y > upper._y)
            _y = upper._y;
        return *this;
    }

    Vector2D& operator= (const Vector2D& other) {
      if(this != &other) {
          _x = other._x;
          _y = other._y;
      }
      return *this;
    }

    Vector2D operator* (Type scalar) const {
        Vector2D result;
        result._x = this->_x * scalar;
        result._y = this->_y * scalar;
        return result;
    }

    Vector2D operator/ (Type scalar) const {
        Vector2D result;
        result._x = this->_x / scalar;
        result._y = this->_y / scalar;
        return result;
    }

    Vector2D operator+ (const Vector2D& other) const {
        Vector2D result;
        result._x = this->_x + other._x;
        result._y = this->_y + other._y;
        return result;
    }

    Vector2D& operator+= (const Vector2D& other) {
        this->_x += other._x;
        this->_y += other._y;
        return *this;
    }

    Vector2D operator- (const Vector2D& other) const {
        Vector2D result;
        result._x = this->_x - other._x;
        result._y = this->_y - other._y;
        return result;
    }

    Vector2D operator- () const {
        Vector2D result;
        result._x = -this->_x;
        result._y = -this->_y;
        return result;
    }

    Vector2D& operator-= (const Vector2D& other) {
        _x -= other._x;
        _y -= other._y;
        return *this;
    }

    bool operator== (const Vector2D& other) {
        return (_x == other._x) && (_y == other._y);
    }
};

typedef Vector2D<FLOATING_POINT_FORMAT> RealVector2D;
typedef Vector2D<int> IntVector2D;

} // namespace Glee3D

#endif // G3D_VECTOR2D_H
