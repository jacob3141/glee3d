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


#include "core/g3d_texturestore.h"
#include "core/g3d_scene.h"
#include "core/g3d_vector2d.h"
#include "core/g3d_rgbacolor.h"
#include "core/g3d_skybox.h"
#include "objects/g3d_cube.h"
#include "core/g3d_terrain.h"

#include "scene.h"


#include <QApplication>
#include <QJsonDocument>

Scene::Scene()
    : Glee3D::Scene() {

    Glee3D::SkyBox *skyBox = new Glee3D::SkyBox();
    skyBox->setTexture(Glee3D::SkyBox::BackX,  "skybox-xneg");
    skyBox->setTexture(Glee3D::SkyBox::FrontX, "skybox-xpos");
    skyBox->setTexture(Glee3D::SkyBox::BackY,  "skybox-yneg");
    skyBox->setTexture(Glee3D::SkyBox::FrontY, "skybox-ypos");
    skyBox->setTexture(Glee3D::SkyBox::BackZ,  "skybox-zneg");
    skyBox->setTexture(Glee3D::SkyBox::FrontZ, "skybox-zpos");
    setSkyBox(skyBox);

    Glee3D::LightSource *globalLight = new Glee3D::LightSource();
    globalLight->setPosition(Glee3D::RealVector3D(5.0, 1000.0, 2.0));
    globalLight->setAmbientLight(Glee3D::RgbaColor(1.0, 1.0, 1.0, 1.0));
    globalLight->setSpecularLight(Glee3D::RgbaColor(1.0, 1.0, 1.0, 1.0));
    globalLight->setDiffuseLight(Glee3D::RgbaColor(1.0, 1.0, 1.0, 1.0));
    insertLightSource(globalLight);

    Glee3D::Terrain *terrain = new Glee3D::Terrain();
    terrain->setScale(10.0);
    terrain->setMaterial(Glee3D::Material::standardMaterial(Glee3D::Material::Bronze));
    terrain->setTilingOffset(1.0);
    terrain->generate("../../heightmaps/heightmap.png");
    //terrain->material()->setAmbientReflection(Glee3D::RgbaColor(0.05, 0.05, 0.05, 1.0));
    //terrain->material()->setDiffuseReflection(Glee3D::RgbaColor(1.0, 1.0, 1.0, 1.0));
    //terrain->material()->setSpecularReflection(Glee3D::RgbaColor(0.0, 0.0, 0.0, 1.0));
    terrain->material()->setTextureId("brushed-aluminium-1");
    terrain->setPosition(Glee3D::RealVector3D(-terrain->width() * terrain->scale() / 2, 0.0, -terrain->height() * terrain->scale() / 2));
    insertTerrain(terrain);
}

void Scene::hover(Glee3D::RealLine3D ray, Glee3D::RealVector3D point) {
    bool somethingSelected = false;
    foreach(Glee3D::Object *o, _objects) {
        if(o->collides(ray)) {
            //o->setSelected(true);
            //o->material()->setEmission(Glee3D::RgbaColor(0.0, 0.2, 1.0, 1.0));
            somethingSelected = true;
        } else {
            //o->setSelected(false);
            //o->material()->setEmission(Glee3D::RgbaColor(0.0, 0.0, 0.0, 1.0));
        }
    }
    if(somethingSelected) {

    }
}

void Scene::processLogic(QMap<int, bool> keyStatusMap, Glee3D::Camera *activeCamera) {
    if(keyStatusMap[Qt::Key_Escape]) {
        QApplication::quit();
    }

//    foreach(Glee3D::Object *o, _objects) {
//        o->rotate(Glee3D::RealVector3D(0.1, 0.1, 0.1));
//    }

    if(keyStatusMap[Qt::Key_Space]) {

    }

    if(keyStatusMap[Qt::Key_E]) {
        activeCamera->move(Glee3D::RealVector3D(0.0, -0.2 * activeCamera->position()._y, 0.0));
    }

    if(keyStatusMap[Qt::Key_Q]) {
        activeCamera->move(Glee3D::RealVector3D(0.0, 0.2 * activeCamera->position()._y, 0.0));
    }

    if(keyStatusMap[Qt::Key_W]) {
        activeCamera->move(Glee3D::RealVector3D(0.0, 0.0, -0.1 * activeCamera->position()._y));
    }

    if(keyStatusMap[Qt::Key_S]) {
        activeCamera->move(Glee3D::RealVector3D(0.0, 0.0, 0.1 * activeCamera->position()._y));
    }

    if(keyStatusMap[Qt::Key_A]) {
        activeCamera->move(Glee3D::RealVector3D(-0.1 * activeCamera->position()._y, 0.0, 0.0));
    }

    if(keyStatusMap[Qt::Key_D]) {
        activeCamera->move(Glee3D::RealVector3D(0.1 * activeCamera->position()._y, 0.0, 0.0));
    }

    //activeCamera->setLookAt(activeCamera->position() + Glee3D::RealVector3D(0, -2, -1));
}
