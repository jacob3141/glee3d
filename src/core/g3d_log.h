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

#ifndef G3D_LOG_H
#define G3D_LOG_H

// Qt includes
#include <QString>

namespace Glee3D {

/**
 * Central log singleton. Usually, you should never deal with this class,
 * rather you are supposed to subclass the Logging class which will offer you
 * logging methods related to each instance.
 * @see Logging
 */
class Log
{
friend class Logging;
public:
    static Log *instance();

protected:
    void information(QString message);
    void warning(QString message);
    void error(QString message);

private:

    Log();
};

}

#endif // G3D_LOG_H
