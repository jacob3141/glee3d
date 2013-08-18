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

#include "gamescene.h"
#include "vector2d.h"
#include "rgbacolor.h"
#include "skybox.h"
#include "cube.h"

#include <QApplication>

GameScene::GameScene(Glee3D::Display *display)
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
    globalLight->setPosition(Glee3D::RealVector3D(20.0, 20.0, 30.0));
    globalLight->setAmbientLight(Glee3D::RgbaColor(4.0, 4.0, 4.0, 0.0));
    globalLight->setSpecularLight(Glee3D::RgbaColor(1.0, 1.0, 1.0, 1.0));
    globalLight->setDiffuseLight(Glee3D::RgbaColor(1.0, 1.0, 1.0, 1.0));
    insertLightSource(globalLight);

    _light = new Glee3D::LightSource();
    _light->setPosition(Glee3D::RealVector3D(2.0, 2.0, 3.0));
    _light->setAmbientLight(Glee3D::RgbaColor(0.0, 0.0, 0.0, 0.0));
    _light->setSpecularLight(Glee3D::RgbaColor(1.0, 1.0, 1.0, 1.0));
    _light->setDiffuseLight(Glee3D::RgbaColor(1.0, 1.0, 1.0, 1.0));
    _light->setLightSourceType(Glee3D::LightSource::Spotlight);
    _light->setSpotCutoff(10.0);
    _light->setSpotExponent(0.0);
    insertLightSource(_light);

    _ship = new Glee3D::Cylinder();
    _ship->generate(0.5, 0.2, 128);
    //_ship->setPosition(Glee3D::RealVector3D(0.0, 0.0, -50.0));
    _ship->setMaterial(new Glee3D::ChromeMaterial());
    _ship->material()->loadTexture("../../textures/chrome.png", *display);
    _ship->setName("Player Ship");

    insertObject(_ship);

    for(int kk = -80; kk <= 80; kk += 20) {
        for(int ll = -80; ll <= 80; ll += 20) {
            Glee3D::Cube *cube = new Glee3D::Cube();
            cube->generate(10.0);
            cube->setMaterial(new Glee3D::CopperMaterial());
            cube->material()->loadTexture("../../textures/chrome.png", *display);
            cube->setPosition(Glee3D::RealVector3D((float)kk, 5.0, (float)ll));
            insertObject(cube);
        }
    }
}

void GameScene::select(Glee3D::RealLine3D line) {
    bool somethingSelected = false;
    foreach(Glee3D::Object *o, _objects) {
        if(o->collides(line)) {
            o->setSelected(true);
            o->material()->setEmission(Glee3D::RgbaColor(0.0, 0.2, 1.0, 1.0));
            somethingSelected = true;
        } else {
            o->setSelected(false);
            o->material()->setEmission(Glee3D::RgbaColor(0.0, 0.0, 0.0, 1.0));
        }
    }

    if(somethingSelected) {
    }
}

void GameScene::drag(Glee3D::RealLine3D from, Glee3D::RealLine3D to) {
    Q_UNUSED(from);
    Q_UNUSED(to);
}

void GameScene::endDrag() {
}

void GameScene::processLogic(QMap<int, bool> keyStatusMap, Glee3D::Camera *activeCamera) {
    if(keyStatusMap[Qt::Key_Escape]) {
        QApplication::quit();
    }

    foreach(Glee3D::Object *o, _objects) {
        //o->rotate(o->spin());
        o->move(o->front() * o->velocity());
    }


    if(keyStatusMap[Qt::Key_Space]) {
        if(_ship->velocity() < 20.0)
            _ship->accelerate(1.1);
    }

    if(keyStatusMap[Qt::Key_E]) {
        if(_ship->velocity() > 0.1)
            _ship->accelerate(0.99);
    }

    double manoeuvrability = 2.0;

    if(keyStatusMap[Qt::Key_W]) {
        _ship->rotate(Glee3D::RealVector3D(-manoeuvrability, 0.0, 0.0));
    }

    if(keyStatusMap[Qt::Key_S]) {
        _ship->rotate(Glee3D::RealVector3D(manoeuvrability, 0.0, 0.0));
    }

    if(keyStatusMap[Qt::Key_A]) {
        _ship->rotate(Glee3D::RealVector3D(0.0, 0.0, -manoeuvrability * 2.0));
    }

    if(keyStatusMap[Qt::Key_D]) {
        _ship->rotate(Glee3D::RealVector3D(0.0, 0.0, manoeuvrability * 2.0));
    }

    Glee3D::RealVector3D cameraDestination = _ship->position() - _ship->front() * 3.0;
    activeCamera->setPosition(cameraDestination * 0.7 + activeCamera->position() * 0.3);
    activeCamera->setUp(_ship->up() * 0.2 + activeCamera->up() * 0.8);
    activeCamera->setLookAt(_ship->position());

    _light->setPosition(_ship->position());
    _light->setSpotDirecton(_ship->front());
}
