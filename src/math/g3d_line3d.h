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

#ifndef G3D_LINE3D_H
#define G3D_LINE3D_H

// Own includes
#include "math/g3d_vector3d.h"
#include "io/g3d_serializable.h"

namespace Glee3D {
    /**
      * @class Line3D
      * @author Jacob Dawid (jacob.dawid@omg-it.works)
      * @date 02.12.2012
      */
    class Line3D : public Serializable {
    public:
        Vector3D point(double alpha) const;

        QString className();
        QJsonObject serialize();
        bool deserialize(QJsonObject jsonObject);

        Vector3D _positionVector;
        Vector3D _directionVector;
    };

} // namespace Glee3D

#endif // G3D_LINE3D_H
