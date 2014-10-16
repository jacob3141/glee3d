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

#ifndef G3D_CAMERA_H
#define G3D_CAMERA_H

// Own includes
#include "g3d_anchored.h"
#include "g3d_matrixstate.h"
#include "g3d_oriented.h"
#include "g3d_logging.h"

/**
 * @namespace Glee3D
 * Namespace for the Glee3D project.
 */
namespace Glee3D {
    /**
      * @class Camera
      * @author Jacob Dawid (jacob.dawid@omg-it.works)
      * @date 02.12.2012
      * @brief Declares a camera in the virtual space.
      */
    class Camera :
        public Anchored,
        public Oriented,
        public Logging {

    public:
        /**
          * @brief Creates a new camera.
          */
        Camera();

        /**
         * Apply the camera matrices. You need to call this to active the
         * camera, ie. you want to start drawing objects as seen by this camera.
         * @return
         */
        void applyCameraMatrix();

        /**
         * Does not apply the camera matrix state, but instead returns the
         * state that would have been active after application.
         * @returns the camera matrix state.
         */
        MatrixState cameraMatrixState();

        /**
          * Sets the aspect ratio for this camera.
          * @param width Width of aspect ratio.
          * @param height Height of aspect ratio.
          */
        void setAspectRatio(int width, int height);

        /**
         * Sets the camera field of view.
         * @param fieldOfView
         */
        void setFieldOfView(double fieldOfView);

        /**
          * Turns the camera so it looks at the specified point defined
          * in the virtual space.
          * @param target Point at which the camera is directed.
          */
        void setLookAt(Vector3D target);

        /** @returns Look-At-vector. */
        Vector3D lookAt();

        /**
          * Moves the camera into the direction that it is looking.
          * @param units Distance that camera shall be moved.
          */
        void moveForward(double units);

    private:
        double _near;
        double _far;
        double _fieldOfView;
        double _aspectRatio;

        Vector3D _lookAt;
    };
} // namespace Glee3D

#endif // G3D_CAMERA_H
