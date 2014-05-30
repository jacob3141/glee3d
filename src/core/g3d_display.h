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

#ifndef G3D_DISPLAY_H
#define G3D_DISPLAY_H

// Own includes
#include "g3d_program.h"
#include "effects/g3d_postrendereffect.h"
#include "g3d_scene.h"
#include "g3d_camera.h"
#include "g3d_framebuffer.h"

// Qt includes
#include <QGLWidget>
#include <QTimer>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QMap>
#include <QPoint>
#include <QKeyEvent>
#include <QList>

/**
 * @namespace Glee3D
 * Namespace for the Glee3D project.
 */
namespace Glee3D {
    /**
      * @class Display
      * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
      * @date 02.12.2012
      */
    class Display : public QGLWidget {
        Q_OBJECT
    public:
        /**
         * @attention You have to make sure you pass the parent widget so that this
         * class can add itself as a focus proxy and correctly process input events!
         * @param parent
         */
        Display(QWidget *parent = 0);

        /**
         * Sets the active camera for rendering the current scene.
         * @param camera The camera object.
         */
        void setActiveCamera(Camera *camera);

        /** @returns the active camera. */
        Camera *activeCamera();

        /** Sets the currently displayed scene.
         * @param scene The scene object.
         */
        void setScene(Scene *scene);

        /** @returns the current scene. */
        Scene *scene();

        /** Appends a post render effect. */
        void appendPostRenderEffect(PostRenderEffect *effect);

        enum MouseMoveMode {
            Normal,
            Drag
        };

        /**
         * Constructs a ray based on the viewing frustrum into 3d space.
         * @param displayPoint
         * @return
         */
        RealLine3D ray(QPoint displayPoint);

        /** Constructs a point based on the information in the depth buffer. */
        RealVector3D point(QPoint displayPoint);

    signals:
        /** This signal will be emitted whenever a new fps value is available. */
        void framesPerSecond(int fps);

    protected:
        /** @overload */
        void initializeGL();

        /** @overload */
        void resizeGL(int w, int h);

        /** @overload */
        void paintGL();

        /** @overload */
        void mousePressEvent(QMouseEvent *mouseEvent);

        /** @overload */
        void mouseReleaseEvent(QMouseEvent *mouseEvent);

        /** @overload */
        void mouseMoveEvent(QMouseEvent *mouseEvent);

        /** @overload */
        void keyPressEvent(QKeyEvent *keyEvent);

        /** @overload */
        void keyReleaseEvent(QKeyEvent *keyEvent);

    private slots:
        /** Schedules a redraw of the displayed scene, returns immediately. */
        void refresh();

        /** Processes a logic step. */
        void processLogic();

        /** Updates the current fps. */
        void updateFramesPerSecond();

        /** Handles a left button on-screen click. */
        void leftButtonClick(QPoint displayPoint);

        /** Handles a new mouse hover position on screen. */
        void hover(QPoint hoverPoint);

        /** Handles a drag event on the screen. */
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
        QList<PostRenderEffect*> _postRenderEffects;
    };
} // namespace Glee3D

#endif // G3D_DISPLAY_H
