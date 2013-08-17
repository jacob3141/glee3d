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

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

// Own includes
#include "matrixstate.h"
#include "rgbacolor.h"

// OpenGL includes
#include <GL/glew.h>

// Qt includes
#include <QRect>

namespace Glee3D {
/**
  * @class FrameBuffer
  * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
  * @date 02.12.2012
  * Makes it easier to handle ramebuffers by hiding a lot of OpenGL's
  * details in a single object.
  */
class FrameBuffer {
public:
    /** @enum FrameBufferProperties */
    enum FrameBufferProperties {
        DepthBuffer         = 1 << 0,
        FloatingPointFormat = 1 << 1,
        LinearFiltering     = 1 << 2
    };

    /**
      * Creates a new frame buffer object.
      * @param width Width of the framebuffer object.
      * @param height Height of the framebuffer object.
      * @param properties Framebuffer properties.
      */
    FrameBuffer(int width,
                int height,
                int properties = FloatingPointFormat | LinearFiltering);

    /**
      * Acquires that framebuffer object as a drawing target. All
      * consecutive drawing calls to OpenGL will be directed to the
      * non-visible memory buffer until release() is called.
      * @see release()
      */
    void acquire();

    /** Releases that framebuffer object, defaulting to the OpenGL
      * visible memory.
      * @see acquire()
      */
    void release();

    /** Binds the framebuffer contents as a texture. */
    void bindTexture();

    /** @deprecated */
    void copy(int width, int height);

    /** Clears the framebuffer object. */
    void clear();

    /** Sets the clear color. */
    void setClearColor(RgbaColor color);

    /** @returns the clear color. */
    RgbaColor clearColor();

    /** @returns the width of the framebuffer. */
    GLsizei width();

    /** @returns the height of the framebuffer. */
    GLsizei height();

    /** @returns properties of this framebuffer. */
    int properties();

private:
    int _properties;
    GLsizei _width;
    GLsizei _height;

    RgbaColor _clearColor;
    MatrixState _previousMatrixState;

    GLuint _texture;
    GLuint _depthBuffer;
    GLuint _frameBufferObject;
};

} // namespace Glee3D

#endif // FRAMEBUFFER_H
