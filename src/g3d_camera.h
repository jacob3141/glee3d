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

#ifndef G3D_CAMERA_H
#define G3D_CAMERA_H

// Own includes
#include "g3d_anchored.h"
#include "g3d_matrixstate.h"

namespace Glee3D {
/**
  * @class Camera
  * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
  * @date 02.12.2012
  * @brief Declares a camera in the virtual space.
  */
class Camera : public Anchored {
public:
    /**
      * @brief Creates a new camera.
      */
    Camera();

    MatrixState matrixState();

    /**
      * Turns the camera so it looks at the specified point defined
      * in the virtual space.
      * @param target Point at which the camera is directed.
      */
    void setLookAt(RealVector3D target);

    /** @returns Look-At-vector. */
    RealVector3D lookAt();

    /**
      * Sets the up-vector of the camera.
      * @param up Up-vector.
      */
    void setUp(RealVector3D up);

    /** @returns Up-vector. */
    RealVector3D up();

    /**
      * Sets the aspect ratio for this camera.
      * @param width Width of aspect ratio.
      * @param height Height of aspect ratio.
      */
    void setAspectRatio(int width, int height);

    void setFieldOfView(double fieldOfView);

    void moveLookAt(RealVector3D delta);

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

    RealVector3D _lookAt;
    RealVector3D _up;
};

} // namespace Glee3D

#endif // G3D_CAMERA_H
