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

#ifndef G3D_PLANE3D_H
#define G3D_PLANE3D_H

// Own includes
#include "math/g3d_vector3d.h"
#include "math/g3d_line3d.h"
#include "io/g3d_serializable.h"

namespace Glee3D {
    /**
      * @class Plane3D
      * @author Jacob Dawid (jacob.dawid@omg-it.works)
      * @date 02.12.2012
      */
    class Plane3D : public Serializable {
    public:
        enum ConstructionMode {
            ThreeVectors,
            PositionAndDirectionVectors
        };

        Plane3D(Vector3D v1,
                Vector3D v2,
                Vector3D v3,
                ConstructionMode constructionMode = ThreeVectors);
        /**
         * Calculates a specific point on the plane in plane coordinates. The
         * unit is determined by the two direction vectors, alpha and beta being
         * multipliers of these.
         * @param alpha Multiplier for the first direction vector.
         * @param beta Multiplier for the second direction vector.
         * @returns the point on the plane.
         */
        Vector3D point(double alpha, double beta);

        /**
         * Calculates the intersection point of a line and this plane.
         * @param line
         * @param exists
         * @return
         */
        Vector3D intersection(Line3D line, bool *exists = 0);

        /**
         * @returns the normalized plane normal.
         */
        Vector3D normal();

        QString className();
        QJsonObject serialize();
        bool deserialize(QJsonObject jsonObject);

        Vector3D _positionVector;
        Vector3D _directionVector1;
        Vector3D _directionVector2;
    };
} // namespace Glee3D;

#endif // G3D_PLANE3D_H
