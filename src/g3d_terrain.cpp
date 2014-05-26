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

// Standard includes
#include <iostream>

namespace Glee3D {
    Terrain::Terrain()
        : Object() {
        setName("Terrain");
        _terrain = 0;
        _tileIDs = 0;
        _normals = 0;
    }

    Terrain::~Terrain() {
        freeMemory();
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
                        _terrain[x + y * _width] = (float)qRed(pixelValue) - 128.0;
                        break;
                    case GreenComponent:
                        _terrain[x + y * _width] = (float)qGreen(pixelValue) - 128.0;
                        break;
                    case BlueComponent:
                        _terrain[x + y * _width] = (float)qBlue(pixelValue) - 128.0;
                        break;
                }

                switch(textureEncoding) {
                    case RedComponent:
                        _tileIDs[x + y * _width] = qRed(pixelValue);
                        break;
                    case GreenComponent:
                        _tileIDs[x + y * _width] = qGreen(pixelValue);
                        break;
                    case BlueComponent:
                        _tileIDs[x + y * _width] = qBlue(pixelValue);
                        break;
                }
            }
        }

        // Precompute surface normals
        RealVector3D *surfaceNormals = new RealVector3D[(_width - 1)*(_height - 1)];
        #define LIN_IDX(x, y) (x) + ((y) * (_width - 1))

        for(int y = 0; y < _height - 1; y++) {
            for(int x = 0; x < _width - 1; x++) {
                RealVector3D v1 = RealVector3D(
                                            0,
                                            _terrain[x + (y+1) * _width] - _terrain[x + y * _width],
                                            (float)(y+1) * 10.0 - (float)y * 10.0);

                RealVector3D v2 = RealVector3D(
                                            (float)(x+1) * 10.0 - (float)x * 10.0,
                                            _terrain[x+1 + y * _width] - _terrain[x + y * _width],
                                            0);

                surfaceNormals[LIN_IDX(x, y)] = v1.crossProduct(v2);
                surfaceNormals[LIN_IDX(x, y)].normalize();
            }
        }


        // Now compute vertex normals for smooth shading
        for(int y = 0; y < _height; y++) {
            for(int x = 0; x < _width; x++) {
                RealVector3D vertexNormal;
                if(x == 0 && y == 0) {
                    vertexNormal = surfaceNormals[LIN_IDX(0, 0)];
                } else if(x > 0 && x < (_width - 1) && y == 0) {
                    vertexNormal = (surfaceNormals[LIN_IDX(x - 1, 0)] + surfaceNormals[LIN_IDX(x, 0)]) * 0.5;
                } else if(x == (_width - 1) && y == 0) {
                    vertexNormal = surfaceNormals[LIN_IDX(_width - 2, 0)];
                } else if(x == (_width - 1) && y > 0 && y < (_height - 1)) {
                    vertexNormal = (surfaceNormals[LIN_IDX(_width - 2, y - 1)] + surfaceNormals[LIN_IDX(_width - 2, y)]) * 0.5;
                } else if(x == (_width - 1) && y == (_height - 1)) {
                    vertexNormal = surfaceNormals[LIN_IDX(_width - 2, _height - 2)];
                } else if(x > 0 && x < (_width - 1) && y == (_height - 1)) {
                    vertexNormal = (surfaceNormals[LIN_IDX(x - 1, _height - 2)] + surfaceNormals[LIN_IDX(x, _height - 2)]) * 0.5;
                } else if(x == 0 && y == (_height - 1)) {
                    vertexNormal = surfaceNormals[LIN_IDX(0, _height - 2)];
                } else if(x == 0 && y > 0 && y < (_height - 1)) {
                    vertexNormal = (surfaceNormals[LIN_IDX(0, y - 1)] + surfaceNormals[LIN_IDX(0, y)]) * 0.5;
                } else {
                    vertexNormal = (surfaceNormals[LIN_IDX(x - 1, y - 1)]
                            + surfaceNormals[LIN_IDX(x    , y - 1)]
                            + surfaceNormals[LIN_IDX(x    , y    )]
                            + surfaceNormals[LIN_IDX(x - 1, y    )]) * 0.25;
                }
                vertexNormal.normalize();
                _normals[x * 3 + y * _width * 3 + 0] = vertexNormal._x;
                _normals[x * 3 + y * _width * 3 + 1] = vertexNormal._y;
                _normals[x * 3 + y * _width * 3 + 2] = vertexNormal._z;
            }
        }

        #undef LIN_IDX
        delete[] surfaceNormals;
        return Ok;
    }

    void Terrain::setTilingOffset(float tilingOffset) {
        _tilingOffset = tilingOffset;
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
                glNormal3f(
                _normals[x * 3 + y * _width * 3 + 0],
                _normals[x * 3 + y * _width * 3 + 1],
                _normals[x * 3 + y * _width * 3 + 2]);
                glVertex3f((float)x * 10.0, _terrain[x + y * _width],(float)y * 10.0);
                glTexCoord2f(_tilingOffset * (float)_tileIDs[x + y * (_width - 1)], 0.0);

                glNormal3f(
                _normals[x * 3 + (y+1) * _width * 3 + 0],
                _normals[x * 3 + (y+1) * _width * 3 + 1],
                _normals[x * 3 + (y+1) * _width * 3 + 2]);
                glVertex3f((float)x * 10.0, _terrain[x + (y+1) * _width],(float)(y+1) * 10.0);
                glTexCoord2f(_tilingOffset * (float)_tileIDs[x + y * (_width - 1)], 1.0);

                glNormal3f(
                _normals[(x+1) * 3 + (y+1) * _width * 3 + 0],
                _normals[(x+1) * 3 + (y+1) * _width * 3 + 1],
                _normals[(x+1) * 3 + (y+1) * _width * 3 + 2]);
                glVertex3f((float)(x+1) * 10.0, _terrain[x+1 + (y+1) * _width],(float)(y+1) * 10.0);
                glTexCoord2f(_tilingOffset * (float)_tileIDs[x + y * (_width - 1)] + _tilingOffset, 1.0);

                glNormal3f(
                _normals[(x+1) * 3 + y * _width * 3 + 0],
                _normals[(x+1) * 3 + y * _width * 3 + 1],
                _normals[(x+1) * 3 + y * _width * 3 + 2]);
                glVertex3f((float)(x+1) * 10.0, _terrain[x+1 + y * _width],(float)y * 10.0);
                glTexCoord2f(_tilingOffset * (float)_tileIDs[x + y * (_width - 1)] + _tilingOffset, 0.0);

            }
        }
        glEnd();
    }

    void Terrain::allocateMemory() {
        freeMemory();
        _terrain = new float[_width * _height];
        _tileIDs = new int[(_width - 1) * (_height - 1)];
        _normals = new float[_width * _height * 3];
    }

    void Terrain::freeMemory() {
        if(_terrain) {
            delete[] _terrain;
        }
        if(_tileIDs) {
            delete[] _tileIDs;
        }
        if(_normals) {
            delete[] _normals;
        }
    }
} // namespace Glee3D
