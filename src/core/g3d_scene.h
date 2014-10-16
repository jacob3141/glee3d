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

#ifndef G3D_SCENE_H
#define G3D_SCENE_H

// Own includes
#include "g3d_entity.h"
#include "g3d_camera.h"
#include "g3d_lightsource.h"
#include "g3d_skybox.h"
#include "g3d_terrain.h"
#include "math/g3d_vector2d.h"
#include "math/g3d_vector3d.h"
#include "math/g3d_line3d.h"

// Qt includes
#include <QObject>
#include <QSet>
#include <QMap>
#include <QSemaphore>

namespace Glee3D {
    /**
      * @class Scene
      * @author Jacob Dawid (jacob.dawid@omg-it.works)
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
        void insert(Entity *object);

        /**
          * Removes an object from the scene.
          * @param obejct Object that shall be removed.
          */
        void remove(Entity *object);

        void insert(Terrain *terrain);

        void remove(Terrain *terrain);

        /**
          * Inserts a light source into the scene.
          * @param lightSource Light source that shall be inserted.
          */
        void insert(LightSource *lightSource);

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
        QSet<Entity*> entities();

        /** @returns All light sources in this scene. */
        QSet<LightSource*> lightSources();

        QSet<Terrain*> terrains();

        virtual void processLogic(QMap<int, bool> keyStatusMap, Camera *activeCamera) {
            Q_UNUSED(keyStatusMap);
            Q_UNUSED(activeCamera);
        }

        virtual void select(Line3D ray, Vector3D point) {
            Q_UNUSED(ray);
            Q_UNUSED(point);
        }

        virtual void hover(Line3D ray, Vector3D point) {
            Q_UNUSED(ray);
            Q_UNUSED(point);
        }

        virtual void drag(Line3D fromRay, Line3D toRay,
                          Vector3D fromPoint, Vector3D toPoint) {
            Q_UNUSED(fromRay);
            Q_UNUSED(toRay);
            Q_UNUSED(fromPoint);
            Q_UNUSED(toPoint);
        }

        virtual void endDrag(Line3D ray, Vector3D point) {
            Q_UNUSED(ray);
            Q_UNUSED(point);
        }

    protected:
        SkyBox *_skyBox;
        QSet<Entity*> _entities;
        QSet<LightSource*> _lightSources;
        QSet<Terrain*> _terrains;

    private:
        QSemaphore *_sceneLock;
    };

} // namespace Glee3D

#endif // G3D_SCENE_H
