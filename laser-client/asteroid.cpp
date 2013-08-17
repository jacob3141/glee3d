///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of glee3d.                                           //
//    Copyright (C) 2012 Jacob Dawid, jacob.dawid@googlemail.com             //
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

#include "asteroid.h"

Asteroid::Asteroid(Entity *parent)
    : Glee3D::Object(parent) {
    setName("Asteroid");
}

void Asteroid::generate(double radius, double aspect, int resolution) {
    _mesh = new Glee3D::Mesh(resolution * resolution,
                   (resolution - 1) * (resolution - 1) * 2);

    int i, j, n = 0;
    // Create randomness
    double heightmap[resolution][resolution];
    for(i = 0; i < resolution; i++) {
        for(j = 0; j < resolution; j++) {
            heightmap[i][j] = (double)(rand() % (int)(radius * 2.0));
        }
    }

    // Blur filter
    for(i = 0; i < resolution; i++) {
        for(j = 0; j < resolution; j++) {
            int k, m;
            double sum = 0.0;
            for(k = -1; k < 2; k++) {
                for(m = -1; m < 2; m++) {
                    sum += heightmap[(i + k + resolution) % resolution]
                                    [(j + m + resolution) % resolution];
                }
            }
            heightmap[i][j] = sum / 9.0;
        }
    }

    for(i = 0; i < resolution; i++) {
        double theta = i * M_PI / (double)(resolution - 1);
        double y = cos(theta);
        double r = sin(theta);
        for(j = 0; j < resolution; j++) {
            double alpha = j * M_PI * 2 / (double)resolution;
            double x = cos(alpha) * r * aspect;
            double z = sin(alpha) * r;
            _mesh->setVertex(n, Glee3D::RealVector3D(
                x * (radius + heightmap[i][j]),
                y * (radius + heightmap[i][j]),
                z * (radius + heightmap[i][j])));
            _mesh->setTextureCoordinates(n, Glee3D::RealVector2D((double)i / (double)resolution,
                                                         (double)j / (double)resolution));
            n++;
        }
    }

    n = 0;
    for(i = 0; i < resolution - 1; i++) {
        for(j = 0; j < resolution - 2; j++) {
            _mesh->setTriangle(n, Glee3D::Triangle(
                j + resolution * (i + 1),
                j + 1 + resolution * i,
                j + resolution * i));
            n++;
            _mesh->setTriangle(n, Glee3D::Triangle(
                j + 1 + resolution * (i + 1),
                j + 1 + resolution * i,
                j + resolution * (i + 1)));
            n++;
        }

        _mesh->setTriangle(n, Glee3D::Triangle(
            j + resolution * (i + 1),
            resolution * i,
            j + resolution * i));
        n++;
        _mesh->setTriangle(n, Glee3D::Triangle(
            resolution * (i + 1),
            resolution * i,
            j + resolution * (i + 1)));
        n++;
    }

    compile();
}
