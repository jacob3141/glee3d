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

#ifndef SCENE_H
#define SCENE_H

// Own includes
#include "object.h"
#include "camera.h"
#include "lightsource.h"
#include "vector3d.h"
#include "vector2d.h"
#include "skybox.h"

// Qt includes
#include <QObject>
#include <QSet>
#include <QMap>
#include <QSemaphore>

namespace Glee3D {
/**
  * @class Scene
  * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
  * @date 02.12.2012
  * The model representation of the current virtual scene.
  */
class Scene : public QObject {
    Q_OBJECT
public:
    /**
      * Creates a new scene.
      */
    explicit Scene(QObject *parent = 0);
    virtual ~Scene();

    /**
      * Sets the skybox for this scene.
      * @param skyBox Skybox for this scene.
      */
    void setSkyBox(SkyBox *skyBox);

    /** @returns The skybox for this scene. */
    SkyBox *skyBox();

    /**
      * Inserts an object into the scene.
      * @param object Object that shall be inserted.
      */
    void insertObject(Object *object);

    /**
      * Removes an object from the scene.
      * @param obejct Object that shall be removed.
      */
    void removeObject(Object *object);

    /**
      * Inserts a light source into the scene.
      * @param lightSource Light source that shall be inserted.
      */
    void insertLightSource(LightSource *lightSource);

    /**
      * Locks the scene. During the time a scene is locked it cannot
      * be modified.
      */
    void lockScene();

    /**
      * Unlocks a previously locked scene.
      */
    void unlockScene();

    /** @returns All objects in this scene. */
    QSet<Object*> objects();

    /** @returns All light sources in this scene. */
    QSet<LightSource*> lightSources();

    virtual void processLogic(QMap<int, bool> keyStatusMap, Camera *activeCamera) {
        Q_UNUSED(keyStatusMap);
        Q_UNUSED(activeCamera);
    }

    virtual void select(RealLine3D line) {
        Q_UNUSED(line);
    }

    virtual void drag(RealLine3D from, RealLine3D to) {
        Q_UNUSED(from);
        Q_UNUSED(to);
    }

    virtual void endDrag() {
    }

protected:
    SkyBox *_skyBox;
    QSet<Object*> _objects;
    QSet<LightSource*> _lightSources;

private:
    QSemaphore *_sceneLock;
};

} // namespace Glee3D

#endif // SCENE_H
