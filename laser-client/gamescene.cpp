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
#include "particle.h"
#include "vector2d.h"
#include "rgbacolor.h"
#include "skybox.h"
#include "laserbeam.h"
#include "asteroid.h"

#include <QApplication>

GameScene::GameScene(Glee3D::Display *display)
    : Glee3D::Scene() {

    Glee3D::SkyBox *skyBox = new Glee3D::SkyBox();
    skyBox->loadTexture(Glee3D::SkyBox::BackX, "../../galaxy/galaxy-X.tga", display);
    skyBox->loadTexture(Glee3D::SkyBox::FrontX, "../../galaxy/galaxy+X.tga", display);
    skyBox->loadTexture(Glee3D::SkyBox::BackY, "../../galaxy/galaxy-Y.tga", display);
    skyBox->loadTexture(Glee3D::SkyBox::FrontY, "../../galaxy/galaxy+Y.tga", display);
    skyBox->loadTexture(Glee3D::SkyBox::BackZ, "../../galaxy/galaxy-Z.tga", display);
    skyBox->loadTexture(Glee3D::SkyBox::FrontZ, "../../galaxy/galaxy+Z.tga", display);
    setSkyBox(skyBox);

    _light = new Glee3D::LightSource();
    _light->setPosition(Glee3D::RealVector3D(2.0, 2.0, 3.0));
    _light->setAmbientLight(Glee3D::RgbaColor(0.0, 0.0, 0.0, 0.0));
    _light->setSpecularLight(Glee3D::RgbaColor(1.0, 1.0, 1.0, 1.0));
    _light->setDiffuseLight(Glee3D::RgbaColor(1.0, 1.0, 1.0, 1.0));
    _light->setLightSourceType(Glee3D::LightSource::Spotlight);
    _light->setSpotCutoff(10.0);
    _light->setSpotExponent(0.0);

    insertLightSource(_light);
    _redLight = new Glee3D::LightSource();
    _redLight->setAmbientLight(Glee3D::RgbaColor(0.0, 0.0, 0.0, 0.0));
    _redLight->setSpecularLight(Glee3D::RgbaColor(1.0, 0.0, 0.0, 1.0));
    _redLight->setDiffuseLight(Glee3D::RgbaColor(1.0, 0.0, 0.0, 1.0));

    _ship = new Glee3D::Cylinder();
    _ship->generate(0.5, 0.2, 128);
    //_ship->setPosition(Glee3D::RealVector3D(0.0, 0.0, -50.0));
    _ship->setMaterial(new Glee3D::ChromeMaterial());
    _ship->material()->loadTexture("../../textures/chrome.png", *display);
    _ship->setName("Player Ship");

    insertObject(_ship);

    for(int i = 0; i < 10; i++) {
        Asteroid *a = new Asteroid();
        a->generate(40.0 + rand() % 10, 0.1 * (double)(rand() % 10 + 10) + 0.5, 64);
        a->setPosition(Glee3D::RealVector3D((rand() % 50 - 25.0)*100, (rand() % 50 - 20)*100, (rand() % 50 - 25.0)*100));
        a->rotate(Glee3D::RealVector3D(90, 180, 90));
        a->setSpin(Glee3D::RealVector3D(rand() % 3,rand() % 3,rand() % 3));
        a->setVelocity(1.0 + rand() % 20);
        a->setMaterial(new Glee3D::ChromeMaterial());
        a->material()->setAmbientReflection(Glee3D::RgbaColor(0.0, 0.0, 0.0, 1.0));
        a->material()->loadTexture("../../textures/galvanized.png", *display);
        insertObject(a);
    }

    connect(&_redLightBlinkTimer, SIGNAL(timeout()), this, SLOT(blinkRedLight()));
    _redLightBlinkTimer.setSingleShot(false);
    _redLightBlinkTimer.setInterval(1000);
    _redLightBlinkTimer.start();
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

    for(int i = 0; i < _missiles.size();) {
        Glee3D::Object *m = _missiles[i];
        m->moveForward(m->velocity());
        if((m->position() - _ship->position()).length() > 1000.0) {
            _missiles.removeAll(m);
            removeObject(m);
            delete m;
        } else {
            i++;
        }
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

    if(keyStatusMap[Qt::Key_F]) {
        shoot();
    }

    Glee3D::RealVector3D cameraDestination = _ship->position() - _ship->front() * 3.0;
    activeCamera->setPosition(cameraDestination * 0.7 + activeCamera->position() * 0.3);
    activeCamera->setUp(_ship->up() * 0.2 + activeCamera->up() * 0.8);
    activeCamera->setLookAt(_ship->position());

    _light->setPosition(_ship->position());
    _light->setSpotDirecton(_ship->front());

    _redLight->setPosition(_ship->position() - _ship->front() * 2);
}

void GameScene::shoot() {
    Glee3D::RealVector3D side = _ship->up().crossProduct(_ship->front());

    LaserBeam *b = new LaserBeam();
    b->setPosition(_ship->position() + side * 0.3);
    b->setRotation(_ship->rotation());
    b->setVelocity(_ship->velocity() + 5.0);
    _missiles.append(b);
    insertObject(b);

    b = new LaserBeam();
    b->setPosition(_ship->position() - side * 0.3);
    b->setRotation(_ship->rotation());
    b->setVelocity(_ship->velocity() + 5.0);
    _missiles.append(b);
    insertObject(b);
}

void GameScene::blinkRedLight() {
    _redLight->switchOnOff();
}
