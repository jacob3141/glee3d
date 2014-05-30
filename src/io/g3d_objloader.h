///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of glee3d.                                           //
//    Copyright (C) 2012 Jacob Dawid, jacob.dawid@cybercatalyst.net          //
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

#ifndef G3D_OBJLOADER_H
#define G3D_OBJLOADER_H

// Own includes
#include "core/g3d_mesh.h"

// Qt includes
#include <QString>

namespace Glee3D {

/**
  * @class ObjLoader
  * @author Jacob Dawid
  * @date 09.12.2012
  * Loader for Wavefront *.obj-files.
  */
class ObjLoader {
public:
    ObjLoader();

    QList<Mesh*> readObjFile(QString fileName);
private:

};

} // namespace Glee3D

#endif // G3D_OBJLOADER_H
