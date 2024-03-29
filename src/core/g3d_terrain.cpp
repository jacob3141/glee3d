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
#include "g3d_display.h"
#include "g3d_terrain.h"

// Qt includes
#include <QImage>
#include <QRgb>
#include <QMap>
#include <QPair>

// Standard includes
#include <iostream>

namespace Glee3D {
    Terrain::Terrain()
        : Anchored(),
          Renderable(),
          Serializable(){
        _scale = 1.0;
    }

    Terrain::~Terrain() {
        freeMemory();
    }

    Terrain::Result Terrain::generate(QString fileName,
                                      Encoding heightEncoding,
                                      Encoding textureEncoding) {
        QImage image;
        if(!image.load(fileName)) {
            std::cout << "Could not find terrain map file: " << fileName.toStdString() << std::endl;
            return FileLoadError;
        }
        return generate(image, heightEncoding, textureEncoding);
    }

    Terrain::Result Terrain::generate(QImage image,
                                      Encoding heightEncoding,
                                      Encoding textureEncoding) {
        _width = image.width();
        _height = image.height();

        if(_width == 0 || _height == 0) {
            return InvalidImageSize;
        }

        allocateMemory();
        for(int y = 0; y < _height; y++) {
            for(int x = 0; x < _width; x++) {
                int pixelValue = image.pixel(x, y);
                switch(heightEncoding) {
                    case RedComponent:
                        _terrain[QPair<int, int>(x,y)] = (double)qRed(pixelValue) - 128.0;
                        break;
                    case GreenComponent:
                        _terrain[QPair<int, int>(x,y)] = (double)qGreen(pixelValue) - 128.0;
                        break;
                    case BlueComponent:
                        _terrain[QPair<int, int>(x,y)] = (double)qBlue(pixelValue) - 128.0;
                        break;
                }

                switch(textureEncoding) {
                    case RedComponent:
                        _tileIDs[QPair<int, int>(x,y)] = qRed(pixelValue);
                        break;
                    case GreenComponent:
                        _tileIDs[QPair<int, int>(x,y)] = qGreen(pixelValue);
                        break;
                    case BlueComponent:
                        _tileIDs[QPair<int, int>(x,y)] = qBlue(pixelValue);
                        break;
                }
            }
        }

        QMap<QPair<int, int>, Vector3D> surfaceNormals;
        for(int y = 0; y < _height - 1; y++) {
            for(int x = 0; x < _width - 1; x++) {
                Vector3D v1 = Vector3D(
                                            0,
                                            _terrain[QPair<int, int>(x, y + 1)] -
                                            _terrain[QPair<int, int>(x, y)],
                                            (double)(y + 1) * 10.0 - (double)y * 10.0);

                Vector3D v2 = Vector3D(
                                            (double)(x + 1) * 10.0 - (double)x * 10.0,
                                            _terrain[QPair<int, int>(x + 1, y)] -
                                            _terrain[QPair<int, int>(x, y)],
                                            0);

                Vector3D normal = v1.crossProduct(v2);
                normal.normalize();
                surfaceNormals[QPair<int, int>(x, y)] = normal;
            }
        }

        // Now compute vertex normals for smooth shading
        for(int y = 0; y < _height; y++) {
            for(int x = 0; x < _width; x++) {
                Vector3D vertexNormal;
                if(x == 0 && y == 0) {
                    vertexNormal = surfaceNormals[QPair<int, int>(0, 0)];
                } else if(x > 0 && x < (_width - 1) && y == 0) {
                    vertexNormal = (surfaceNormals[QPair<int, int>(x - 1, 0)] + surfaceNormals[QPair<int, int>(x, 0)]) * 0.5;
                } else if(x == (_width - 1) && y == 0) {
                    vertexNormal = surfaceNormals[QPair<int, int>(_width - 2, 0)];
                } else if(x == (_width - 1) && y > 0 && y < (_height - 1)) {
                    vertexNormal = (surfaceNormals[QPair<int, int>(_width - 2, y - 1)] + surfaceNormals[QPair<int, int>(_width - 2, y)]) * 0.5;
                } else if(x == (_width - 1) && y == (_height - 1)) {
                    vertexNormal = surfaceNormals[QPair<int, int>(_width - 2, _height - 2)];
                } else if(x > 0 && x < (_width - 1) && y == (_height - 1)) {
                    vertexNormal = (surfaceNormals[QPair<int, int>(x - 1, _height - 2)] + surfaceNormals[QPair<int, int>(x, _height - 2)]) * 0.5;
                } else if(x == 0 && y == (_height - 1)) {
                    vertexNormal = surfaceNormals[QPair<int, int>(0, _height - 2)];
                } else if(x == 0 && y > 0 && y < (_height - 1)) {
                    vertexNormal = (surfaceNormals[QPair<int, int>(0, y - 1)] + surfaceNormals[QPair<int, int>(0, y)]) * 0.5;
                } else {
                    vertexNormal = (surfaceNormals[QPair<int, int>(x - 1, y - 1)]
                            + surfaceNormals[QPair<int, int>(x    , y - 1)]
                            + surfaceNormals[QPair<int, int>(x    , y    )]
                            + surfaceNormals[QPair<int, int>(x - 1, y    )]) * 0.25;
                }
                vertexNormal.normalize();
                _normals[QPair<int, int>(x, y)] = vertexNormal;
            }
        }

        // Translate calculated data into vertex buffer arrays
        _vertexBuffer = new double[(_width - 1) * (_height - 1) * 4 * 3];
        _textureCoordinatesBuffer = new double[(_width - 1) * (_height - 1) * 4 * 2];
        _normalsBuffer = new double[(_width - 1) * (_height - 1) * 4 * 3];

        #define vtx(i, c) ((i) * 3 + (c))
        #define tex(i, c) ((i) * 2 + (c))
        #define nml(i, c) ((i) * 3 + (c))

        int i = 0;
        for(int y = 0; y < _height - 1; y++) {
            for(int x = 0; x < _width - 1; x++) {
                QPair<int, int> p1(x, y);
                QPair<int, int> p2(x, y + 1);
                QPair<int, int> p3(x + 1, y + 1);
                QPair<int, int> p4(x + 1, y);

                Vector3D n1 = _normals[p1];
                Vector3D n2 = _normals[p2];
                Vector3D n3 = _normals[p3];
                Vector3D n4 = _normals[p4];

                double tileID = 0; //_tileIDs[p1];

                //
                _vertexBuffer[vtx(i, 0)] = (double)(x * _scale);
                _vertexBuffer[vtx(i, 1)] = (double)(_terrain[p1] * _scale / 10.0);
                _vertexBuffer[vtx(i, 2)] = (double)(y * _scale);
                _textureCoordinatesBuffer[tex(i, 0)] = _tilingOffset * (double)tileID;
                _textureCoordinatesBuffer[tex(i, 1)] = 0.0f;
                _normalsBuffer[nml(i, 0)] = (double)n1.x();
                _normalsBuffer[nml(i, 1)] = (double)n1.y();
                _normalsBuffer[nml(i, 2)] = (double)n1.z();
                i++;

                //
                _vertexBuffer[vtx(i, 0)] = (double)(x * _scale);
                _vertexBuffer[vtx(i, 1)] = (double)(_terrain[p2] * _scale / 10.0);
                _vertexBuffer[vtx(i, 2)] = (double)((y + 1) * _scale);
                _textureCoordinatesBuffer[tex(i, 0)] = _tilingOffset * (double)tileID;
                _textureCoordinatesBuffer[tex(i, 1)] = 1.0f;
                _normalsBuffer[nml(i, 0)] = (double)n2.x();
                _normalsBuffer[nml(i, 1)] = (double)n2.y();
                _normalsBuffer[nml(i, 2)] = (double)n2.z();
                i++;

                //
                _vertexBuffer[vtx(i, 0)] = (double)((x + 1) * _scale);
                _vertexBuffer[vtx(i, 1)] = (double)(_terrain[p3] * _scale / 10.0);
                _vertexBuffer[vtx(i, 2)] = (double)((y + 1) * _scale);
                _textureCoordinatesBuffer[tex(i, 0)] = _tilingOffset * (double)tileID + _tilingOffset;
                _textureCoordinatesBuffer[tex(i, 1)] = 1.0f;
                _normalsBuffer[nml(i, 0)] = (double)n3.x();
                _normalsBuffer[nml(i, 1)] = (double)n3.y();
                _normalsBuffer[nml(i, 2)] = (double)n3.z();
                i++;

                //
                _vertexBuffer[vtx(i, 0)] = (double)((x + 1) * _scale);
                _vertexBuffer[vtx(i, 1)] = (double)(_terrain[p4] * _scale / 10.0);
                _vertexBuffer[vtx(i, 2)] = (double)(y * _scale);
                _textureCoordinatesBuffer[tex(i, 0)] = _tilingOffset * (double)tileID + _tilingOffset;
                _textureCoordinatesBuffer[tex(i, 1)] = 0.0f;
                _normalsBuffer[nml(i, 0)] = (double)n4.x();
                _normalsBuffer[nml(i, 1)] = (double)n4.y();
                _normalsBuffer[nml(i, 2)] = (double)n4.z();
                i++;
            }
        }

        return Ok;
    }

    void Terrain::setTilingOffset(double tilingOffset) {
        _tilingOffset = tilingOffset;
    }

    void Terrain::setScale(double scale) {
        _scale = scale;
    }

    double Terrain::scale() {
        return _scale;
    }

    int Terrain::width() {
        return _width;
    }

    int Terrain::height() {
        return _height;
    }

    void Terrain::render(RenderMode renderMode) {
        Q_UNUSED(renderMode);
        material()->activate();

        glVertexPointer(3, GL_DOUBLE, 0, _vertexBuffer);
        glTexCoordPointer(2, GL_DOUBLE, 0, _textureCoordinatesBuffer);
        glNormalPointer(GL_DOUBLE, 0, _normalsBuffer);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        glDrawArrays(GL_QUADS, 0, (_width - 1) * (_height - 1) * 4);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
    }

    QString Terrain::className() {
        return "Terrain";
    }

    QJsonObject Terrain::serialize() {
        // TODO: Implement.
        return QJsonObject();
    }

    bool Terrain::deserialize(QJsonObject json) {
        Q_UNUSED(json);
        // TODO: Implement.
        return false;
    }

    void Terrain::allocateMemory() {
        freeMemory();
    }

    void Terrain::freeMemory() {
        _terrain.clear();
        _tileIDs.clear();
        _normals.clear();
    }
} // namespace Glee3D
