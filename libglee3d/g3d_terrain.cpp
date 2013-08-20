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
#include "g3d_terrain.h"

// Qt includes
#include <QImage>
#include <QRgb>

// Standard includes
#include <iostream>

namespace Glee3D {
    Terrain::Terrain(Entity *parent)
        : Object(parent) {
        setName("Terrain");
    }

    Terrain::~Terrain() {
    }

    void Terrain::generateFromHeightmap(QString fileName) {
        QImage heightmap;
        if(!heightmap.load(fileName)) {
            std::cout << "Error loading heightmap " << fileName.toStdString() << std::endl;
            return;
        }

        int width = heightmap.width();
        int height = heightmap.height();

        _mesh = new Mesh(width * height, (width - 1) * (height - 1) * 2);

        int vertex = 0;
        for(int zz = 0; zz < height; zz++) {
            for(int xx = 0; xx < width; xx++) {
                _mesh->setVertex(vertex,
                                 RealVector3D(
                                     ((float)zz - (float)height / 2) * 10.0,
                                     (float)qRed(heightmap.pixel(xx, zz)) - (float)128.0,
                                     ((float)xx - (float)width / 2) * 10.0)
                                 );
                _mesh->setTextureCoordinates(vertex, RealVector2D((float)xx / (float)width,
                                                                  (float)zz / (float)height));
                vertex++;
            }
        }

        int triangle = 0;
        for(int zz = 0; zz < height - 1; zz++) {
            for(int xx = 0; xx < width - 1; xx++) {
                _mesh->setTriangle(triangle, Triangle(xx + zz * width,
                                                      xx + zz * width + 1,
                                                      xx + (zz + 1) * width));
                triangle++;

                _mesh->setTriangle(triangle, Triangle(xx + (zz + 1) * width + 1,
                                                      xx + (zz + 1) * width,
                                                      xx + zz * width + 1));
                triangle++;
            }
        }

        compile();
    }
}
