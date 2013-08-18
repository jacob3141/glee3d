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

#include "skybox.h"
#include "camera.h"
#include "scene.h"
#include "GL/glu.h"

namespace Glee3D {
    SkyBox::SkyBox()
        : Object() {
    }

    void SkyBox::loadTexture(Plane plane, QString fileName, Display *display) {
        Material *material = new Material();
        material->setAmbientReflection(RgbaColor(1.0, 1.0, 1.0, 1.0));
        material->setDiffuseReflection(RgbaColor(0.0, 0.0, 0.0, 1.0));
        material->setSpecularReflection(RgbaColor(0.0, 0.0, 0.0, 1.0));
        material->loadTexture(fileName, *display);
        Material *existingSurface = _materials.value(plane, 0);
        if(existingSurface)
            delete existingSurface;
        _materials[plane] = material;
    }

    void SkyBox::render() {

        glPushAttrib(GL_ENABLE_BIT);
        glEnable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glDisable(GL_LIGHTING);
        glDisable(GL_BLEND);

        glColor4f(1,1,1,1);
        double k = 80.0f;

        _materials[BackX]->activate();
        const GLfloat vertexDataBackX[] = {
            -k,  k, -k,
            -k,  k,  k,
            -k, -k,  k,
            -k, -k, -k,
        };

        const GLfloat textureCoordinatesBackX[] = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        };

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertexDataBackX);
        glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinatesBackX);
        glDrawArrays(GL_QUADS, 0, 4);

        _materials[FrontX]->activate();
        const GLfloat vertexDataFrontX[] = {
            k, -k, -k,
            k, -k,  k,
            k,  k,  k,
            k,  k, -k
        };

        const GLfloat textureCoordinatesFrontX[] = {
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f
        };

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertexDataFrontX);
        glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinatesFrontX);
        glDrawArrays(GL_QUADS, 0, 4);


        _materials[BackY]->activate();
        const GLfloat vertexDataBackY[] = {
             k, -k, -k,
             k, -k,  k,
            -k, -k,  k,
            -k, -k, -k
        };

        const GLfloat textureCoordinatesBackY[] = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        };

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertexDataBackY);
        glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinatesBackY);
        glDrawArrays(GL_QUADS, 0, 4);

        _materials[FrontY]->activate();
        const GLfloat vertexDataFrontY[] = {
             k,  k, -k,
             k,  k,  k,
            -k,  k,  k,
            -k,  k, -k
        };

        const GLfloat textureCoordinatesFrontY[] = {
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f
        };

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertexDataFrontY);
        glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinatesFrontY);
        glDrawArrays(GL_QUADS, 0, 4);

        _materials[BackZ]->activate();
        const GLfloat vertexDataBackZ[] = {
             k, -k, -k,
             k,  k, -k,
            -k,  k, -k,
            -k, -k, -k
        };

        const GLfloat textureCoordinatesBackZ[] = {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f
        };

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertexDataBackZ);
        glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinatesBackZ);
        glDrawArrays(GL_QUADS, 0, 4);

        _materials[FrontZ]->activate();
        const GLfloat vertexDataFrontZ[] = {
            -k, -k,  k,
            -k,  k,  k,
             k,  k,  k,
             k, -k,  k
        };

        const GLfloat textureCoordinatesFrontZ[] = {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f
        };

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertexDataFrontZ);
        glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinatesFrontZ);
        glDrawArrays(GL_QUADS, 0, 4);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        glPopAttrib();
        glPopMatrix();
    }

}
