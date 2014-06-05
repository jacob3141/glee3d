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
#include "g3d_skybox.h"
#include "g3d_scene.h"

// GL utilities includes
#include "GL/glu.h"

namespace Glee3D {
    SkyBox::SkyBox()
        : Renderable() {
    }

    void SkyBox::setTexture(Plane plane, QString textureId) {
        Material *material = new Material();
        material->setAmbientReflection(RgbaColor(1.0, 1.0, 1.0, 1.0));
        material->setDiffuseReflection(RgbaColor(0.0, 0.0, 0.0, 1.0));
        material->setSpecularReflection(RgbaColor(0.0, 0.0, 0.0, 1.0));
        material->setTextureId(textureId);
        Material *existingSurface = _materials.value(plane, 0);
        if(existingSurface)
            delete existingSurface;
        _materials[plane] = material;
    }

    void SkyBox::render(RenderMode renderMode) {
        Q_UNUSED(renderMode);
        glPushAttrib(GL_ENABLE_BIT);
        glEnable(GL_TEXTURE_2D);
        glDisable(GL_CULL_FACE);
        glDisable(GL_LIGHTING);
        glDisable(GL_BLEND);

        glColor4f(1,1,1,1);
        double k = 10000.0f;

        _materials[BackX]->activate();
        const GLfloat vertexDataBackX[] = {
            (float)-k, (float) k, (float)-k,
            (float)-k, (float) k, (float) k,
            (float)-k, (float)-k, (float) k,
            (float)-k, (float)-k, (float)-k,
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
            (float) k, (float)-k, (float)-k,
            (float) k, (float)-k, (float) k,
            (float) k, (float) k, (float) k,
            (float) k, (float) k, (float)-k
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
            (float) k, (float)-k, (float)-k,
            (float) k, (float)-k, (float) k,
            (float)-k, (float)-k, (float) k,
            (float)-k, (float)-k, (float)-k
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
            (float) k, (float) k, (float)-k,
            (float) k, (float) k, (float) k,
            (float)-k, (float) k, (float) k,
            (float)-k, (float) k, (float)-k
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
            (float) k, (float)-k, (float)-k,
            (float) k, (float) k, (float)-k,
            (float)-k, (float) k, (float)-k,
            (float)-k, (float)-k, (float)-k
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
            (float)-k, (float)-k, (float) k,
            (float)-k, (float) k, (float) k,
            (float) k, (float) k, (float) k,
            (float) k, (float)-k, (float) k
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

} // namespace Glee3D
