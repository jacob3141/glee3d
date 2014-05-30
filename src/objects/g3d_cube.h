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

#ifndef G3D_CUBE_H
#define G3D_CUBE_H

// Own includes
#include "core/g3d_object.h"

/**
 * @namespace Glee3D
 * Namespace for the Glee3D project.
 */
namespace Glee3D {
    /**
      * @class Cube
      * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
      * @date 02.12.2012
      */
    class Cube : public Object {
    public:
        /** Creates a new cube. */
        Cube();

        /** Destructor. */
        virtual ~Cube();

        /**
         * Generates a new cube based on the given parameters.
         * @param edgeLength Base edge length.
         * @param scaleX Scaling factor in x direction.
         * @param scaleY Scaling factor in y direction.
         * @param scaleZ Scaling factor in z direction.
         */
        void generate(double edgeLength, double scaleX = 1.0, double scaleY = 1.0, double scaleZ = 1.0);
    };
} // namespace Glee3D

#endif // G3D_CUBE_H
