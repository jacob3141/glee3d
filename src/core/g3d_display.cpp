///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of glee3d.                                           //
//    Copyright (C) 2012-2015 Jacob Dawid, jacob.dawid@omg-it.works          //
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

// Own includes
#include "g3d_display.h"
#include "g3d_skybox.h"
#include "g3d_matrixstate.h"
#include "g3d_texturestore.h"
#include "g3d_utilities.h"

// Standard includes
#include <iostream>

namespace Glee3D {
    Display::Display(QWidget *parent)
        : QGLWidget(parent),
          Logging("Display") {

        if(parent) {
            parent->setFocusProxy(this);
            setFocus();
        }

        _scene = 0;
        _activeCamera = new Camera();
        _mouseMoveMode = Normal;

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
        setMouseTracking(true);
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

    void Display::appendPostRenderEffect(PostRenderEffect *effect) {
        _postRenderEffects.append(effect);
    }

    Line3D Display::ray(QPoint displayPoint) {
        Line3D line;

        // Retrieve viewport, model view matrix and projection matrix.
        int viewport[4];        
        glGetIntegerv(GL_VIEWPORT, viewport);
        MatrixState cameraMatrixState = _activeCamera->cameraMatrixState();
        Vector3D frontPlanePoint, backPlanePoint;

        // Get the point at the front plane of the viewing frustrum.
        Utilities::unproject(Vector3D(displayPoint.x(), (viewport[3] - displayPoint.y()), 0.0),
                cameraMatrixState.modelviewMatrix(),
                cameraMatrixState.projectionMatrix(),
                viewport,
                frontPlanePoint);

        // Get the point at the back plane of the viewing frustrum.
        Utilities::unproject(Vector3D(displayPoint.x(), (viewport[3] - displayPoint.y()), 1.0),
                cameraMatrixState.modelviewMatrix(),
                cameraMatrixState.projectionMatrix(),
                viewport,
                backPlanePoint);

        // Calculate position and direction vector.
        line._positionVector = frontPlanePoint;
        line._directionVector = backPlanePoint - frontPlanePoint;
        return line;
    }

    Vector3D Display::point(QPoint displayPoint) {
        // Retrieve viewport, model view matrix and projection matrix.
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        MatrixState cameraMatrixState = _activeCamera->cameraMatrixState();
        Vector3D point;

        GLdouble x = (GLdouble)displayPoint.x();
        GLdouble y = (GLdouble)(viewport[3] - displayPoint.y());
        GLdouble z;
        // Access the depth component.
        glReadPixels((int)x, (int)y, 1, 1, GL_DEPTH_COMPONENT, GL_DOUBLE, &z);

        // Get the point at the front plane of the viewing frustrum.
        Utilities::unproject(Vector3D(x, y, z),
                             cameraMatrixState.modelviewMatrix(),
                             cameraMatrixState.projectionMatrix(),
                             viewport,
                             point);
        return point;
    }

    void Display::initializeGL() {
        configureOpenGL();

        foreach(PostRenderEffect *effect, _postRenderEffects) {
            effect->initialize();
        }

        information("Building per pixel renderer.");
        if(!_renderProgram.build(":/shaders/glsl/perpixellighting.vert.glsl",
                                 ":/shaders/glsl/perpixellighting.frag.glsl")) {
           error("Failed building GL render program.");
        }
    }

    void Display::resizeGL(int w, int h) {
        glViewport(0, 0, (GLint)w, (GLint)h);
        if(_activeCamera) {
            _activeCamera->setAspectRatio(w, h);
        }

        delete _frameBuffer;
        _frameBuffer = new FrameBuffer(w, h, true);
    }

    void Display::paintGL() {
        makeCurrent();
        _renderProgram.insert();
        _frameBuffer->clear();
        if(_scene) {
            _scene->lockScene();
            if(_activeCamera) {
                _activeCamera->applyCameraMatrix();
                SkyBox *s = _scene->skyBox();
                if(s) {
                    MatrixState matrixState(MatrixState::AutomaticSave | MatrixState::AutomaticRestore);
                    glMatrixMode(GL_MODELVIEW);
                    glTranslated(_activeCamera->position().x(),
                                 _activeCamera->position().y(),
                                 _activeCamera->position().z());
                    s->render();
                }

                QSet<LightSource*> lightSources = _scene->lightSources();
                int i = 0;
                foreach(LightSource* lightSource, lightSources) {
                    lightSource->activate(GL_LIGHT0 + i);
                    i++;
                    if(i > 7) {
                        i = 7;
                        // TODO: Decide which light sources to use in order
                        // to exceed OpenGLs limit of only eight light sources.

                        // TODO: This should be handled by own shaders.
                    }
                }

                // Render terrains.
                QSet<Terrain*> terrains = _scene->terrains();
                foreach(Terrain *terrain, terrains) {
                    terrain->render();
                }

                // Render objects.
                QSet<Entity*> objects = _scene->entities();
                foreach(Entity *object, objects) {
                    // Tell the object to render itself
                    object->render();
                }
            }
            _scene->unlockScene();
        }

        _frameBuffer->release();

        foreach(PostRenderEffect *effect, _postRenderEffects) {
            effect->apply(_frameBuffer);
        }

        _frameBuffer->copy(_frameBuffer->width(), _frameBuffer->height());
        swapBuffers();
    }

    void Display::refresh() {
        _framesPerSecondCounter++;
        QMetaObject::invokeMethod(this, "updateGL");
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
            _mouseMoveMode = Normal;
            if(_scene) {
                _scene->endDrag(ray(mouseEvent->pos()), point(mouseEvent->pos()));
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
        case Normal:
            hover(mouseEvent->pos());
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
            _scene->select(ray(displayPoint), point(displayPoint));
        }
    }

    void Display::hover(QPoint hoverPoint) {
        if(_scene) {
            _scene->hover(ray(hoverPoint), point(hoverPoint));
        }
    }

    void Display::drag(QPoint dragFrom, QPoint dragTo) {
        // Make sure any scene is set.
        if(_scene) {
            _scene->drag(ray(dragFrom), ray(dragTo), point(dragFrom), point(dragTo));
        }
    }

    void Display::keyPressEvent(QKeyEvent *keyEvent) {
        _keyStatusMap[keyEvent->key()] = true;
    }

    void Display::keyReleaseEvent(QKeyEvent *keyEvent) {
        _keyStatusMap[keyEvent->key()] = false;
    }

    void Display::configureOpenGL() {
        // Disable normalization since we will precalculate our normals.
        glDisable(GL_NORMALIZE);
        // Disable the default OpenGL lightning because we will provide our own
        glDisable(GL_LIGHTING);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_SMOOTH);
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POLYGON_SMOOTH);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glPointSize(1.0);
        glLineWidth(1.0);
    }
} // namespace Glee3D
