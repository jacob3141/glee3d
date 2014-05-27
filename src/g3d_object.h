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

#ifndef G3D_OBJECT_H
#define G3D_OBJECT_H

// Own includes
#include "g3d_anchored.h"
#include "g3d_oriented.h"
#include "g3d_material.h"
#include "g3d_vector2d.h"
#include "g3d_mesh.h"
#include "g3d_serializable.h"
#include "g3d_renderable.h"
#include "g3d_texturizable.h"

// Qt includes
#include <QHash>

namespace Glee3D {

/**
  * @class Object
  * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
  * @date 02.12.2012
  * Represents an object in the virtual space.
  */
class Object :
        public Anchored,
        public Oriented,
        public Renderable,
        public Texturizable,
        public Serializable {
public:
    /** Creates a new object for the virtual 3D space. */
    Object();

    /** Destructor. */
    virtual ~Object();

    /** Sets the name for this object.
      * @param name Name for this object.
      */
    void setName(QString name);

    /** @returns the name for this object. */
    QString name();

    /** Accelerates the object by the given amount.
      * @param value Acceleration value.
      * @badcode This should be a vector.
      * @deprecated
      */
    void accelerate(double value);

    /** Sets the velocity for this object.
      * @param value Velocity for this object.
      * @badcode This should be a vector.
      * @deprecated
      */
    void setVelocity(double value);

    /** @returns the velocity for this object. */
    double velocity();

    /** Sets the spin for this object.
      * @param spin Spin of this object for all three angles in degrees.
      */
    void setSpin(RealVector3D spin);

    /** @returns the spin for this object. */
    RealVector3D spin();

    /** Sets whether this object is selected or not.
      * @param on true, if this object is selected.
      */
    void setSelected(bool on = true);

    /** @returns true, when this object is in selected-state. */
    bool selected();

    /** Moves the object forward, ie. in the directon of its
      * front-vector.
      * @param units The distance this object shall be moved.
      */
    void moveForward(double units);

    /** Moves the object backward, ie. in the directon of its
      * front-vector.
      * @param units The distance this object shall be moved.
      */
    void moveBackward(double units);

    /** Applies translation and rotation to the model view matrix. */
    void applyModelViewMatrix();

    /** Renders this object using OpenGL commands. */
    virtual void render(RenderMode renderMode = Textured);

    /** Check whether this object collides with the given line.
      * @param line Collision line.
      * @returns true, when this object collides with the given line.
      */
    bool collides(const RealLine3D& line);

    virtual void compile();

    /** @overload */
    virtual QString className();

    /** @overload */
    virtual QJsonObject serialize();

    /** @overload */
    virtual bool deserialize(QJsonObject jsonObject);

protected:
    QString _name;
    bool _selected;

    Mesh *_mesh;
    CompiledMesh *_compiledMesh;

    RealVector3D _spin;
    double _velocity;
};

} // namespace Glee3D

#endif // G3D_OBJECT_H
