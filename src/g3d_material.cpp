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
#include "g3d_display.h"
#include "g3d_material.h"
#include "g3d_texturestore.h"

// Qt includes
#include <QGLWidget>

namespace Glee3D {
    Material::Material()
        : Serializable() {
        _textureId          = "";
        _ambientReflection  = RgbaColor();
        _diffuseReflection  = RgbaColor();
        _specularReflection = RgbaColor();
        _emission           = RgbaColor();
    }

    void Material::activate() {
        float ambientReflection[]
                = { _ambientReflection._red,
                    _ambientReflection._green,
                    _ambientReflection._blue,
                    _ambientReflection._alpha };
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambientReflection);

        float diffuseReflection[]
                = { _diffuseReflection._red,
                    _diffuseReflection._green,
                    _diffuseReflection._blue,
                    _diffuseReflection._alpha };
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseReflection);

        float specularReflection[]
                = { _specularReflection._red,
                    _specularReflection._green,
                    _specularReflection._blue,
                    _specularReflection._alpha };
        glMaterialfv(GL_FRONT, GL_SPECULAR, specularReflection);
        glMaterialf(GL_FRONT, GL_SHININESS, _shininess);

        float emission[]
                = { _emission._red,
                    _emission._green,
                    _emission._blue,
                    _emission._alpha };
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);

        TextureStore::instance().activateTexture(_textureId);
    }

    RgbaColor Material::ambientReflection() {
        return _ambientReflection;
    }

    RgbaColor Material::diffuseReflection() {
        return _diffuseReflection;
    }

    RgbaColor Material::specularReflection() {
        return _specularReflection;
    }

    float Material::shininess() {
        return _shininess;
    }

    RgbaColor Material::emission() {
        return _emission;
    }

    QString Material::textureId() {
        return _textureId;
    }

    void Material::setAmbientReflection(RgbaColor ambientReflection) {
        _ambientReflection = ambientReflection;
    }

    void Material::setDiffuseReflection(RgbaColor diffuseReflection) {
        _diffuseReflection = diffuseReflection;
    }

    void Material::setSpecularReflection(RgbaColor specularReflection) {
        _specularReflection = specularReflection;
    }

    void Material::setShininess(float shininess) {
        _shininess = shininess;
    }

    void Material::setEmission(RgbaColor emission) {
        _emission = emission;
    }

    void Material::setTextureId(QString textureId) {
        _textureId = textureId;
    }

    QString Material::className() {
        return "Material";
    }

    QJsonObject Material::serialize() {
        QJsonObject jsonObject;
        jsonObject["class"] = className();

        jsonObject["ambientReflection"]     = _ambientReflection.serialize();
        jsonObject["diffuseReflection"]     = _diffuseReflection.serialize();
        jsonObject["specularReflection"]    = _specularReflection.serialize();
        jsonObject["shininess"]             = _shininess;
        jsonObject["emission"]              = _emission.serialize();
        jsonObject["textureId"]             = _textureId;
        return jsonObject;
    }

    bool Material::deserialize(QJsonObject jsonObject) {
        if(!jsonObject.contains("class")) {
            _deserializationError = Serializable::NoClassSpecified;
            return false;
        }

        if(jsonObject.contains("ambientReflection")
        && jsonObject.contains("diffuseReflection")
        && jsonObject.contains("specularReflection")
        && jsonObject.contains("shininess")
        && jsonObject.contains("emission")
        && jsonObject.contains("textureId")) {
            if(jsonObject["class"] == className()) {
                if(!_ambientReflection.deserialize(jsonObject.value("ambientReflection").toObject())) {
                    _deserializationError = _ambientReflection.deserializationError();
                    return false;
                }

                if(!_diffuseReflection.deserialize(jsonObject.value("diffuseReflection").toObject())) {
                    _deserializationError = _diffuseReflection.deserializationError();
                    return false;
                }

                if(!_specularReflection.deserialize(jsonObject.value("specularReflection").toObject())) {
                    _deserializationError = _specularReflection.deserializationError();
                    return false;
                }

                _shininess = (float)jsonObject["shininess"].toDouble();

                if(!_emission.deserialize(jsonObject.value("emission").toObject())) {
                    _deserializationError = _emission.deserializationError();
                    return false;
                }

                _textureId = jsonObject["textureId"].toString();

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
