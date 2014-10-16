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

#ifndef G3D_TEXTURIZABLE_H
#define G3D_TEXTURIZABLE_H

// Own includes
#include "g3d_material.h"

namespace Glee3D {
    class Texturizable {
    public:
        Texturizable() { }
        virtual ~Texturizable() { }

        /** Sets the material.
          * @param material Material that shall be set.
          */
        void setMaterial(Material *material) {
            _material = material;
        }

        /** @returns the material. */
        Material *material() {
            return _material;
        }

    protected:
        Material *_material;
    };
} // namespace Glee3D

#endif // G3D_TEXTURIZABLE_H
