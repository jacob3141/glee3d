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

#include "worldeditor.h"
#include "ui_worldeditor.h"

#include "core/g3d_texturestore.h"

#include <QMdiSubWindow>

WorldEditor::WorldEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WorldEditor)
{
    ui->setupUi(this);

    _display = new Glee3D::Display(this);
    _display->activeCamera()->setPosition(Glee3D::RealVector3D(0.0, 200.0, 10.0));
    _display->activeCamera()->setLookAt(Glee3D::RealVector3D(0.0, 0.0, 0.0));

    Glee3D::TextureStore& textureStore = Glee3D::TextureStore::instance();
    textureStore.loadTexture(*_display, "../../skybox/sky/xneg.png", "skybox-xneg");
    textureStore.loadTexture(*_display, "../../skybox/sky/xpos.png", "skybox-xpos");
    textureStore.loadTexture(*_display, "../../skybox/sky/yneg.png", "skybox-yneg");
    textureStore.loadTexture(*_display, "../../skybox/sky/ypos.png", "skybox-ypos");
    textureStore.loadTexture(*_display, "../../skybox/sky/zneg.png", "skybox-zneg");
    textureStore.loadTexture(*_display, "../../skybox/sky/zpos.png", "skybox-zpos");
    textureStore.loadTexture(*_display, "../../textures/green.png", "green");

    _scene = new Scene();
    _display->setScene(_scene);

    setCentralWidget(_display);
    connect(_display, SIGNAL(framesPerSecond(int)), this, SLOT(updateFps(int)));
}

WorldEditor::~WorldEditor()
{
    delete ui;
}

void WorldEditor::updateFps(int fps)
{
    this->setWindowTitle(QString("World Editor (%1 fps)").arg(fps));
}

