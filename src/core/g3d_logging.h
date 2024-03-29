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

#ifndef G3D_LOGGING_H
#define G3D_LOGGING_H

// Own includes
#include "g3d_log.h"

// Qt includes
#include <QString>

namespace Glee3D {

class Logging {
public:
    enum NotificationEvents {
        None        = 0x00,
        OnCreate    = 0x01,
        OnDestroy   = 0x02
    };

    Logging(QString className,
            NotificationEvents notificationEvents = None) :
        _className(className),
        _notificationEvents(notificationEvents) {
        if(_notificationEvents & OnCreate) {
            information("Created object.");
        }
    }

    virtual ~Logging() {
        if(_notificationEvents & OnDestroy) {
            information("Destroyed object.");
        }
    }

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
    NotificationEvents _notificationEvents;
};

}

#endif // G3D_LOGGING_H
