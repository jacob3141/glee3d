///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of glee3d.                                           //
//    Copyright (C) 2012-2014 Jacob Dawid, jacob.dawid@cybercatalyst.net     //
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

#ifndef G3D_SERIALIZABLE_H
#define G3D_SERIALIZABLE_H

// Qt includes
#include <QJsonObject>

namespace Glee3D {
    class Serializable {
    public:
        enum DeserializationError {
            NoError,
            NoClassSpecified,
            WrongClass,
            MissingElements
        };

        virtual ~Serializable() { }

        DeserializationError deserializationError() {
            return _deserializationError;
        }

        virtual QString className() = 0;
        virtual QJsonObject serialize() = 0;
        virtual bool deserialize(QJsonObject json) = 0;

    protected:
        DeserializationError _deserializationError;
    };

} // namespace Glee3D

#endif // G3D_SERIALIZABLE_H
