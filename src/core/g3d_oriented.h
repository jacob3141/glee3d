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
#include "math/g3d_vector3d.h"

/**
 * @namespace Glee3D
 * Namespace for the Glee3D project.
 */
namespace Glee3D {
    /**
     * Represents an oriented widget in the virtual space. Widgets may be
     * oriented, but do not necessarily have to have a position.
     */
    class Oriented {
    public:
        /** Initializes a new oriented widget. */
        Oriented();

        /** Destructor. */
        virtual ~Oriented();

        /** Sets the rotation for this widget.
          * @param value Vector containing angles for all three axes in degrees.
          */
        void setRotation(RealVector3D value);

        /** @returns the widget's rotation for all three axes in degrees. */
        RealVector3D rotation();

        /** Rotates the widget based on the current rotation state.
          * @param delta Vector containing angles for all three axes in degrees.
          */
        void rotate(RealVector3D delta);

        /** @returns the widget's side-vector (positive x direction). */
        RealVector3D sideVector();

        /** @returns the widget's front-vector (positive z direction). */
        RealVector3D frontVector();

        /** @returns the widget's up-vector (positive y direction). */
        RealVector3D upVector();

        void applyRotation();

    protected:
        /** This property holds the rotation for the x, y and z axis in degrees. */
        RealVector3D _rotation;
    };

} // namespace Glee3D

#endif // G3D_ORIENTED_H
