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

#ifndef G3D_RGBACOLOR_H
#define G3D_RGBACOLOR_H

// Own includes
#include "io/g3d_serializable.h"

namespace Glee3D {
    /**
      * @struct RgbaColor
      * @author Jacob Dawid (jacob.dawid@omg-it.works)
      * @date 02.12.2012
      * Defines a color after the rgba color model.
      */
    class RgbaColor : public Serializable {
    public:
        /** Initialization of color struct. */
        RgbaColor() {
            _red = 0.0;
            _green = 0.0;
            _blue = 0.0;
            _alpha = 1.0;
        }

        /** Initialization of color struct. */
        RgbaColor(float red, float green, float blue, float alpha) {
            _red = red;
            _green = green;
            _blue = blue;
            _alpha = alpha;
        }

        /** @overload */
        QString className() {
            return "RgbaColor";
        }

        /** @overload */
        QJsonObject serialize() {
            QJsonObject jsonObject;
            jsonObject["class"] = className();
            jsonObject["red"]   = _red;
            jsonObject["green"] = _green;
            jsonObject["blue"]  = _blue;
            jsonObject["alpha"] = _alpha;
            return jsonObject;
        }

        /** @overload */
        bool deserialize(QJsonObject jsonObject) {
            if(!jsonObject.contains("class")) {
                _deserializationError = Serializable::NoClassSpecified;
                return false;
            }

            if(jsonObject.contains("red")
            && jsonObject.contains("green")
            && jsonObject.contains("blue")
            && jsonObject.contains("alpha")) {
                if(jsonObject["class"] == className()) {
                    _red    = (float)jsonObject["red"].toDouble();
                    _green  = (float)jsonObject["green"].toDouble();
                    _blue   = (float)jsonObject["blue"].toDouble();
                    _alpha  = (float)jsonObject["alpha"].toDouble();

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

        float _red;
        float _green;
        float _blue;
        float _alpha;
    };

} // namespace Glee3D

#endif // G3D_RGBACOLOR_H
