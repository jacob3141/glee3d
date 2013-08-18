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

#include "display.h"
#include "GL/glu.h"
#include "skybox.h"
#include "matrixstate.h"

#include <iostream>

namespace Glee3D {
    Display::Display(QWidget *parent)
        : QGLWidget(parent) {

        if(parent) {
            parent->setFocusProxy(this);
            setFocus();
        }

        _scene = 0;
        _activeCamera = new Camera();
        _mouseMoveMode = Ignore;

        _framesPerSecondCounter = 0;
        _framesPerSecond = 0;

        _logicTimer.setInterval(20);
        _logicTimer.setSingleShot(false);
        connect(&_logicTimer, SIGNAL(timeout()), this, SLOT(processLogic()));

        _refreshTimer.setInterval(1000 / 60);
        _refreshTimer.setSingleShot(false);
        connect(&_refreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));

        _framesPerSecondTimer.setInterval(1000);
        _framesPerSecondTimer.setSingleShot(false);
        connect(&_framesPerSecondTimer, SIGNAL(timeout()), this, SLOT(updateFramesPerSecond()));

        _refreshTimer.start();
        _framesPerSecondTimer.start();
        _logicTimer.start();

        _frameBuffer = 0;
        setAutoBufferSwap(false);
    }

    void Display::setActiveCamera(Camera *camera) {
        _activeCamera = camera;
        _activeCamera->setAspectRatio(width(), height());
        updateGL();
    }

    Camera *Display::activeCamera() {
        return _activeCamera;
    }

    void Display::setScene(Scene *scene) {
        _scene = scene;
    }

    Scene *Display::scene() {
        return _scene;
    }

    void Display::appendEffect(Effect *effect) {
        _effects.append(effect);
    }

    RealLine3D Display::ray(QPoint displayPoint) {
        RealLine3D line;

        // Retrieve viewport, model view matrix and projection matrix.
        int viewport[4];        
        glGetIntegerv(GL_VIEWPORT, viewport);
        MatrixState cameraMatrixState = _activeCamera->matrixState();
        RealVector3D frontPlanePoint, backPlanePoint;

        // Get the point at the front plane of the viewing frustrum.
        gluUnProject((GLdouble)displayPoint.x(),
                     (GLdouble)(height() - displayPoint.y()),
                     0.0,
                     cameraMatrixState.modelviewMatrix()._data,
                     cameraMatrixState.projectionMatrix()._data,
                     viewport,
                     &frontPlanePoint._x, &frontPlanePoint._y, &frontPlanePoint._z);

        // Get the point at the back plane of the viewing frustrum.
        gluUnProject((GLdouble)displayPoint.x(),
                     (GLdouble)(height() - displayPoint.y()),
                     1.0,
                     cameraMatrixState.modelviewMatrix()._data,
                     cameraMatrixState.projectionMatrix()._data,
                     viewport,
                     &backPlanePoint._x, &backPlanePoint._y, &backPlanePoint._z);

        // Calculate position and direction vector.
        line._positionVector = frontPlanePoint;
        line._directionVector = backPlanePoint - frontPlanePoint;
        return line;
    }

    void Display::initializeGL() {        

        GLenum result = glewInit();
        if(result != GLEW_OK) {
            std::cout << "Error initializing glew: " << (const char*)glewGetErrorString(result) << std::endl;
        } else {
            std::cout << "glew initialized successfully." << std::endl;
        }

        if(glewIsSupported("GL_VERSION_2_0")) {
            std::cout << "OpenGL 2.0 supported\n" << std::endl;
        }

        if(!GLEW_EXT_framebuffer_object) {
            std::cout << "Framebuffer objects have to be supported." << std::endl;
        }

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glClearColor(0.0,0.0,0.0,1.0);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_CULL_FACE);
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POLYGON_SMOOTH);
        glPointSize(4.0);
        glLineWidth(2.0);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_NORMALIZE);

        foreach(Effect *effect, _effects) {
            effect->initialize();
        }
    }

    void Display::resizeGL(int w, int h) {
        std::cout << "Resizing to " << w << "x" << h << std::endl;
        glViewport(0, 0, (GLint)w, (GLint)h);
        if(_activeCamera) {
            _activeCamera->setAspectRatio(w, h);
        }

        delete _frameBuffer;
        _frameBuffer = new FrameBuffer(w, h, true);
    }

    void Display::paintGL() {
        _frameBuffer->clear();
        if(_scene) {
            _scene->lockScene();
            if(_activeCamera) {
                MatrixState cameraMatrixState = _activeCamera->matrixState();
                cameraMatrixState.load();

                SkyBox *s = _scene->skyBox();
                if(s) {
                    s->setPosition(_activeCamera->position());
                    s->applyModelView();
                    s->render();
                }

                cameraMatrixState.load();
                QSet<LightSource*> lightSources = _scene->lightSources();
                int i = 0;
                foreach(LightSource* lightSource, lightSources) {
                    lightSource->activate(GL_LIGHT0 + i);
                    i++;
                    if(i > 7) {
                        i = 7;
                        // TODO: Decide which light sources to use in order
                        // to exceed OpenGLs limit of only eight light sources.
                    }
                }

                // Render objects.
                QSet<Object*> objects = _scene->objects();
                foreach(Object *object, objects) {
                    cameraMatrixState.load();
                    object->applyModelView();
                    object->render();
                }

                cameraMatrixState.load();
                glDisable(GL_LIGHTING);
                glDisable(GL_TEXTURE_2D);
                glBegin(GL_LINES);
                glColor3f(0.0, 1.0, 0.0);
                for(int zz = -80; zz <= 80; zz++) {
                    glVertex3i(-80, 0, zz);
                    glVertex3i( 80, 0, zz);
                }
                for(int zz = -80; zz <= 80; zz++) {
                    glVertex3i(zz, 0, -80);
                    glVertex3i(zz, 0,  80);
                }
                glEnd();
                glEnable(GL_LIGHTING);
                glEnable(GL_TEXTURE_2D);
            }
            _scene->unlockScene();
        }
        _frameBuffer->release();

        foreach(Effect *effect, _effects) {
            effect->apply(_frameBuffer);
        }

        _frameBuffer->copy(_frameBuffer->width(), _frameBuffer->height());
        swapBuffers();
    }

    void Display::refresh() {
        _framesPerSecondCounter++;
        updateGL();
    }

    void Display::processLogic() {
        if(_scene) {
            _scene->lockScene();
            _scene->processLogic(_keyStatusMap, _activeCamera);
            _scene->unlockScene();
        }
    }

    void Display::mousePressEvent(QMouseEvent *mouseEvent) {
        Qt::MouseButton mouseButton = mouseEvent->button();
        switch(mouseButton) {
        case Qt::LeftButton:
            _mouseMoveMode = Drag;
            _dragFrom = mouseEvent->pos();
            leftButtonClick(mouseEvent->pos());
            break;
        default:
            break;
        }
    }

    void Display::mouseReleaseEvent(QMouseEvent *mouseEvent) {
        Qt::MouseButton mouseButton = mouseEvent->button();

        switch(mouseButton) {
        case Qt::LeftButton:
            _mouseMoveMode = Ignore;
            if(_scene) {
                _scene->endDrag();
            }
            break;
        default:
            break;
        }
    }

    void Display::mouseMoveEvent(QMouseEvent *mouseEvent) {
        Q_UNUSED(mouseEvent);

        switch(_mouseMoveMode) {
        default:
        case Ignore:
            break;
        case Drag:
            QPoint dragTo = mouseEvent->pos();
            drag(_dragFrom, dragTo);
            _dragFrom = dragTo;
            break;
        }
    }

    void Display::updateFramesPerSecond() {
        _framesPerSecond = _framesPerSecondCounter;
        _framesPerSecondCounter = 0;
        emit framesPerSecond(_framesPerSecond);
    }

    void Display::leftButtonClick(QPoint displayPoint) {
        // Make sure any scene is set.
        if(_scene) {
            _scene->select(ray(displayPoint));
        }
    }

    void Display::drag(QPoint dragFrom, QPoint dragTo) {
        // Make sure any scene is set.
        if(_scene) {
            _scene->drag(ray(dragFrom), ray(dragTo));
        }
    }

    void Display::keyPressEvent(QKeyEvent *keyEvent) {
        _keyStatusMap[keyEvent->key()] = true;
    }

    void Display::keyReleaseEvent(QKeyEvent *keyEvent) {
        _keyStatusMap[keyEvent->key()] = false;
    }
}
