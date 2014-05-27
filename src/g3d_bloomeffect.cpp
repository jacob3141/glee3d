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

// Own includes
#include "g3d_bloomeffect.h"
#include "g3d_matrixstate.h"

// GL extension wrangler includes
#include "GL/glew.h"

// Standard includes
#include <iostream>
#include <math.h>
#include <cstdio>

#define BUFFER_WIDTH  128
#define BUFFER_HEIGHT 128

GLfloat lightblue[4] = {122, 143, 248, 0};

namespace Glee3D {
BloomEffect::BloomEffect()
    : PostRenderEffect() {
}

BloomEffect::~BloomEffect() {

}

void BloomEffect::initialize() {
    _filterDepth = 4;
    _kernelSize = 5;

    // Generate Gauss-Kernel
    float coefficient = 1 / sqrt(2 * M_PI);
    _filterKernel = new float[_kernelSize];
    for(int i = 0; i < _kernelSize; i++) {
        float pos = (float)i - 0.5 * (float)_kernelSize;
        _filterKernel[i] = coefficient * exp(-0.5 * pos * pos);
    }

    _passA = new FrameBuffer*[_filterDepth];
    _passB = new FrameBuffer*[_filterDepth];

    _blitProgram.compile(
        "void main(void)"
        "{"
        "    gl_TexCoord[0] = gl_MultiTexCoord0;"
        "    gl_Position    = ftransform();"
        "}"
    , Program::Vertex);

    _blitProgram.compile(
        "uniform sampler2D source;"
        "uniform vec4 bkgd;"
        "void main(void)"
        "{"
        "    vec4 t = texture2D(source, gl_TexCoord[0].st);"
        "    gl_FragColor = t + bkgd;"
        "}"
    , Program::Fragment);
    _blitProgram.link();

    _combineProgram.compile(
        "void main(void)"
        "{"
        "    gl_TexCoord[0] = gl_MultiTexCoord0;"
        "    gl_Position    = ftransform();"
        "}"
    , Program::Vertex);

    _combineProgram.compile(
         "uniform sampler2D Pass0;\n"
         "uniform sampler2D Pass1;\n"
         "uniform sampler2D Pass2;\n"
         "uniform sampler2D Pass3;\n"
         "uniform vec4 bkgd;\n"
         "void main(void)\n"
         "{\n"
         "    vec4 t0 = texture2D(Pass0, gl_TexCoord[0].st);\n"
         "    vec4 t1 = texture2D(Pass1, gl_TexCoord[0].st);\n"
         "    vec4 t2 = texture2D(Pass2, gl_TexCoord[0].st);\n"
         "    vec4 t3 = texture2D(Pass3, gl_TexCoord[0].st);\n"
         "    gl_FragColor = t0 + t1 + t2 + t3 + bkgd;\n"
         "}\n"
    , Program::Fragment);

    _combineProgram.link();

//    _filterProgram.compile(GLSL(
//        void main(void)
//        {
//            gl_TexCoord[0] = gl_MultiTexCoord0;
//            gl_Position    = ftransform();
//        }
//    ), Program::Vertex);

//    _filterProgram.compile(GLSL(
//        uniform sampler2D source;
//        uniform float coefficients[5];
//        uniform vec2 offsets[5];
//        void main(void)
//        {
//            float d = 0.1;
//            vec4 c = vec4(0, 0, 0, 0);
//            vec2 tc = gl_TexCoord[0].st;
//            c += coefficients[0] * texture2D(source, tc + offsets[0]);
//            c += coefficients[1] * texture2D(source, tc + offsets[1]);
//            c += coefficients[2] * texture2D(source, tc + offsets[2]);
//            c += coefficients[3] * texture2D(source, tc + offsets[3]);
//            c += coefficients[4] * texture2D(source, tc + offsets[4]);
//            gl_FragColor = c;
//        }
//    ), Program::Fragment);
//    _filterProgram.link();


    GLsizei width = BUFFER_WIDTH;
    GLsizei height = BUFFER_HEIGHT;
    for(int p = 0; p < _filterDepth; p++) {
       _passA[p] = new FrameBuffer(width, height);
       width = width >> 1;
       height = height >> 1;
    }

    width = BUFFER_WIDTH;
    height = BUFFER_HEIGHT;
    for(int p = 0; p < _filterDepth; p++) {
       _passB[p] = new FrameBuffer(width, height);
       width = width >> 1;
       height = height >> 1;
    }
}

void BloomEffect::blur(FrameBuffer **from, FrameBuffer **to, Direction dir) {
    // Set up the filter.
    _filterProgram.insert();
    glUniform1i(_filterProgram.glUniformLocation("source"), 0);
    glUniform1fv(_filterProgram.glUniformLocation("coefficients"), _filterDepth, _filterKernel);
    GLint offsetsLocation = _filterProgram.glUniformLocation("offsets");

    // Perform the blurring.
    for(int pass = 0; pass < _filterDepth; pass++) {
        float offsets[_kernelSize * 2];
        float offset = 1.0f / (float)from[pass]->width();

        for(int c = 0; c < _kernelSize; c++) {
            offsets[c * 2 + 0] = (dir == HORIZONTAL) ? offset * (c - 2) : 0;
            offsets[c * 2 + 1] = (dir == VERTICAL)   ? offset * (c - 2) : 0;
        }

        to[pass]->acquire();
        glUniform2fv(offsetsLocation, _kernelSize, offsets);
        from[pass]->copy(to[pass]->width(), to[pass]->height());
        to[pass]->release();
    }
}

void BloomEffect::apply(FrameBuffer *frameBuffer) {
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    // Downsample the scene into the source materials.
    frameBuffer->bindTexture();
    for(int p = 1; p < _filterDepth; p++) {
      _passA[p]->acquire();

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, _passA[p]->width(), 0, _passA[p]->height(), -10, 10);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0, 0, -6.0);

      glBegin(GL_QUADS);
          glTexCoord2i(0, 0); glVertex2i(-1, -1);
          glTexCoord2i(1, 0); glVertex2i(1, -1);
          glTexCoord2i(1, 1); glVertex2i(1, 1);
          glTexCoord2i(0, 1); glVertex2i(-1, 1);
      glEnd();
    }

    // Perform the horizontal blurring pass.
    blur(_passA, _passB, HORIZONTAL);

    // Draw left portion of window.
    _blitProgram.insert();
    glUniform4fv(_blitProgram.glUniformLocation("bkgd"), 1, lightblue);
    glUniform1i(_blitProgram.glUniformLocation("source"), 0);

    frameBuffer->acquire();
    frameBuffer->clear();

    MatrixState matrixState;
    matrixState.save();
    for(int p = 0; p < _filterDepth; p++) {
      _passA[p]->copy(frameBuffer->width(), frameBuffer->height());
      glTranslatef(0, (GLfloat) _passA[p]->height() + 1, 0);
    }
    matrixState.load();
    glTranslatef((GLfloat) _passA[0]->width() + 1, 0, 0);
    for(int p = 0; p < _filterDepth; p++) {
      _passB[p]->copy(frameBuffer->width(), frameBuffer->height());
      glTranslatef(0, (GLfloat) _passB[p]->height() + 1, 0);
    }

    // Perform the vertical blurring pass.
    blur(_passB, _passA, VERTICAL);

    // Draw right portion of window.
    frameBuffer->acquire();

    glTranslatef((GLfloat) 2 * _passB[0]->width() + 2, 0, 0);
    _blitProgram.insert();

    matrixState.save();
    for(int p = 0; p < _filterDepth; p++) {
      _passA[p]->copy(frameBuffer->width(), frameBuffer->height());
      glTranslatef(0, (GLfloat) _passA[p]->height() + 1, 0);
    }
    matrixState.load();
    glTranslatef((GLfloat) _passA[0]->width() + 1, 0, 0);

    _combineProgram.insert();
    glUniform4fv(_combineProgram.glUniformLocation("bkgd"), 1, lightblue);

    for(int p = 0; p < _filterDepth; p++) {
      glActiveTexture(GL_TEXTURE0 + p);
      _passA[p]->bindTexture();
      glUniform1i(_combineProgram.glUniformLocation(QString("Pass%1").arg(p)), p);
    }

    glBegin(GL_QUADS);
    glTexCoord2i(0, 0); glVertex2i(0, 0);
    glTexCoord2i(1, 0); glVertex2i(_passA[0]->width(), 0);
    glTexCoord2i(1, 1); glVertex2i(_passA[0]->width(), _passA[0]->height());
    glTexCoord2i(0, 1); glVertex2i(0, _passA[0]->height());
    glEnd();

    _combineProgram.eject();

    for(int p = 0; p < _filterDepth; p++) {
      glActiveTexture(GL_TEXTURE0 + p);
      glDisable(GL_TEXTURE_2D);
    }
    glActiveTexture(GL_TEXTURE0);

    frameBuffer->release();
}

} // namespace Glee3D
