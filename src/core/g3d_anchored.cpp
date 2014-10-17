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
#include "g3d_anchored.h"

// Qt includes
#include <QGLWidget>

namespace Glee3D {
    Anchored::Anchored() {
        _position = Vector3D(0.0, 0.0, 0.0);
    }

    Vector3D Anchored::position() {
        return _position;
    }

    void Anchored::setPosition(Vector3D position) {
        _position = position;
    }

    void Anchored::move(Vector3D delta) {
        _position += delta;
    }

    void Anchored::applyTranslation() {
        glTranslated(_position.x(), _position.y(), _position.z());
    }
} // namespace Glee3D
