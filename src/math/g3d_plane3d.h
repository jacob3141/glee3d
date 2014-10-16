///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of glee3d.                                           //
//    Copyright (C) 2012-2014 Jacob Dawid, jacob.dawid@omg-it.works          //
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
    template <typename NumberType>
    class Plane3D : public Serializable {
    public:
        enum ConstructionMode {
            ThreeVectors,
            PositionAndDirectionVectors
        };

        Plane3D(Vector3D<NumberType> v1,
                Vector3D<NumberType> v2,
                Vector3D<NumberType> v3,
                ConstructionMode constructionMode = ThreeVectors) {
            switch(constructionMode) {
            case ThreeVectors:
                _positionVector = v1;
                _directionVector1 = v2 - v1;
                _directionVector2 = v3 - v1;
                break;
            case PositionAndDirectionVectors:
                _positionVector = v1;
                _directionVector1 = v2;
                _directionVector2 =  v3;
                break;
            }
        }

        /**
         * Calculates a specific point on the plane in plane coordinates. The
         * unit is determined by the two direction vectors, alpha and beta being
         * multipliers of these.
         * @param alpha Multiplier for the first direction vector.
         * @param beta Multiplier for the second direction vector.
         * @returns the point on the plane.
         */
        Vector3D<NumberType> point(NumberType alpha, NumberType beta) {
            return _positionVector + _directionVector1 * alpha + _directionVector2 * beta;
        }

        /**
         * Calculates the intersection point of a line and this plane.
         * @param line
         * @param exists
         * @return
         */
        Vector3D<NumberType> intersection(Line3D<NumberType> line, bool *exists = 0) {
            Vector3D<NumberType> planeNormal = _directionVector1.crossProduct(_directionVector2);
            NumberType numerator = planeNormal.scalarProduct(_positionVector) - planeNormal.scalarProduct(line._positionVector);
            NumberType denominator = planeNormal.scalarProduct(line._directionVector);
            if(denominator != 0.0) {
                NumberType alpha = numerator / denominator;
                if(exists) {
                    (*exists) = true;
                }
                return line.point(alpha);
            }
            if(exists) {
                (*exists) = false;
            }
            return Vector3D<NumberType>();
        }

        /**
         * @returns the normalized plane normal.
         */
        Vector3D<NumberType> normal() {
            return _directionVector1.crossProduct(_directionVector2).normalize();
        }

        QString className() {
            return "Plane3D";
        }

        QJsonObject serialize() {
            QJsonObject jsonObject;
            jsonObject["class"] = className();
            jsonObject["positionVector"] = _positionVector.serialize();
            jsonObject["directionVector1"] = _directionVector1.serialize();
            jsonObject["directionVector2"] = _directionVector2.serialize();
            return jsonObject;
        }

        bool deserialize(QJsonObject jsonObject) {
            if(!jsonObject.contains("class")) {
                _deserializationError = Serializable::NoClassSpecified;
                return false;
            }

            if(jsonObject.contains("positionVector")
            && jsonObject.contains("directionVector")) {
                if(jsonObject["class"] == className()) {
                    if(!_positionVector.deserialize(jsonObject.value("positionVector").toObject())) {
                        _deserializationError = _positionVector.deserializationError();
                        return false;
                    }

                    if(!_directionVector1.deserialize(jsonObject.value("directionVector1").toObject())) {
                        _deserializationError = _directionVector1.deserializationError();
                        return false;
                    }

                    if(!_directionVector2.deserialize(jsonObject.value("directionVector2").toObject())) {
                        _deserializationError = _directionVector2.deserializationError();
                        return false;
                    }

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

        Vector3D<NumberType> _positionVector;
        Vector3D<NumberType> _directionVector1;
        Vector3D<NumberType> _directionVector2;
    };
    typedef Plane3D<double> RealPlane3D;
} // namespace Glee3D;

#endif // G3D_PLANE3D_H
