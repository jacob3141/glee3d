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
#include "material.h"

#include <iostream>

#include <QGLWidget>

namespace Glee3D {
    Material::Material() {
        _glTexture          = 0;
        _hasTexture         = false;
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

        if(_hasTexture) {
            glBindTexture(GL_TEXTURE_2D, _glTexture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        } else {
            glBindTexture(GL_TEXTURE_2D, GL_NONE);
        }
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

    void Material::loadTexture(QString fileName, Display& display) {
        _hasTexture = true;
        display.makeCurrent();
        if(!_texture.load(fileName)) {
            std::cout << "Error loading texture: " << fileName.toStdString() << std::endl;
        }
        _glTexture = display.bindTexture(_texture);
    }
}
