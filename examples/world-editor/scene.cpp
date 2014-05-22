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


#include "scene.h"

#include "g3d_scene.h"
#include "g3d_vector2d.h"
#include "g3d_rgbacolor.h"
#include "g3d_skybox.h"
#include "g3d_cube.h"
#include "g3d_terrain.h"

#include <QApplication>

Scene::Scene(Glee3D::Display *display)
    : Glee3D::Scene() {

    Glee3D::SkyBox *skyBox = new Glee3D::SkyBox();
    skyBox->loadTexture(Glee3D::SkyBox::BackX, "../../skybox/sky/xneg.png", display);
    skyBox->loadTexture(Glee3D::SkyBox::FrontX, "../../skybox/sky/xpos.png", display);
    skyBox->loadTexture(Glee3D::SkyBox::BackY, "../../skybox/sky/yneg.png", display);
    skyBox->loadTexture(Glee3D::SkyBox::FrontY, "../../skybox/sky/ypos.png", display);
    skyBox->loadTexture(Glee3D::SkyBox::BackZ, "../../skybox/sky/zneg.png", display);
    skyBox->loadTexture(Glee3D::SkyBox::FrontZ, "../../skybox/sky/zpos.png", display);
    setSkyBox(skyBox);

    Glee3D::LightSource *globalLight = new Glee3D::LightSource();
    globalLight->setPosition(Glee3D::RealVector3D(10.0, 100.0, 12.0));
    globalLight->setAmbientLight(Glee3D::RgbaColor(0.5, 0.5, 0.5, 1.0));
    globalLight->setSpecularLight(Glee3D::RgbaColor(0.5, 0.5, 0.5, 1.0));
    globalLight->setDiffuseLight(Glee3D::RgbaColor(0.8, 0.8, 0.8, 1.0));
    insertLightSource(globalLight);

    Glee3D::Cube *cube = new Glee3D::Cube();
    cube->generate(10.0);
    cube->setMaterial(new Glee3D::PearlMaterial());
    cube->material()->loadTexture("../../textures/chrome.png", *display);
    cube->setPosition(Glee3D::RealVector3D(0.0, 50.0, 0.0));
    insertObject(cube);

    Glee3D::Terrain *terrain = new Glee3D::Terrain();
    terrain->generate("../../heightmaps/heightmap.png");
    terrain->setMaterial(new Glee3D::ChromeMaterial());
    terrain->material()->loadTexture("../../textures/terraintiles.png", *display);
    terrain->setTilingOffset(0.5);
    insertObject(terrain);
}

void Scene::select(Glee3D::RealLine3D line) {
    Q_UNUSED(line);
//    bool somethingSelected = false;
//    foreach(Glee3D::Object *o, _objects) {
//        if(o->collides(line)) {
//            o->setSelected(true);
//            o->material()->setEmission(Glee3D::RgbaColor(0.0, 0.2, 1.0, 1.0));
//            somethingSelected = true;
//        } else {
//            o->setSelected(false);
//            o->material()->setEmission(Glee3D::RgbaColor(0.0, 0.0, 0.0, 1.0));
//        }
//    }

//    if(somethingSelected) {
//    }
}

void Scene::drag(Glee3D::RealLine3D from, Glee3D::RealLine3D to) {
    Q_UNUSED(from);
    Q_UNUSED(to);
}

void Scene::endDrag() {
}

void Scene::processLogic(QMap<int, bool> keyStatusMap, Glee3D::Camera *activeCamera) {
    if(keyStatusMap[Qt::Key_Escape]) {
        QApplication::quit();
    }

    foreach(Glee3D::Object *o, _objects) {
        o->rotate(o->spin());
        o->move(o->front() * o->velocity());
    }


    if(keyStatusMap[Qt::Key_Space]) {

    }

    if(keyStatusMap[Qt::Key_E]) {
        activeCamera->move(Glee3D::RealVector3D(0.0, 0.05 * activeCamera->position()._y, 0.0));
    }

    if(keyStatusMap[Qt::Key_Q]) {
        activeCamera->move(Glee3D::RealVector3D(0.0, -0.05 * activeCamera->position()._y, 0.0));
    }

    if(keyStatusMap[Qt::Key_W]) {
        activeCamera->move(Glee3D::RealVector3D(0.0, 0.0, 0.05 * activeCamera->position()._y));
    }

    if(keyStatusMap[Qt::Key_S]) {
        activeCamera->move(Glee3D::RealVector3D(0.0, 0.0, -0.05 * activeCamera->position()._y));
    }

    if(keyStatusMap[Qt::Key_A]) {
        activeCamera->move(Glee3D::RealVector3D(0.05 * activeCamera->position()._y, 0.0, 0.0));
    }

    if(keyStatusMap[Qt::Key_D]) {
        activeCamera->move(Glee3D::RealVector3D(-0.05 * activeCamera->position()._y, 0.0, 0.0));
    }

    activeCamera->setLookAt(Glee3D::RealVector3D(activeCamera->position()._x, 0, activeCamera->position()._z + activeCamera->position()._y * 2));

}
