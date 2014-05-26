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

// Own includes
#include "g3d_object.h"
#include "g3d_matrixstate.h"

// Qt includes
#include <QGLWidget>

// OpenGL includes
#include "GL/glu.h"

namespace Glee3D {
    Object::Object()
        : Anchored(),
          Renderable(),
          Serializable() {
        _mesh = 0;
        _compiledMesh = 0;
        _selected = false;
        _rotation = RealVector3D(0.0, 0.0, 0.0);
        _spin = RealVector3D(0.0, 0.0, 0.0);
        _velocity = 0.0;
        _visible = true;
    }

    Object::~Object() {
        delete _mesh;
        delete _compiledMesh;
    }

    void Object::setName(QString name) {
        _name = name;
    }

    QString Object::name() {
        return _name;
    }

    void Object::applyModelView() {
        glMatrixMode(GL_MODELVIEW);
        glTranslated(_position._x, _position._y, _position._z);
        glRotated(_rotation._x, 1.0, 0.0, 0.0);
        glRotated(_rotation._y, 0.0, 1.0, 0.0);
        glRotated(_rotation._z, 0.0, 0.0, 1.0);
    }

    void Object::render(RenderMode renderMode) {
        Q_UNUSED(renderMode);
        if(!_visible)
            return;

        if(_compiledMesh) {
            if(_material) {
                _material->activate();
            }

            _compiledMesh->render();
        }
    }

    void Object::setRotation(RealVector3D value) {
        _rotation = value;
    }

    void Object::rotate(RealVector3D delta) {
        MatrixState matrixState;
        matrixState.save();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotated(_rotation._x, 1.0, 0.0, 0.0);
        glRotated(_rotation._y, 0.0, 1.0, 0.0);
        glRotated(_rotation._z, 0.0, 0.0, 1.0);

        glRotated(delta._x, 1.0, 0.0, 0.0);
        glRotated(delta._y, 0.0, 1.0, 0.0);
        glRotated(delta._z, 0.0, 0.0, 1.0);

        float m[16];
        glGetFloatv(GL_MODELVIEW_MATRIX , m);

        _rotation._y = asin(m[8]) * 180.0 / M_PI;
        if( _rotation._y < 90.0 ) {
            if( _rotation._y > -90.0 ) {
                _rotation._x = atan2(-m[9], m[10]) * 180.0 / M_PI;
                _rotation._z = atan2(-m[4], m[0]) * 180.0 / M_PI;
            } else {
                _rotation._x = -atan2(m[1], m[5]) * 180.0 / M_PI;
                _rotation._z = 0;
            }
        } else {
            _rotation._x = atan2(m[1], m[5])*180.0 / M_PI;
            _rotation._z = 0;
        }

        matrixState.load();
    }

    RealVector3D Object::rotation() {
        return _rotation;
    }

    RealVector3D Object::front() {
        RealVector3D result;
        double rot_x = _rotation._x * 2 * M_PI / 360.0;
        double rot_y = _rotation._y * 2 * M_PI / 360.0;

        result._x = sin(rot_y);
        result._y = - sin(rot_x) * cos(rot_y);
        result._z = cos(rot_x) * cos(rot_y);
        return result;
    }

    RealVector3D Object::up() {
        RealVector3D result;
        double rot_x = _rotation._x * 2 * M_PI / 360.0;
        double rot_y = _rotation._y * 2 * M_PI / 360.0;
        double rot_z = _rotation._z * 2 * M_PI / 360.0;

        result._x = - cos(rot_y) * sin(rot_z);
        result._y = - sin(rot_z) * sin(rot_y) * sin(rot_x) + cos(rot_x) * cos(rot_z);
        result._z = cos(rot_x) * sin(rot_y) * sin(rot_z) + cos(rot_z) * sin(rot_x);
        return result;
    }

    double Object::velocity() {
        return _velocity;
    }

    void Object::accelerate(double value) {
        if(_velocity < 0.001)
            _velocity = 0.001;
        _velocity *= value;
        if(_velocity < 0.001)
            _velocity = 0.0;
    }

    void Object::setVelocity(double value) {
        _velocity = value;
    }

    RealVector3D Object::spin() {
        return _spin;
    }

    void Object::setSpin(RealVector3D spin) {
        _spin = spin;
    }

    bool Object::selected() {
        return _selected;
    }

    void Object::setSelected(bool on) {
        _selected = on;
    }

    void Object::moveForward(double units) {
        _position += (front() * units);
    }

    void Object::moveBackward(double units) {
        _position += (- front() * units);
    }

    void Object::setMaterial(Material *material) {
        _material = material;
    }

    Material *Object::material() {
        return _material;
    }

    bool Object::collides(const RealLine3D& line) {
        if(!_compiledMesh)
            return false;

        double area = ((_position - line._positionVector).crossProduct(line._directionVector)).length();
        double distance = area / line._directionVector.length();

        if(distance < _compiledMesh->collisionRadius()) {
            return true;

//            for(int i = 0; i < _triangleCount; i++) {
//                int i1 = _triangles[i]._indices[0];
//                int i2 = _triangles[i]._indices[1];
//                int i3 = _triangles[i]._indices[2];

//                RealPlane3D p(_vertices[i1], _vertices[i2], _vertices[i3]);
//                RealVector3D i = p.intersection(line);
//                double alpha = i._x / p._directionVector1._x;
//                double beta  = i._x / p._directionVector2._x;

//                if(alpha >= 0.0 && beta >= 0.0) {
//                    if(alpha + beta < 1.0) {
//                        return true;
//                    }
//                }
//            }
        }
        return false;
    }

    void Object::compile() {
        if(_compiledMesh) {
            delete _compiledMesh;
            _compiledMesh = 0;
        }

        if(_mesh) {
            _compiledMesh = _mesh->compile();
        }
    }

    QString Object::className() {
        return "Object";
    }

    QJsonObject Object::serialize() {
        QJsonObject jsonObject;
        jsonObject["class"] = className();

        jsonObject["name"]      = _name;
        jsonObject["selected"]  = _selected;
        jsonObject["visible"]   = _visible;
        if(_mesh) {
            jsonObject["mesh"]      = _mesh->serialize();
        }
        if(_material) {
            jsonObject["material"]  = _material->serialize();
        }
        jsonObject["rotation"]  = _rotation.serialize();
        jsonObject["spin"]      = _spin.serialize();
        jsonObject["velocity"]  = _velocity;

        return jsonObject;
    }

    bool Object::deserialize(QJsonObject jsonObject) {
        if(!jsonObject.contains("class")) {
            _deserializationError = Serializable::NoClassSpecified;
            return false;
        }

        if(jsonObject.contains("name")
        && jsonObject.contains("selected")
        && jsonObject.contains("visible")
        && jsonObject.contains("rotation")
        && jsonObject.contains("spin")
        && jsonObject.contains("velocity")) {
            if(jsonObject["class"] == className()) {
                _name       = jsonObject["name"].toString();
                _selected   = jsonObject["selected"].toBool();
                _visible    = jsonObject["visible"].toBool();

                if(jsonObject.contains("mesh")) {
                    if(_mesh) {
                        delete _mesh;
                    }
                    _mesh = new Mesh();
                    if(!_mesh->deserialize(jsonObject["mesh"].toObject())) {
                        _deserializationError = _mesh->deserializationError();
                        qDebug() << className() << ": Couldn't deserialize mesh";
                        return false;
                    }
                }

                if(jsonObject.contains("material")) {
                    _material = new Material();
                    if(!_material->deserialize(jsonObject["material"].toObject())) {
                        _deserializationError = _material->deserializationError();
                        qDebug() << className() << ": Couldn't deserialize material";
                        return false;
                    }
                }

                if(!_rotation.deserialize(jsonObject["rotation"].toObject())) {
                    _deserializationError = _rotation.deserializationError();
                    return false;
                }

                if(!_spin.deserialize(jsonObject["spin"].toObject())) {
                    _deserializationError = _spin.deserializationError();
                    return false;
                }

                _velocity = jsonObject["velocity"].toDouble();

                compile();
                _deserializationError = Serializable::NoError;
                return true;
            } else {
                _deserializationError = Serializable::WrongClass;
                return false;
            }
        } else {
            _deserializationError = Serializable::MissingElements;
            return false;
        }
    }
} // namespace Glee3D
