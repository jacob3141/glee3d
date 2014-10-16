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
    template <typename NumberType>
    class Line3D : public Serializable {
    public:
        Vector3D<NumberType> point(NumberType alpha) const {
            return _positionVector + _directionVector * alpha;
        }

        QString className() {
            return "Line3D";
        }

        QJsonObject serialize() {
            QJsonObject jsonObject;
            jsonObject["class"] = className();
            jsonObject["positionVector"] = _positionVector.serialize();
            jsonObject["directionVector"] = _directionVector.serialize();
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

                    if(!_directionVector.deserialize(jsonObject.value("directionVector").toObject())) {
                        _deserializationError = _directionVector.deserializationError();
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
        Vector3D<NumberType> _directionVector;
    };

    typedef Line3D<double> RealLine3D;
} // namespace Glee3D

#endif // G3D_LINE3D_H
