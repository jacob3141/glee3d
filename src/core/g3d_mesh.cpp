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
#include "g3d_mesh.h"

namespace Glee3D {
    Mesh::Mesh()
        : Serializable() {
        _vertices = 0;
        _triangles = 0;
        _textureCoordinates = 0;

        _vertexCount = 0;
        _triangleCount = 0;
    }

    Mesh::Mesh(int vertexCount, int triangleCount)
        : Serializable() {
        _vertices = 0;
        _triangles = 0;
        _textureCoordinates = 0;

        create(vertexCount, triangleCount);
    }

    Mesh::~Mesh() {
        freeMemory();
    }

    void Mesh::create(int vertexCount, int triangleCount) {
        _vertexCount = vertexCount;
        _triangleCount = triangleCount;
        allocateMemory();
    }

    CompiledMesh *Mesh::compile() {
        CompiledMesh *compiledMesh = new CompiledMesh(_triangleCount);

        // Determine collision radius
        double maxDistance = 0.0;
        for(int i = 0; i < _vertexCount; i++) {
            double length = _vertices[i].length();
            if(length > maxDistance) {
                maxDistance = length;
            }
        }
        compiledMesh->_collisionRadius = maxDistance;

        // Compute surface normals.
        RealVector3D *surfaceNormals = new RealVector3D[_triangleCount];
        for(int i = 0; i < _triangleCount; i++) {
            int i1 = _triangles[i]._indices[0];
            int i2 = _triangles[i]._indices[1];
            int i3 = _triangles[i]._indices[2];

            // User the cross product to determine the normal of a material.
            surfaceNormals[i] = ((_vertices[i2] - _vertices[i1])
                    .crossProduct(_vertices[i3] - _vertices[i1])).normalize();
        }

        // Calculate vertex joint normals for smooth shadowing
        RealVector3D vertexJointNormal[_vertexCount];
        for(int i = 0; i < _vertexCount; i++) {
            RealVector3D cumulatedJointNormal;
            for(int j = 0; j < _triangleCount; j++) {
                if(_triangles[j]._indices[0] == i
                || _triangles[j]._indices[1] == i
                || _triangles[j]._indices[2] == i) {
                    cumulatedJointNormal += surfaceNormals[j];
                }
            }
            vertexJointNormal[i] = cumulatedJointNormal.normalize();
        }
        delete[] surfaceNormals;

        int i;
        for(i = 0; i < _triangleCount; i++) {
            int i1 = _triangles[i]._indices[0];
            int i2 = _triangles[i]._indices[1];
            int i3 = _triangles[i]._indices[2];

            compiledMesh->_vertices[i * 9 + 0] = _vertices[i1]._x;
            compiledMesh->_vertices[i * 9 + 1] = _vertices[i1]._y;
            compiledMesh->_vertices[i * 9 + 2] = _vertices[i1]._z;
            compiledMesh->_vertices[i * 9 + 3] = _vertices[i2]._x;
            compiledMesh->_vertices[i * 9 + 4] = _vertices[i2]._y;
            compiledMesh->_vertices[i * 9 + 5] = _vertices[i2]._z;
            compiledMesh->_vertices[i * 9 + 6] = _vertices[i3]._x;
            compiledMesh->_vertices[i * 9 + 7] = _vertices[i3]._y;
            compiledMesh->_vertices[i * 9 + 8] = _vertices[i3]._z;

            compiledMesh->_texCoords[i * 6 + 0] = _textureCoordinates[i1]._x;
            compiledMesh->_texCoords[i * 6 + 1] = _textureCoordinates[i1]._y;
            compiledMesh->_texCoords[i * 6 + 2] = _textureCoordinates[i2]._x;
            compiledMesh->_texCoords[i * 6 + 3] = _textureCoordinates[i2]._y;
            compiledMesh->_texCoords[i * 6 + 4] = _textureCoordinates[i3]._x;
            compiledMesh->_texCoords[i * 6 + 5] = _textureCoordinates[i3]._y;

            compiledMesh->_normals[i * 9 + 0] = vertexJointNormal[i1]._x;
            compiledMesh->_normals[i * 9 + 1] = vertexJointNormal[i1]._y;
            compiledMesh->_normals[i * 9 + 2] = vertexJointNormal[i1]._z;
            compiledMesh->_normals[i * 9 + 3] = vertexJointNormal[i2]._x;
            compiledMesh->_normals[i * 9 + 4] = vertexJointNormal[i2]._y;
            compiledMesh->_normals[i * 9 + 5] = vertexJointNormal[i2]._z;
            compiledMesh->_normals[i * 9 + 6] = vertexJointNormal[i3]._x;
            compiledMesh->_normals[i * 9 + 7] = vertexJointNormal[i3]._y;
            compiledMesh->_normals[i * 9 + 8] = vertexJointNormal[i3]._z;
        }
        return compiledMesh;
    }

    void Mesh::setVertex(int index, RealVector3D vertex) {
        _vertices[index] = vertex;
    }

    void Mesh::setTriangle(int index, Triangle triangle) {
        _triangles[index] = triangle;
    }

    void Mesh::setTextureCoordinates(int index, RealVector2D textureCoordinates) {
        _textureCoordinates[index] = textureCoordinates;
    }

    RealVector3D Mesh::vertex(int index) {
        return _vertices[index];
    }

    Triangle Mesh::triangle(int index) {
        return _triangles[index];
    }

    RealVector2D Mesh::textureCoordinates(int index) {
        return _textureCoordinates[index];
    }

    QString Mesh::className() {
        return "Mesh";
    }

    QJsonObject Mesh::serialize() {
        QJsonObject jsonObject;
        jsonObject["class"] = className();

        QJsonArray verticesArray, textureCoordinatesArray, trianglesArray;
        for(int i = 0; i < _vertexCount; i++) {
            verticesArray.append(_vertices[i].serialize());
        }

        for(int i = 0; i < _vertexCount; i++) {
            textureCoordinatesArray.append(_textureCoordinates[i].serialize());
        }

        for(int i = 0; i < _triangleCount; i++) {
            trianglesArray.append(_triangles[i].serialize());
        }

        jsonObject["vertices"] = verticesArray;
        jsonObject["textureCoordinates"] = textureCoordinatesArray;
        jsonObject["triangles"] = trianglesArray;
        return jsonObject;
    }

    bool Mesh::deserialize(QJsonObject jsonObject) {
        if(!jsonObject.contains("class")) {
            _deserializationError = Serializable::NoClassSpecified;
            qDebug() << className() << " Class name not specified";
            return false;
        }

        if(jsonObject.contains("vertices")
        && jsonObject.contains("textureCoordinates")
        && jsonObject.contains("triangles")) {
            if(jsonObject["class"] == className()) {
                if(jsonObject["vertices"].type() != QJsonValue::Array
                || jsonObject["textureCoordinates"].type() != QJsonValue::Array
                || jsonObject["triangles"].type() != QJsonValue::Array) {
                    _deserializationError = Serializable::MissingElements;
                    qDebug() << className() << ": Vertex data must be stored in arrays";
                    return false;
                }

                QJsonArray verticesArray = jsonObject["vertices"].toArray();
                QJsonArray textureCoordinatesArray = jsonObject["textureCoordinates"].toArray();
                QJsonArray trianglesArray = jsonObject["triangles"].toArray();

                if(verticesArray.count() != textureCoordinatesArray.count()) {
                    _deserializationError = Serializable::MissingElements;
                    qDebug() << className() << ": Vertex count must be the same as texture coordinates count";
                    return false;
                }

                create(verticesArray.count(), trianglesArray.count());

                for(int i = 0; i < _vertexCount; i++) {
                    if(!_vertices[i].deserialize(verticesArray[i].toObject())) {
                        _deserializationError = _vertices[i].deserializationError();
                        qDebug() << className() << ": Couldn't deserialize vertex " << i;
                        return false;
                    }
                }

                for(int i = 0; i < _vertexCount; i++) {
                    if(!_textureCoordinates[i].deserialize(textureCoordinatesArray[i].toObject())) {
                        _deserializationError = _textureCoordinates[i].deserializationError();
                        qDebug() << className() << ": Couldn't deserialize texture coordinate " << i;
                        return false;
                    }
                }

                for(int i = 0; i < _triangleCount; i++) {
                    if(!_triangles[i].deserialize(trianglesArray[i].toObject())) {
                        _deserializationError = _triangles[i].deserializationError();
                        qDebug() << className() << ": Couldn't deserialize triangle " << i;
                        return false;
                    }
                }

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

    void Mesh::allocateMemory() {
        freeMemory();
        _vertices = new RealVector3D[_vertexCount];
        _textureCoordinates = new RealVector2D[_vertexCount];
        _triangles = new Triangle[_triangleCount];

        int i;
        for(i = 0; i < _triangleCount; i++) {
            _triangles[i]._indices[0] = 0;
            _triangles[i]._indices[1] = 0;
            _triangles[i]._indices[2] = 0;
        }
    }

    void Mesh::freeMemory() {
        if(_vertices) delete[] _vertices;
        if(_triangles) delete[] _triangles;
        if(_textureCoordinates) delete[] _textureCoordinates;

        _vertices = 0;
        _triangles = 0;
        _textureCoordinates = 0;
    }

} // namespace Glee3D
