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

#ifndef G3D_SKYBOX_H
#define G3D_SKYBOX_H

// Own includes
#include "g3d_object.h"
#include "g3d_material.h"

// Qt includes
#include <QMap>

namespace Glee3D {

class Display;
class Camera;
/**
  * @class SkyBox
  * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
  * @date 02.12.2012
  * Defines a skybox.
  */
class SkyBox : public Object {
public:
    /**
      * @enum Plane
      * Enumeration for all skybox planes.
      */
    enum Plane {
        BackX,
        FrontX,
        BackY,
        FrontY,
        BackZ,
        FrontZ
    };

    /**
      * Creates a new skybox.
      */
    SkyBox();

    /**
      * Loads a texture for a specific plane.
      * NOTE: Usually the Surface class should be used, but in this case
      * we can optimize performance by just ignoring using a texture and
      * not defining material properties.
      * @param plane Plane for which the texture shall be loaded.
      * @param fileName File name of the texture image.
      * @param display The current display.
      */
    void loadTexture(Plane plane, QString fileName, Display *display);

    /**
      * Renders the skybox.
      */
    void render();

private:
    QMap<Plane, Material*> _materials;
};

} // namespace Glee3D

#endif // G3D_SKYBOX_H
