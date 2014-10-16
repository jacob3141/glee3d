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

// Own includes
#include "g3d_log.h"

// Qt includes
#include <QDebug>

namespace Glee3D {

Log *Log::instance()
{
    static Log* log = new Log();
    return log;
}

Log::Log()
{
}

void Log::information(QString message)
{
    qDebug() << "Info: " << message;
}

void Log::warning(QString message)
{
    qDebug() << "Warning: " << message;
}

void Log::error(QString message)
{
    qDebug() << "Error: " << message;
}


} // namespace Glee3D
