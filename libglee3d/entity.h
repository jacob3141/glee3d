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

#ifndef ENTITY_H
#define ENTITY_H

// Own includes
#include "vector3d.h"

namespace Glee3D {
/**
  * @class Entity
  * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
  * @date 02.12.2012
  * An entity can be anything that qualifies as an independent object in
  * the 3D world. The idea is that entities can be made up of other
  * child entities to form a more complex object.
  */
class Entity {
public:
    /**
      * Creates a new entity.
      * @param parent Parent entity.
      */
    Entity(Entity *parent = 0);

    /**
      * @returns Position of this entity in relation to its parent.
      */
    RealVector3D position();

    /**
      * Set the position of this entitiy in relation to its parent.
      * @param position Position that shall be set for this entity.
      */
    void setPosition(RealVector3D position);

    /**
      * Moves this entity in relation to its parent.
      * @param delta Distance that this entity shall be moved.
      */
    void move(RealVector3D delta);

protected:
    RealVector3D _position;

private:
    Entity *_parent;
};

} // namespace Glee3D

#endif // ENTITY_H
