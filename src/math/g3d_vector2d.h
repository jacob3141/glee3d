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

#ifndef G3D_VECTOR2D_H
#define G3D_VECTOR2D_H

// Own includes
#include "io/g3d_serializable.h"

namespace Glee3D {

/**
  * @class Vector2D
  * @author Jacob Dawid (jacob.dawid@omg-it.works)
  * @date 02.12.2012
  */
class Vector2D : public Serializable {
public:
    Vector2D();

    Vector2D(double x, double y);

    double length() const;
    Vector2D& normalize();
    Vector2D& limit(Vector2D lower, Vector2D upper);
    Vector2D& operator= (const Vector2D& other);
    Vector2D operator* (double scalar) const;
    Vector2D operator/ (double scalar) const;
    Vector2D operator+ (const Vector2D& other) const;
    Vector2D& operator+= (const Vector2D& other);
    Vector2D operator- (const Vector2D& other) const;
    Vector2D operator- () const;
    Vector2D& operator-= (const Vector2D& other);
    bool operator== (const Vector2D& other);

    QString className();
    QJsonObject serialize();
    bool deserialize(QJsonObject jsonObject);

    double *data();

    double x();
    double y();

    void setX(double x);
    void setY(double y);

private:
    double _data[2];
};

} // namespace Glee3D

#endif // G3D_VECTOR2D_H
