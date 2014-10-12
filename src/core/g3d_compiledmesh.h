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

#ifndef G3D_COMPILEDMESH_H
#define G3D_COMPILEDMESH_H

// Own includes
#include "g3d_mesh.h"
#include "g3d_logging.h"

namespace Glee3D {
    /**
      * @class CompiledMesh
      * @author Jacob Dawid
      * @date 09.12.2012
      * A compiled mesh is a ready-to-render version of a mesh. A mesh
      * has to be compiled into a CompiledMesh, which then has a render()
      * method to draw the mesh.
      */
    class CompiledMesh :
        public Logging {
    public:
        CompiledMesh(Mesh *mesh);
        ~CompiledMesh();

        void allocateMemory(int triangleCount);
        void postCompile();

        void render();

        double collisionRadius();

    private:
        int _count;
        GLfloat *_normals;
        GLfloat *_vertices;
        GLfloat *_texCoords;
        GLuint   _normalsVBOHandle;
        GLuint   _verticesVBOHandle;
        GLuint   _texCoordsVBOHandle;
        double   _collisionRadius;
    };

} // namespace Glee3D

#endif // G3D_COMPILEDMESH_H
