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

#ifndef DISPLAY_H
#define DISPLAY_H

// Own includes
#include "program.h"
#include "effect.h"
#include "scene.h"
#include "camera.h"
#include "framebuffer.h"

// Qt includes
#include <QGLWidget>
#include <QTimer>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QMap>
#include <QPoint>
#include <QKeyEvent>
#include <QList>

namespace Glee3D {
/**
  * @class Display
  * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
  * @date 02.12.2012
  */
class Display : public QGLWidget {
    Q_OBJECT
public:
    Display(QWidget *parent = 0);

    void setActiveCamera(Camera *camera);
    Camera *activeCamera();

    void setScene(Scene *scene);
    Scene *scene();

    void appendEffect(Effect *effect);

    enum MouseMoveMode {
        Ignore,
        Drag
    };

    RealLine3D ray(QPoint displayPoint);

signals:
    void framesPerSecond(int fps);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *mouseEvent);
    void mouseReleaseEvent(QMouseEvent *mouseEvent);
    void mouseMoveEvent(QMouseEvent *mouseEvent);

    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);

private slots:
    void refresh();
    void processLogic();
    void updateFramesPerSecond();
    void leftButtonClick(QPoint displayPoint);
    void drag(QPoint dragFrom, QPoint dragTo);

private:
    Scene *_scene;
    Camera *_activeCamera;
    FrameBuffer *_frameBuffer;

    QTimer _refreshTimer;
    QTimer _logicTimer;
    QTimer _framesPerSecondTimer;
    QPoint _dragFrom;
    int _framesPerSecondCounter;
    int _framesPerSecond;

    MouseMoveMode _mouseMoveMode;

    QMap<int, bool> _keyStatusMap;
    QList<Effect*> _effects;
};

} // namespace Glee3D

#endif // DISPLAY_H
