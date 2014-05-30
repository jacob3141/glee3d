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

    void Terrain::applyModelViewMatrix() {
        glMatrixMode(GL_MODELVIEW);
        glTranslated(_position._x, _position._y, _position._z);
        //glRotated(_rotation._x, 1.0, 0.0, 0.0);
        //glRotated(_rotation._y, 0.0, 1.0, 0.0);
        //glRotated(_rotation._z, 0.0, 0.0, 1.0);
    }


    Terrain::Result Terrain::generate(QString fileName,
                                      Encoding heightEncoding,
                                      Encoding textureEncoding) {
        QImage image;
        if(!image.load(fileName)) {
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
                        _terrain[QPair<int, int>(x,y)] = (float)qRed(pixelValue) - 128.0;
                        break;
                    case GreenComponent:
                        _terrain[QPair<int, int>(x,y)] = (float)qGreen(pixelValue) - 128.0;
                        break;
                    case BlueComponent:
                        _terrain[QPair<int, int>(x,y)] = (float)qBlue(pixelValue) - 128.0;
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

        QMap<QPair<int, int>, RealVector3D> surfaceNormals;
        for(int y = 0; y < _height - 1; y++) {
            for(int x = 0; x < _width - 1; x++) {
                RealVector3D v1 = RealVector3D(
                                            0,
                                            _terrain[QPair<int, int>(x, y + 1)] -
                                            _terrain[QPair<int, int>(x, y)],
                                            (float)(y + 1) * 10.0 - (float)y * 10.0);

                RealVector3D v2 = RealVector3D(
                                            (float)(x + 1) * 10.0 - (float)x * 10.0,
                                            _terrain[QPair<int, int>(x + 1, y)] -
                                            _terrain[QPair<int, int>(x, y)],
                                            0);

                RealVector3D normal = v1.crossProduct(v2);
                normal.normalize();
                surfaceNormals[QPair<int, int>(x, y)] = normal;
            }
        }

        // Now compute vertex normals for smooth shading
        for(int y = 0; y < _height; y++) {
            for(int x = 0; x < _width; x++) {
                RealVector3D vertexNormal;
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

        return Ok;
    }

    void Terrain::setTilingOffset(float tilingOffset) {
        _tilingOffset = tilingOffset;
    }

    void Terrain::setScale(float scale) {
        _scale = scale;
    }

    float Terrain::scale() {
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
        glBegin(GL_QUADS);
        for(int y = 0; y < _height - 1; y++) {
            for(int x = 0; x < _width - 1; x++) {
                QPair<int, int> p1(x, y);
                QPair<int, int> p2(x, y + 1);
                QPair<int, int> p3(x + 1, y + 1);
                QPair<int, int> p4(x + 1, y);

                RealVector3D n1 = _normals[p1];
                RealVector3D n2 = _normals[p2];
                RealVector3D n3 = _normals[p3];
                RealVector3D n4 = _normals[p4];

                float tileID = 0; //_tileIDs[p1];
                glNormal3f(n1._x, n1._y, n1._z);
                glVertex3f((float)x * _scale, _terrain[p1],(float)y * _scale);
                glTexCoord2f(_tilingOffset * (float)tileID, 0.0);

                glNormal3f(n2._x, n2._y, n2._z);
                glVertex3f((float)x * _scale, _terrain[p2],(float)(y+1) * _scale);
                glTexCoord2f(_tilingOffset * (float)tileID, 1.0);

                glNormal3f(n3._x, n3._y, n3._z);
                glVertex3f((float)(x+1) * _scale, _terrain[p3],(float)(y+1) * _scale);
                glTexCoord2f(_tilingOffset * (float)tileID + _tilingOffset, 1.0);

                glNormal3f(n4._x, n4._y, n4._z);
                glVertex3f((float)(x+1) * _scale, _terrain[p4],(float)y * _scale);
                glTexCoord2f(_tilingOffset * (float)tileID + _tilingOffset, 0.0);
            }
        }
        glEnd();
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
