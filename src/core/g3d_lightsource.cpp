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
#include "g3d_lightsource.h"

namespace Glee3D {
    LightSource::LightSource()
        : Anchored(),
          Logging("LightSource") {
        _lightSourceType = Punctual;
        _switchedOn = true;
    }

    void LightSource::setSwitchedOn(bool on) {
        _switchedOn = on;
    }

    bool LightSource::switchedOn() const {
        return _switchedOn;
    }

    void LightSource::switchOnOff() {
        _switchedOn = !_switchedOn;
    }

    void LightSource::activate(int glLight) {
        glDisable(glLight);
        GLfloat ambientLight[] = { _ambientLight._red,
                                   _ambientLight._green,
                                   _ambientLight._blue,
                                   _ambientLight._alpha };
        glLightfv(glLight, GL_AMBIENT, ambientLight);

        GLfloat diffuseLight[] = { _diffuseLight._red,
                                   _diffuseLight._green,
                                   _diffuseLight._blue,
                                   _diffuseLight._alpha };
        glLightfv(glLight, GL_DIFFUSE, diffuseLight);

        GLfloat specularLight[] = { _specularLight._red,
                                    _specularLight._green,
                                    _specularLight._blue,
                                    _specularLight._alpha };
        glLightfv(glLight, GL_SPECULAR, specularLight);

        GLfloat position[] = { (GLfloat)_position._x,
                               (GLfloat)_position._y,
                               (GLfloat)_position._z,
                               1.0f };
        glLightfv(glLight, GL_POSITION, position);

        switch(_lightSourceType) {
            case Punctual: {
            } break;

            case Spotlight: {
                GLfloat spotDirection[] = { (GLfloat)_spotDirection._x,
                                            (GLfloat)_spotDirection._y,
                                            (GLfloat)_spotDirection._z,
                                            0.0f };
                glLightfv(glLight, GL_SPOT_DIRECTION, spotDirection);
                glLightf(glLight, GL_SPOT_CUTOFF, _spotCutoff);
                glLightf(glLight, GL_SPOT_EXPONENT, _spotExponent);
            } break;
        }

        glEnable(glLight);
    }

    void LightSource::setLightSourceType(LightSourceType lightSourceType) {
        _lightSourceType = lightSourceType;
    }

    void LightSource::setAmbientLight(RgbaColor ambientLight) {
        _ambientLight = ambientLight;
    }

    void LightSource::setDiffuseLight(RgbaColor diffuseLight) {
        _diffuseLight = diffuseLight;
    }

    void LightSource::setSpecularLight(RgbaColor specularLight) {
        _specularLight = specularLight;
    }

    void LightSource::setSpotDirecton(RealVector3D spotDirection) {
        _spotDirection = spotDirection;
    }

    void LightSource::setSpotCutoff(double spotCutoff) {
        _spotCutoff = spotCutoff;
    }

    void LightSource::setSpotExponent(double spotExponent) {
        _spotExponent = spotExponent;
    }

    RealVector3D LightSource::spotDirection() {
        return _spotDirection;
    }

    double LightSource::spotCutoff() {
        return _spotCutoff;
    }

    double LightSource::spotExponent() {
        return _spotExponent;
    }

    LightSource::LightSourceType LightSource::lightSourceType() {
        return _lightSourceType;
    }

    RgbaColor LightSource::ambientLight() {
        return _ambientLight;
    }

    RgbaColor LightSource::diffuseLight() {
        return _diffuseLight;
    }

    RgbaColor LightSource::specularLight() {
        return _specularLight;
    }

    QString LightSource::className() {
        return "LightSource";
    }

    QJsonObject LightSource::serialize() {
        QJsonObject jsonObject;
        jsonObject["class"] = className();

        jsonObject["switchedOn"] = _switchedOn;
        jsonObject["ambientLight"] = _ambientLight.serialize();
        jsonObject["diffuseLight"] = _diffuseLight.serialize();
        jsonObject["specularLight"] = _specularLight.serialize();
        jsonObject["spotDirection"] = _spotDirection.serialize();
        jsonObject["spotCutoff"] = _spotCutoff;
        jsonObject["spotExponent"] = _spotExponent;

        switch(_lightSourceType) {
        case Spotlight: jsonObject["lightSourceType"] = QString("Spotlight"); break;
        case Punctual: jsonObject["lightSourceType"] = QString("Punctual"); break;
        }

        return jsonObject;
    }

    bool LightSource::deserialize(QJsonObject jsonObject) {
        if(!jsonObject.contains("class")) {
            _deserializationError = Serializable::NoClassSpecified;
            return false;
        }

        if(jsonObject.contains("switchedOn")
        && jsonObject.contains("ambientLight")
        && jsonObject.contains("diffuseLight")
        && jsonObject.contains("specularLight")
        && jsonObject.contains("spotDirection")
        && jsonObject.contains("spotCutoff")
        && jsonObject.contains("spotExponent")
        && jsonObject.contains("lightSourceType")) {
            if(jsonObject["class"] == className()) {
                _switchedOn = jsonObject["switchedOn"].toBool();

                if(!_ambientLight.deserialize(jsonObject.value("ambientLight").toObject())) {
                    _deserializationError = _ambientLight.deserializationError();
                    return false;
                }

                if(!_diffuseLight.deserialize(jsonObject.value("diffuseLight").toObject())) {
                    _deserializationError = _diffuseLight.deserializationError();
                    return false;
                }

                if(!_specularLight.deserialize(jsonObject.value("specularLight").toObject())) {
                    _deserializationError = _specularLight.deserializationError();
                    return false;
                }

                if(!_spotDirection.deserialize(jsonObject.value("spotDirection").toObject())) {
                    _deserializationError = _spotDirection.deserializationError();
                    return false;
                }

                _spotCutoff = jsonObject["spotCutoff"].toDouble();
                _spotExponent = jsonObject["spotExponent"].toDouble();

                QString lightSourceType = jsonObject["lightSourceType"].toString();
                if(lightSourceType == "Punctual") {
                    _lightSourceType = Punctual;
                } else if (lightSourceType == "Spotlight") {
                    _lightSourceType = Spotlight;
                }

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
