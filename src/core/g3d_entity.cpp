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
#include "g3d_entity.h"

// Qt includes
#include <QGLWidget>

namespace Glee3D {
    Entity::Entity()
        : Anchored(),
          Oriented(),
          Renderable(),
          Texturizable(),
          Serializable(),
          Logging("Entity") {
        _mesh = 0;
        _parent = 0;
        _compiledMesh = 0;
        _selected = false;
    }

    Entity::~Entity() {
        delete _mesh;
        delete _compiledMesh;
    }

    void Entity::setName(QString name) {
        _name = name;
    }

    QString Entity::name() {
        return _name;
    }

    void Entity::render(RenderMode renderMode) {
        Q_UNUSED(renderMode);
        if(!_visible)
            return;

        if(!_compiledMesh) {
            compile();
        }

        if(_compiledMesh) {
            if(_material) {
                _material->activate();
            }

            _compiledMesh->render();
        }

        foreach(Entity* entity, _children) {
            entity->render(renderMode);
        }
    }

    bool Entity::selected() {
        return _selected;
    }

    void Entity::setSelected(bool on) {
        _selected = on;
    }

    void Entity::moveForward(double units) {
        _position += (front() * units);
    }

    void Entity::moveBackward(double units) {
        _position += (- front() * units);
    }

    bool Entity::collides(const Line3D& line) {
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

//                Plane3D p(_vertices[i1], _vertices[i2], _vertices[i3]);
//                Vector3D i = p.intersection(line);
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

    void Entity::compile() {
        if(_compiledMesh) {
            delete _compiledMesh;
            _compiledMesh = 0;
        }

        if(_mesh) {
            _compiledMesh = new CompiledMesh(_mesh);
        }
    }

    Mesh *Entity::mesh() {
        return _mesh;
    }

    void Entity::setMesh(Mesh *mesh) {
        _mesh = mesh;
    }

    void Entity::subordinate(Entity *child) {
        if(child) {
            child->_parent = this;
            _children.append(child);
        }
    }

    QString Entity::className() {
        return "Entity";
    }

    QJsonObject Entity::serialize() {
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
        jsonObject["rotation"]  = _rotationAnglesAroundAxis.serialize();

        return jsonObject;
    }

    bool Entity::deserialize(QJsonObject jsonObject) {
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
                        error("Couldn't deserialize mesh.");
                        return false;
                    }
                }

                if(jsonObject.contains("material")) {
                    _material = new Material();
                    if(!_material->deserialize(jsonObject["material"].toObject())) {
                        _deserializationError = _material->deserializationError();
                        error("Couldn't deserialize material");
                        return false;
                    }
                }

                if(!_rotationAnglesAroundAxis.deserialize(jsonObject["rotation"].toObject())) {
                    _deserializationError = _rotationAnglesAroundAxis.deserializationError();
                    return false;
                }

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
