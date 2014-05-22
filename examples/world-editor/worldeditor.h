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

#ifndef WORLDEDITOR_H
#define WORLDEDITOR_H

#include "g3d_display.h"

#include "scene.h"

#include <QMainWindow>

namespace Ui {
class WorldEditor;
}

class WorldEditor : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit WorldEditor(QWidget *parent = 0);
    ~WorldEditor();
    
private:
    Ui::WorldEditor *ui;

    Glee3D::Display *_display;
    Glee3D::Display *_topDownViewDisplay;
    Scene *_scene;
};

#endif // WORLDEDITOR_H
