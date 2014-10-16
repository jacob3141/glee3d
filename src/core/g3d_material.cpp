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
#include "g3d_material.h"
#include "g3d_texturestore.h"

// Qt includes
#include <QGLWidget>

namespace Glee3D {
    Material* Material::standardMaterial(StandardMaterial standardMaterial) {
        switch(standardMaterial) {

        case BlackRubber:
            return new Material("",
                RgbaColor(0.02, 0.02, 0.02, 1.0),  // Ambient
                RgbaColor(0.01, 0.01, 0.01, 1.0),  // Diffuse
                RgbaColor(0.40, 0.40, 0.40, 1.0),  // Specular
                10.0,                              // Shininess
                RgbaColor(0.00, 0.00, 0.00, 0.0)); // Emission
        case BlackPlastic:
            return new Material("",
                RgbaColor(0.00, 0.00, 0.00, 1.0),  // Ambient
                RgbaColor(0.01, 0.01, 0.01, 1.0),  // Diffuse
                RgbaColor(0.50, 0.50, 0.50, 1.0),  // Specular
                32.0,                              // Shininess
                RgbaColor(0.00, 0.00, 0.00, 0.0)); // Emission
        case Bronze:
            return new Material("",
                RgbaColor(0.21, 0.13, 0.05, 1.0),  // Ambient
                RgbaColor(0.71, 0.43, 0.18, 1.0),  // Diffuse
                RgbaColor(0.39, 0.27, 0.17, 1.0),  // Specular
                25.6,                              // Shininess
                RgbaColor(0.00, 0.00, 0.00, 0.0)); // Emission
        case BronzePolished:
            return new Material("",
                RgbaColor(0.25, 0.15, 0.06, 1.0),  // Ambient
                RgbaColor(0.40, 0.24, 0.10, 1.0),  // Diffuse
                RgbaColor(0.77, 0.46, 0.20, 1.0),  // Specular
                76.8,                              // Shininess
                RgbaColor(0.00, 0.00, 0.00, 0.0)); // Emission
        case Chrome:
            return new Material("",
                RgbaColor(0.25, 0.25, 0.25, 1.0),  // Ambient
                RgbaColor(0.40, 0.40, 0.40, 1.0),  // Diffuse
                RgbaColor(0.77, 0.77, 0.77, 1.0),  // Specular
                76.8,                              // Shininess
                RgbaColor(0.00, 0.00, 0.00, 0.0)); // Emission
        case Copper:
            return new Material("",
                RgbaColor(0.19, 0.07, 0.02, 1.0),  // Ambient
                RgbaColor(0.70, 0.27, 0.08, 1.0),  // Diffuse
                RgbaColor(0.26, 0.14, 0.09, 1.0),  // Specular
                12.8,                              // Shininess
                RgbaColor(0.00, 0.00, 0.00, 0.0)); // Emission
        case CopperPolished:
            return new Material("",
                RgbaColor(0.23, 0.09, 0.03, 1.0),  // Ambient
                RgbaColor(0.55, 0.21, 0.07, 1.0),  // Diffuse
                RgbaColor(0.58, 0.22, 0.07, 1.0),  // Specular
                51.2,                              // Shininess
                RgbaColor(0.00, 0.00, 0.00, 0.0)); // Emission
        case Gold:
            return new Material("",
                RgbaColor(0.25, 0.20, 0.07, 1.0),  // Ambient
                RgbaColor(0.75, 0.61, 0.23, 1.0),  // Diffuse
                RgbaColor(0.63, 0.65, 0.37, 1.0),  // Specular
                51.2,                              // Shininess
                RgbaColor(0.00, 0.00, 0.00, 0.0)); // Emission
        case GoldPolished:
            return new Material("",
                RgbaColor(0.25, 0.22, 0.06, 1.0),  // Ambient
                RgbaColor(0.35, 0.31, 0.09, 1.0),  // Diffuse
                RgbaColor(0.80, 0.72, 0.21, 1.0),  // Specular
                83.2,                              // Shininess
                RgbaColor(0.00, 0.00, 0.00, 0.0)); // Emission
        case Pearl:
            return new Material("",
                RgbaColor(0.25, 0.21, 0.21, 0.9),  // Ambient
                RgbaColor(0.99, 0.83, 0.83, 0.9),  // Diffuse
                RgbaColor(0.30, 0.30, 0.30, 0.9),  // Specular
                11.3,                              // Shininess
                RgbaColor(0.00, 0.00, 0.00, 0.0)); // Emission
        case Ruby:
            return new Material("",
                RgbaColor(0.17, 0.01, 0.01, 0.5),  // Ambient
                RgbaColor(0.61, 0.04, 0.04, 0.5),  // Diffuse
                RgbaColor(0.73, 0.63, 0.63, 0.5),  // Specular
                76.8,                              // Shininess
                RgbaColor(0.00, 0.00, 0.00, 0.0)); // Emission
        case Silver:
            return new Material("",
                RgbaColor(0.19, 0.19, 0.19, 1.0),  // Ambient
                RgbaColor(0.51, 0.51, 0.51, 1.0),  // Diffuse
                RgbaColor(0.51, 0.51, 0.51, 1.0),  // Specular
                51.2,                              // Shininess
                RgbaColor(0.00, 0.00, 0.00, 0.0)); // Emission
        case SilverPolished:
            return new Material("",
                RgbaColor(0.23, 0.23, 0.23, 1.0),  // Ambient
                RgbaColor(0.28, 0.28, 0.28, 1.0),  // Diffuse
                RgbaColor(0.77, 0.77, 0.77, 1.0),  // Specular
                89.6,                              // Shininess
                RgbaColor(0.00, 0.00, 0.00, 0.0)); // Emission
        };

        // This should never happen.
        Q_ASSERT(false);
        return 0;
    }

    Material::Material()
        : Serializable(),
          Logging("Material") {
        _textureId          = "";
        _ambientReflection  = RgbaColor();
        _diffuseReflection  = RgbaColor();
        _specularReflection = RgbaColor();
        _shininess          = 0.4;
        _emission           = RgbaColor();
    }

    Material::Material(QString textureId,
        RgbaColor ambientReflection,
        RgbaColor diffuseReflection,
        RgbaColor specularReflection,
        float shininess,
        RgbaColor emission)
        : Serializable(),
          Logging("Material") {
        _textureId = textureId;
        _ambientReflection = ambientReflection;
        _diffuseReflection = diffuseReflection;
        _specularReflection = specularReflection;
        _shininess = shininess;
        _emission = emission;
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
