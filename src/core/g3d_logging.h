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

#ifndef G3D_LOGGING_H
#define G3D_LOGGING_H

// Own includes
#include "g3d_log.h"

// Qt includes
#include <QString>

namespace Glee3D {

class Logging {
public:
    Logging(QString className) : _className(className) { information("Created object."); }
    virtual ~Logging() { information("Destroyed object."); }

    virtual QString identifier() { return QString("%1").arg((long)this); }

    void information(QString message) {
        Log::instance()->information(addObjectInfo(message));
    }

    void warning(QString message) {
        Log::instance()->warning(addObjectInfo(message));
    }

    void error(QString message) {
        Log::instance()->error(addObjectInfo(message));
    }

private:
    QString addObjectInfo(QString message) {
        return QString("[%1(%2)] %3").arg(_className).arg(identifier()).arg(message);
    }

    QString _className;
};

}

#endif // G3D_LOGGING_H
