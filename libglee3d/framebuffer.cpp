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

#include "framebuffer.h"
#include <iostream>

namespace Glee3D {

FrameBuffer::FrameBuffer(int width, int height, int properties) {
    _properties = properties;
    _width = width;
    _height = height;
    _clearColor = RgbaColor(0, 0, 0, 0);

    GLenum internalFormat = (_properties & FloatingPointFormat) ? GL_RGBA16F_ARB : GL_RGBA;
    GLenum type = (_properties & FloatingPointFormat) ? GL_HALF_FLOAT_ARB : GL_UNSIGNED_BYTE;
    GLenum filter = (_properties & LinearFiltering) ? GL_LINEAR : GL_NEAREST;

    // Create framebuffer object.
    _frameBufferObject = 0;
    glGenFramebuffers(1, &_frameBufferObject);
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferObject);

    // create depth renderbuffer
    if(_properties & DepthBuffer) {
        _depthBuffer = 0;
        glGenRenderbuffers(1, &_depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER,
                              GL_DEPTH_COMPONENT,
                              _width, _height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    } else {
        _depthBuffer = 0;
    }

    // create a color texture
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0,
                 internalFormat,
                 _width, _height,
                 0, GL_RGBA, type, 0);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    filter);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    filter);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Attach texture to framebuffer object.
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D, _texture, 0);
    if(_properties & DepthBuffer) {
        // Attach depth buffer to framebuffer object.
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                  GL_DEPTH_ATTACHMENT,
                                  GL_RENDERBUFFER,
                                  _depthBuffer);
    }

    // Release framebuffer object.
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status == GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Successfully created framebuffer." << std::endl;
    } else {
        char enums[][20] = {
            "attachment",         // GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT........... All framebuffer attachment points are 'framebuffer attachment complete'.
            "missing attachment", // GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT....There is at least one image attached to the framebuffer.
            "",                   //
            "dimensions",         // GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT............All attached images have the same width and height.
            "formats",            // GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT...............All images attached to the attachment points COLOR_ATTACHMENT0_EXT through COLOR_ATTACHMENTn_EXT must have the same internal format.
            "draw buffer",        // GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT...........The value of FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT must not be NONE for any color attachment point(s) named by DRAW_BUFFERi.
            "read buffer",        // GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT...........If READ_BUFFER is not NONE, then the value of FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT must not be NONE for the color attachment point named by READ_BUFFER.
            "unsupported format"  // GL_FRAMEBUFFER_UNSUPPORTED_EXT......................The combination of internal formats of the attached images does not violate an implementation-dependent set of restrictions.
        };
        status -= GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT;
        std::cout << "Incomplete framebuffer object due to " << enums[status] << std::endl;
    }
}

void FrameBuffer::acquire() {
    _previousMatrixState.save();
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferObject);

    if(_properties & DepthBuffer) {
        glEnable(GL_DEPTH_TEST);
    }
}

void FrameBuffer::release() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    _previousMatrixState.load();
}

void FrameBuffer::bindTexture() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture);
}

void FrameBuffer::copy(int width, int height) {
    // TODO: Store modelview and projection matrices
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -10, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -6.0);

    bindTexture();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glColor3f(1.0, 1.0, 1.0);

    const GLfloat vertexData[] = {
        0, 0,
        _width, 0,
        _width, _height,
        0, _height
    };

    const GLfloat textureCoordinates[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertexData);
    glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinates);
    glDrawArrays(GL_QUADS, 0, 4);
}

void FrameBuffer::clear() {
    acquire();
    glClearColor(_clearColor._red,
                 _clearColor._green,
                 _clearColor._blue,
                 _clearColor._alpha);
    glClear(GL_COLOR_BUFFER_BIT | ((_properties & DepthBuffer) ? GL_DEPTH_BUFFER_BIT : 0));
}

void FrameBuffer::setClearColor(RgbaColor color) {
    _clearColor = color;
}

RgbaColor FrameBuffer::clearColor() {
    return _clearColor;
}

GLsizei FrameBuffer::width() {
    return _width;
}

GLsizei FrameBuffer::height() {
    return _height;
}

int FrameBuffer::properties() {
    return _properties;
}

} // namespace Glee3D
