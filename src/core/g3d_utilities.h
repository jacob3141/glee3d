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

#ifndef G3D_UTILITIES_H
#define G3D_UTILITIES_H

// Own includes
#include "math/g3d_vector3d.h"
#include "math/g3d_matrix4x4.h"

namespace Glee3D {

/**
 * Utility class.
 */
class Utilities {
public:
    /**
     * Reimplementation of gluPerspective.
     * @param fieldOfView
     * @param aspectRatio
     * @param near
     * @param far
     * @returns the corresponding perspective matrix.
     */
    static Matrix4x4 perspective(double fieldOfView,
                                 double aspectRatio,
                                 double near,
                                 double far);

    /**
     * Reimplementation of glFrustum.
     * @param left
     * @param right
     * @param bottom
     * @param top
     * @param near
     * @param far
     * @returns the perspective matrix.
     */
    static Matrix4x4 frustum(double left,
                             double right,
                             double bottom,
                             double top,
                             double near,
                             double far);

    /**
     * Reimplementation of glOrtho.
     * @param left
     * @param right
     * @param bottom
     * @param top
     * @param near
     * @param far
     * @returns the perspective matrix.
     */
    static Matrix4x4 ortho(double left,
                           double right,
                           double bottom,
                           double top,
                           double near,
                           double far);
    /**
     * Reimplementation of gluLookAt.
     * @param eye Position of the eye.
     * @param center Position that the eye is targeting.
     * @param up Orientation vector that defines like the viewer is headed.
     * @returns the corresponding modelview matrix.
     */
    static Matrix4x4 lookAt(Vector3D eye,
                                           Vector3D center,
                                           Vector3D up);

    static bool unproject(Vector3D window,
                          Matrix4x4 modelMatrix,
                          Matrix4x4 projectionMatrix,
                          const int viewport[4],
                          Vector3D &result);
};

} // namespace Glee3D

#endif // G3D_UTILITIES_H
