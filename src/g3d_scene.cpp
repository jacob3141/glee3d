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

#include <QApplication>

#include "g3d_scene.h"

namespace Glee3D {
    Scene::Scene(QObject *parent)
        : QObject(parent) {
        _sceneLock = new QSemaphore(1);
        _skyBox = 0;
    }

    Scene::~Scene() {
    }

    void Scene::setSkyBox(SkyBox *skyBox) {
        _skyBox = skyBox;
    }

    SkyBox *Scene::skyBox() {
        return _skyBox;
    }

    void Scene::insertObject(Object *object) {
        if(object) {
            _objects.insert(object);
        }
    }

    void Scene::removeObject(Object *object) {
        if(object) {
            _objects.remove(object);
        }
    }

    void Scene::insertLightSource(LightSource *lightSource) {
        if(lightSource) {
            _lightSources.insert(lightSource);
        }
    }

    void Scene::lockScene() {
        _sceneLock->acquire();
    }

    void Scene::unlockScene() {
        _sceneLock->release();
    }

    QSet<Object*> Scene::objects() {
        return _objects;
    }

    QSet<LightSource*> Scene::lightSources() {
        return _lightSources;
    }
} // namespace Glee3D
