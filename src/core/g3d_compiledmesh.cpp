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

// Own includes
#include "g3d_compiledmesh.h"

namespace Glee3D {
    CompiledMesh::CompiledMesh(Mesh *mesh)
        : Logging("CompiledMesh") {
        if(!mesh) {
            Q_ASSERT(false);
            error("A compiled mesh cannot be created with a null mesh.");
            return;
        }
        allocateMemory(mesh->_triangleCount);

        // Determine collision radius
        double maxDistance = 0.0;
        for(int i = 0; i < mesh->_vertexCount; i++) {
            double length = mesh->_vertices[i].length();
            if(length > maxDistance) {
                maxDistance = length;
            }
        }
        _collisionRadius = maxDistance;

        // Compute surface normals.
        Vector3D *surfaceNormals = new Vector3D[mesh->_triangleCount];
        for(int i = 0; i < mesh->_triangleCount; i++) {
            int i1 = mesh->_triangles[i]._indices[0];
            int i2 = mesh->_triangles[i]._indices[1];
            int i3 = mesh->_triangles[i]._indices[2];

            // User the cross product to determine the normal of a material.
            surfaceNormals[i] = ((mesh->_vertices[i2] - mesh->_vertices[i1])
                    .crossProduct(mesh->_vertices[i3] - mesh->_vertices[i1])).normalize();
        }

        // Calculate vertex joint normals for smooth shadowing
        Vector3D vertexJointNormal[mesh->_vertexCount];
        for(int i = 0; i < mesh->_vertexCount; i++) {
            Vector3D cumulatedJointNormal;
            for(int j = 0; j < mesh->_triangleCount; j++) {
                if(mesh->_triangles[j]._indices[0] == i
                || mesh->_triangles[j]._indices[1] == i
                || mesh->_triangles[j]._indices[2] == i) {
                    cumulatedJointNormal += surfaceNormals[j];
                }
            }
            vertexJointNormal[i] = cumulatedJointNormal.normalize();
        }
        delete[] surfaceNormals;

        int i;
        for(i = 0; i < mesh->_triangleCount; i++) {
            int i1 = mesh->_triangles[i]._indices[0];
            int i2 = mesh->_triangles[i]._indices[1];
            int i3 = mesh->_triangles[i]._indices[2];

            _vertices[i * 9 + 0] = mesh->_vertices[i1].x();
            _vertices[i * 9 + 1] = mesh->_vertices[i1].y();
            _vertices[i * 9 + 2] = mesh->_vertices[i1].z();
            _vertices[i * 9 + 3] = mesh->_vertices[i2].x();
            _vertices[i * 9 + 4] = mesh->_vertices[i2].y();
            _vertices[i * 9 + 5] = mesh->_vertices[i2].z();
            _vertices[i * 9 + 6] = mesh->_vertices[i3].x();
            _vertices[i * 9 + 7] = mesh->_vertices[i3].y();
            _vertices[i * 9 + 8] = mesh->_vertices[i3].z();

            _texCoords[i * 6 + 0] = mesh->_textureCoordinates[i1].x();
            _texCoords[i * 6 + 1] = mesh->_textureCoordinates[i1].y();
            _texCoords[i * 6 + 2] = mesh->_textureCoordinates[i2].x();
            _texCoords[i * 6 + 3] = mesh->_textureCoordinates[i2].y();
            _texCoords[i * 6 + 4] = mesh->_textureCoordinates[i3].x();
            _texCoords[i * 6 + 5] = mesh->_textureCoordinates[i3].y();

            _normals[i * 9 + 0] = vertexJointNormal[i1].x();
            _normals[i * 9 + 1] = vertexJointNormal[i1].y();
            _normals[i * 9 + 2] = vertexJointNormal[i1].z();
            _normals[i * 9 + 3] = vertexJointNormal[i2].x();
            _normals[i * 9 + 4] = vertexJointNormal[i2].y();
            _normals[i * 9 + 5] = vertexJointNormal[i2].z();
            _normals[i * 9 + 6] = vertexJointNormal[i3].x();
            _normals[i * 9 + 7] = vertexJointNormal[i3].y();
            _normals[i * 9 + 8] = vertexJointNormal[i3].z();
        }

        postCompile();
    }

    CompiledMesh::~CompiledMesh() {
        glDeleteBuffers(1, &_normalsVBOHandle);
        glDeleteBuffers(1, &_verticesVBOHandle);
        glDeleteBuffers(1, &_texCoordsVBOHandle);
    }

    void CompiledMesh::allocateMemory(int triangleCount) {
        // Each triangle has three vertices.
        _count = triangleCount * 3;

        // Each triangle has three normals, of which each has three
        // coordinate values.
        _normals = new double[_count * 3];

        // Each triangle has three vertices, of which each has three
        // coordinate values.
        _vertices = new double[_count * 3];

        // Each triangle has three vertices, of which each has two
        // coordinate values.
        _texCoords = new double[_count * 2];
    }

    void CompiledMesh::postCompile() {
        // Generate vertex buffer obejcts
        glGenBuffers(1, &_normalsVBOHandle);
        glGenBuffers(1, &_verticesVBOHandle);
        glGenBuffers(1, &_texCoordsVBOHandle);

        // Upload vertex data to graphics card
        glBindBuffer(GL_ARRAY_BUFFER, _normalsVBOHandle);
        glBufferData(GL_ARRAY_BUFFER, sizeof(double) * _count * 3, _normals, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, _verticesVBOHandle);
        glBufferData(GL_ARRAY_BUFFER, sizeof(double) * _count * 3, _vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, _texCoordsVBOHandle);
        glBufferData(GL_ARRAY_BUFFER, sizeof(double) * _count * 2, _texCoords, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Free memory
        delete[] _normals;
        delete[] _vertices;
        delete[] _texCoords;
    }

    void CompiledMesh::render() {
        glBindBuffer(GL_ARRAY_BUFFER, _verticesVBOHandle);
        glVertexPointer(3, GL_DOUBLE, 0, 0L);
        glBindBuffer(GL_ARRAY_BUFFER, _texCoordsVBOHandle);
        glTexCoordPointer(2, GL_DOUBLE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, _normalsVBOHandle);
        glNormalPointer(GL_DOUBLE, 0, 0L);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        glDrawArrays(GL_TRIANGLES, 0, _count * 3);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    double CompiledMesh::collisionRadius() {
        return _collisionRadius;
    }

} // namespace Glee3D
