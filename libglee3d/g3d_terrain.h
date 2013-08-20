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

#ifndef G3D_TERRAIN_H
#define G3D_TERRAIN_H

// Own includes
#include "g3d_object.h"

// Qt includes
#include <QString>

namespace Glee3D {
    /**
      * @class Terrain
      * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
      * @date 18.08.2013
      */
    class Terrain : public Object {
    public:
        explicit Terrain(Entity *parent = 0);
        virtual ~Terrain();

        void generateFromHeightmap(QString fileName);

    protected:

    };
} // namespace Glee3D

#endif // G3D_TERRAIN_H
