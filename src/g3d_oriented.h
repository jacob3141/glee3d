///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of glee3d.                                           //
//    Copyright (C) 2014 Jacob Dawid, jacob.dawid@cybercatalyst.net          //
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

#ifndef G3D_ORIENTED_H
#define G3D_ORIENTED_H

// Own includes
#include "g3d_vector3d.h"

namespace Glee3D {

    class Oriented {
    public:
        Oriented();
        virtual ~Oriented();

        /** Sets the rotation for this object.
          * @param value Vector containing angles for all three axes in degrees.
          */
        void setRotation(RealVector3D value);

        /** Rotates the object based on the current rotation state.
          * @param delta Vector containing angles for all three axes in degrees.
          */
        void rotate(RealVector3D delta);

        /** @returns the object's rotation for all three axes in degrees. */
        RealVector3D rotation();

        /** @returns the object's front-vector. */
        RealVector3D front();

        /** @returns the object's up-vector. */
        RealVector3D up();

        /**
          * Sets the up-vector of the camera.
          * @param up Up-vector.
          */
        //void setUp(RealVector3D up);

    protected:
        RealVector3D _rotation;
        RealVector3D _up;
    };

} // namespace Glee3D

#endif // G3D_ORIENTED_H
