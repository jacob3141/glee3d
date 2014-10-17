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
    Vector3D();
    Vector3D(double x, double y, double z);

    double length() const;
    Vector3D& normalize();
    Vector3D crossProduct(const Vector3D& other) const;
    double scalarProduct(const Vector3D& other) const;
    Vector3D& operator= (const Vector3D& other);
    Vector3D operator* (double scalar) const;
    Vector3D operator+ (const Vector3D& other) const;
    Vector3D& operator+= (const Vector3D& other);
    Vector3D operator- (const Vector3D& other) const;
    Vector3D operator- () const;
    Vector3D& operator-= (const Vector3D& other);

    QString className();
    QJsonObject serialize();
    bool deserialize(QJsonObject jsonObject);

    double *data();

    double x();
    double y();
    double z();

    void setX(double x);
    void setY(double y);
    void setZ(double z);

private:
    double _data[3];
};

} // namespace Glee3D

#endif // G3D_VECTOR3D_H
