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
#include "g3d_cylinder.h"
#include "math/g3d_vector3d.h"

// Standard includes
#include <math.h>

namespace Glee3D {
    Cylinder::Cylinder()
        : Entity() {
        setName("Cylinder");
    }

    void Cylinder::generate(double radius, double height, int segments) {
        _mesh = new Glee3D::Mesh(segments * 2 + 2, segments * 2 + segments * 6);
        for(int i = 0; i < segments; i++) {
            double alpha = (double)i / (double)segments * 2.0 * M_PI;
            _mesh->setVertex(i, Glee3D::Vector3D(
                cos(alpha) * radius,
                - height / 2,
                sin(alpha) * radius));

            _mesh->setVertex(i + segments, Glee3D::Vector3D(
                cos(alpha) * radius,
                + height / 2,
                sin(alpha) * radius));

            _mesh->setTextureCoordinates(i, Glee3D::Vector2D(0.0, 0.0));
            _mesh->setTextureCoordinates(i + segments, Glee3D::Vector2D(
                cos(alpha) / 2.0 + 0.5, sin(alpha) / 2.0 + 0.5));
        }

        _mesh->setVertex(segments * 2, Glee3D::Vector3D(
            0.0, - height / 2, 0.0));
        _mesh->setTextureCoordinates(segments * 2,
            Glee3D::Vector2D(0.5, 0.5));

        _mesh->setVertex(segments * 2 + 1, Glee3D::Vector3D(
            0.0, + height / 2, 0.0));
        _mesh->setTextureCoordinates(segments * 2 + 1,
            Glee3D::Vector2D(0.5, 0.5));

        int i;
        int count = 0;
        for(i = 0; i < segments - 1; i++) {
            _mesh->setTriangle(count,
               Glee3D::Triangle(i + segments, i + 1, i));
            count++;

            _mesh->setTriangle(count,
               Glee3D::Triangle(i + segments, i + segments + 1, i + 1));
            count++;
        }

        _mesh->setTriangle(i * 2,
            Glee3D::Triangle(2 * segments - 1, segments, 0));
        count++;

        _mesh->setTriangle(i * 2 + 1,
            Glee3D::Triangle(2 * segments - 1, 0, segments - 1));
        count++;


        for(i = 0; i < segments - 1; i++) {
            _mesh->setTriangle(count, Glee3D::Triangle(i, i + 1, segments * 2));
            count++;
        }

        _mesh->setTriangle(count, Glee3D::Triangle(i, 0, segments * 2));
        count++;

        for(i = 0; i < segments - 1; i++) {
            _mesh->setTriangle(count,
                Glee3D::Triangle(segments * 2 + 1, i + segments + 1, i + segments));
            count++;
        }

        _mesh->setTriangle(count,
            Glee3D::Triangle(segments * 2 + 1, i + 1, i + segments));
        count++;
    }
} // namespace Glee3D
