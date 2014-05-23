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

#ifndef G3D_MESH_H
#define G3D_MESH_H

// Own includes
#include "g3d_vector2d.h"
#include "g3d_vector3d.h"
#include "g3d_serializable.h"

// Qt includes
#include <QGLWidget>
#include <QJsonArray>

namespace Glee3D {

/**
  * @class CompiledMesh
  * @author Jacob Dawid
  * @date 09.12.2012
  * A compiled mesh is a ready-to-render version of a mesh. A mesh
  * has to be compiled into a CompiledMesh, which then has a render()
  * method to draw the mesh.
  */
class CompiledMesh {
    friend class Mesh;
public:
    CompiledMesh(int triangleCount) {
        // Each triangle has three vertices.
        _count = triangleCount * 3;

        // Each triangle has three normals, of which each has three
        // coordinate values.
        _normals = new GLfloat[_count * 3];

        // Each triangle has three vertices, of which each has three
        // coordinate values.
        _vertices = new GLfloat[_count * 3];

        // Each triangle has three vertices, of which each has two
        // coordinate values.
        _texCoords = new GLfloat[_count * 2];
    }

    ~CompiledMesh() {
        delete[] _normals;
        delete[] _vertices;
        delete[] _texCoords;
    }

    inline void render() {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, _vertices);
        glTexCoordPointer(2, GL_FLOAT, 0, _texCoords);
        glNormalPointer(GL_FLOAT, 0, _normals);
        glDrawArrays(GL_TRIANGLES, 0, _count);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
    }

    inline double collisionRadius() {
        return _collisionRadius;
    }

private:
    int _count;
    GLfloat *_normals;
    GLfloat *_vertices;
    GLfloat *_texCoords;
    double _collisionRadius;
};

struct Triangle : public Serializable {
    Triangle() {
        _indices[0] = 0;
        _indices[1] = 0;
        _indices[2] = 0;
    }

    Triangle(int i1, int i2, int i3) {
        _indices[0] = i1;
        _indices[1] = i2;
        _indices[2] = i3;
    }

    QString className() {
        return "Triangle";
    }

    QJsonObject serialize() {
        QJsonObject jsonObject;
        jsonObject["class"] = className();
        jsonObject["indices_0"] = _indices[0];
        jsonObject["indices_1"] = _indices[1];
        jsonObject["indices_2"] = _indices[2];
        return jsonObject;
    }

    bool deserialize(QJsonObject jsonObject) {
        if(!jsonObject.contains("class")) {
            _deserializationError = Serializable::NoClassSpecified;
            return false;
        }

        if(jsonObject.contains("indices_0")
        && jsonObject.contains("indices_1")
        && jsonObject.contains("indices_2")) {
            if(jsonObject["class"] == className()) {
                _indices[0] = jsonObject["indices_0"].toInt();
                _indices[1] = jsonObject["indices_1"].toInt();
                _indices[2] = jsonObject["indices_2"].toInt();
                _deserializationError = Serializable::NoError;
                return true;
            } else {
                _deserializationError = Serializable::WrongClass;
                return false;
            }
        } else {
            _deserializationError = Serializable::MissingElements;
            return false;
        }
    }

    int _indices[3];
};

/**
  * @class Mesh
  * @author Jacob Dawid
  * @date 09.12.2012
  * Defines a mesh.
  */
class Mesh : public Serializable {
public:
    /**
      * Creates a new mesh.
      */
    Mesh();

    /**
      * Creates a new mesh.
      * @param vertexCount The number of vertices.
      * @param triangleCount The number triangles.
      */
    Mesh(int vertexCount, int triangleCount);

    /** Destructor. */
    ~Mesh();

    /** Creates a new mesh.
      * @param vertexCount The number of vertices.
      * @param triangleCount The number triangles.
      */
    void create(int vertexCount, int triangleCount);

    /**
      * Compiles the mesh into a ready-to-render version.
      * @returns the compiled mesh.
      */
    CompiledMesh *compile();

    /**
      * Sets the vertex data for the specified index.
      * @param index Index of vertex.
      * @param vertex Vertex data.
      */
    void setVertex(int index, RealVector3D vertex);

    /**
      * Sets the triangle for the specified index.
      * @param index Index of triangle.
      * @param triangle Triangle holding all three indices.
      */
    void setTriangle(int index, Triangle triangle);

    /**
      * Sets the texture coordinates for the specificed vertex.
      * @param index Index of vertex.
      * @param textureCoordinates Texture coordinates.
      */
    void setTextureCoordinates(int index, RealVector2D textureCoordinates);

    /** @returns the vertex of the specified index. */
    RealVector3D vertex(int index);

    /** @returns the triangle of the specified index. */
    Triangle triangle(int index);

    /** @returns the texture coordinates of the specified index. */
    RealVector2D textureCoordinates(int index);

    /** @overload */
    QString className();

    /** @overload */
    QJsonObject serialize();

    /** @overload */
    bool deserialize(QJsonObject jsonObject);

private:
    void allocateMemory();
    void freeMemory();

    int _vertexCount;
    int _triangleCount;

    RealVector3D *_vertices;
    Triangle *_triangles;
    RealVector2D *_textureCoordinates;
};

} // namespace Glee3D

#endif // G3D_MESH_H
