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

#ifndef G3D_ANCHORED_H
#define G3D_ANCHORED_H

// Own includes
#include "math/g3d_vector3d.h"

/**
 * @namespace Glee3D
 * Namespace for the Glee3D project.
 */
namespace Glee3D {
    /**
      * @class Anchored
      * @author Jacob Dawid (jacob.dawid@omg-it.works)
      * @date 02.12.2012
      * An anchored widgets owns an anchor position, that means that a position
      * can be assigned in the virtual space.
      */
    class Anchored {
    public:
        /** Creates a new entity.
          * @param parent Parent entity.
          */
        Anchored();

        /** @returns Position of this entity in relation to its parent. */
        Vector3D position();

        /** Set the position of this entitiy in relation to its parent.
          * @param position Position that shall be set for this entity.
          */
        void setPosition(Vector3D position);

        /** Moves this entity in relation to its parent.
          * @param delta Distance that this entity shall be moved.
          */
        void move(Vector3D delta);

        void applyTranslation();

    protected:
        /** Position for this widget. */
        Vector3D _position;
    };
} // namespace Glee3D

#endif // G3D_ANCHORED_H
