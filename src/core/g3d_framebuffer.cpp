///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of glee3d.                                           //
//    Copyright (C) 2012-2014 Jacob Dawid, jacob.dawid@cybercatalyst.net     //
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

// Own includes
#include "g3d_framebuffer.h"
#include "g3d_matrixstate.h"

// Standard includes
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
        //std::cout << "Successfully created framebuffer." << std::endl;
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

void FrameBuffer::target() {
    _previousMatrixState.save();
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferObject);

    if(_properties & DepthBuffer) {
        glEnable(GL_DEPTH_TEST);
    }
}

void FrameBuffer::release() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    _previousMatrixState.restore();
}

void FrameBuffer::bindTexture() {
    glBindTexture(GL_TEXTURE_2D, _texture);
}

void FrameBuffer::copy(int width, int height) {
    MatrixState matrixState;
    matrixState.save();

    glPushAttrib(GL_ENABLE_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -10, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -6.0);

    bindTexture();
    glDisable(GL_DEPTH_TEST);

    // Create a fullscreen quad. Pass it a z parameter of 1.0 to ensure it is
    // always on top of the target.
    const GLfloat vertices[] = {
        0.0f,            0.0f,             1.0f,
        (GLfloat)_width, 0.0f,             1.0f,
        (GLfloat)_width, (GLfloat)_height, 1.0f,
        0.0f,            (GLfloat)_height, 1.0f
    };

    // All vertices have to face upwards from the target.
    const GLfloat normals[] = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };

    // Set the texture coordinates.
    const GLfloat textureCoordinates[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    // Usually, this will be handled my materials, but since we need to deal
    // with our own texture here, let's save the overhead of dealing with
    // material objects set the right values inline.
    float ambientReflection[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float diffuseReflection[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    float specularReflection[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    float emission[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientReflection);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseReflection);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularReflection);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);

    // Draw the quad.
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinates);
    glNormalPointer(GL_FLOAT, 0, normals);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    matrixState.restore();
    glPopAttrib();
}

void FrameBuffer::clear() {
    target();
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
