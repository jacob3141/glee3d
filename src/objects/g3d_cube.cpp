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
#include "g3d_cube.h"

namespace Glee3D {
    Cube::Cube()
        : Entity() {
        setName("Cube");
    }

    Cube::~Cube() {
    }

    void Cube::generate(double edgeLength, double scaleX, double scaleY, double scaleZ) {
        _mesh = new Mesh(8, 12);
        double k = edgeLength / 2;
        _mesh->setVertex(0, RealVector3D(-k * scaleX, -k * scaleY, -k * scaleZ));
        _mesh->setVertex(1, RealVector3D(+k * scaleX, -k * scaleY, -k * scaleZ));
        _mesh->setVertex(2, RealVector3D(+k * scaleX, +k * scaleY, -k * scaleZ));
        _mesh->setVertex(3, RealVector3D(-k * scaleX, +k * scaleY, -k * scaleZ));
        _mesh->setVertex(4, RealVector3D(-k * scaleX, -k * scaleY, +k * scaleZ));
        _mesh->setVertex(5, RealVector3D(+k * scaleX, -k * scaleY, +k * scaleZ));
        _mesh->setVertex(6, RealVector3D(+k * scaleX, +k * scaleY, +k * scaleZ));
        _mesh->setVertex(7, RealVector3D(-k * scaleX, +k * scaleY, +k * scaleZ));

        _mesh->setTriangle(0, Triangle(2, 1, 0));
        _mesh->setTriangle(1, Triangle(3, 2, 0));
        _mesh->setTriangle(2, Triangle(4, 5, 6));
        _mesh->setTriangle(3, Triangle(4, 6, 7));
        _mesh->setTriangle(4, Triangle(2, 6, 1));
        _mesh->setTriangle(5, Triangle(1, 6, 5));
        _mesh->setTriangle(6, Triangle(3, 6, 2));
        _mesh->setTriangle(7, Triangle(7, 6, 3));
        _mesh->setTriangle(8, Triangle(0, 4, 3));
        _mesh->setTriangle(9, Triangle(3, 4, 7));
        _mesh->setTriangle(10, Triangle(1, 4, 0));
        _mesh->setTriangle(11, Triangle(5, 4, 1));

        _mesh->setTextureCoordinates(0, RealVector2D( 0.25, 0.25));
        _mesh->setTextureCoordinates(1, RealVector2D( 0.75, 0.25));
        _mesh->setTextureCoordinates(2, RealVector2D( 0.75, 0.75));
        _mesh->setTextureCoordinates(3, RealVector2D( 0.25, 0.75));
        _mesh->setTextureCoordinates(4, RealVector2D( 0.0, 0.0));
        _mesh->setTextureCoordinates(5, RealVector2D( 1.0, 0.0));
        _mesh->setTextureCoordinates(6, RealVector2D( 1.0, 1.0));
        _mesh->setTextureCoordinates(7, RealVector2D( 0.0, 1.0));
    }
} // namespace Glee3D
