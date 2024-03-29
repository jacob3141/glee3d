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
    _display->activeCamera()->setPosition(Glee3D::Vector3D(0.0, 200.0, 2000.0));
    _display->activeCamera()->setLookAt(Glee3D::Vector3D(0.0, 0.0, 0.0));

    Glee3D::TextureStore& textureStore = Glee3D::TextureStore::instance();
    textureStore.loadTexture(*_display, "../../skybox/gray/xneg.png", "skybox-xneg");
    textureStore.loadTexture(*_display, "../../skybox/gray/xpos.png", "skybox-xpos");
    textureStore.loadTexture(*_display, "../../skybox/gray/yneg.png", "skybox-yneg");
    textureStore.loadTexture(*_display, "../../skybox/gray/ypos.png", "skybox-ypos");
    textureStore.loadTexture(*_display, "../../skybox/gray/zneg.png", "skybox-zneg");
    textureStore.loadTexture(*_display, "../../skybox/gray/zpos.png", "skybox-zpos");

    textureStore.loadTexture(*_display, "../../../../assets/textures/blank.png", "blank");

    textureStore.loadTexture(*_display, "../../../../assets/textures/brushed-aluminium-1.jpg", "brushed-aluminium-1");
    textureStore.loadTexture(*_display, "../../../../assets/textures/brushed-aluminium-2.jpg", "brushed-aluminium-2");
    textureStore.loadTexture(*_display, "../../../../assets/textures/brushed-aluminium-3.jpg", "brushed-aluminium-3");

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

