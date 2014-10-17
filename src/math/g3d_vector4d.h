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

#ifndef G3D_VECTOR4D_H
#define G3D_VECTOR4D_H

// Own includes
#include "io/g3d_serializable.h"
#include "math/g3d_vector2d.h"
#include "math/g3d_vector3d.h"

// C++ includes
#include <math.h>

namespace Glee3D {

/**
  * @class Vector4D
  * @author Jacob Dawid (jacob.dawid@omg-it.works)
  * @date 02.12.2012
  */
class Vector4D : public Serializable {
public:
    Vector4D();
    Vector4D(double x, double y, double z, double w);
    Vector4D(Vector3D v3d, double w = 1.0);
    Vector4D(Vector2D v2d, double z = 0.0, double w = 1.0);

    double length() const;
    Vector4D& normalize();
    Vector4D& operator= (const Vector4D& other);
    Vector4D operator* (double scalar) const;
    Vector4D operator+ (const Vector4D& other) const;
    Vector4D& operator+= (const Vector4D& other);
    Vector4D operator- (const Vector4D& other) const;
    Vector4D operator- () const ;
    Vector4D& operator-= (const Vector4D& other);

    Vector3D toVector3D(bool divideByW = true);

    QString className();
    QJsonObject serialize();
    bool deserialize(QJsonObject jsonObject);

    double *data();

    double x();
    double y();
    double z();
    double w();

    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setW(double w);

private:
    double _data[4];
};

} // namespace Glee3D

#endif // G3D_VECTOR4D_H
