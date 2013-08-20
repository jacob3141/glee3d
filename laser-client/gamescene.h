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

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "g3d_display.h"
#include "g3d_scene.h"
#include "g3d_cube.h"
#include "g3d_cylinder.h"
#include <QList>

class GameScene : public Glee3D::Scene {
    Q_OBJECT
public:
    GameScene(Glee3D::Display *display);

    void select(Glee3D::RealLine3D line);
    void drag(Glee3D::RealLine3D from, Glee3D::RealLine3D to);
    void endDrag();

    void processLogic(QMap<int, bool> keyStatusMap, Glee3D::Camera *activeCamera);

private:
};

#endif // GAMESCENE_H
