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

#ifndef G3D_MATERIAL_H
#define G3D_MATERIAL_H

// Own includes
#include "g3d_rgbacolor.h"

// Qt includes
#include <QImage>
#include <QGLWidget>

namespace Glee3D {
class Display;

/**
  * @class Material
  * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
  * @date 02.12.2012
  * Defines a material.
  */
class Material {
public:
    /** Creates a new material. */
    Material();

    /** Activates this material. */
    void activate();

    /** @returns Color of the ambient reflection. */
    RgbaColor ambientReflection();

    /** @returns Color of the diffuse reflection. */
    RgbaColor diffuseReflection();

    /** @returns Color of the specular reflection. */
    RgbaColor specularReflection();

    /** @returns Shininess of this material. */
    float shininess();

    /** @returns Color of the emission of this material. */
    RgbaColor emission();

    /**
      * Sets the ambient reflection color for this material.
      * @param ambientReflection Ambient reflection color.
      */
    void setAmbientReflection(RgbaColor ambientReflection);

    /**
      * Sets the diffuse reflection color for this material.
      * @param diffuseReflection Diffuse reflection color.
      */
    void setDiffuseReflection(RgbaColor diffuseReflection);

    /**
      * Sets the specular reflection color for this material.
      * @param specularReflection Specular reflection color.
      */
    void setSpecularReflection(RgbaColor specularReflection);

    /**
      * Sets the shininess for this material.
      * @param shininess Intensity of shininess.
      */
    void setShininess(float shininess);

    /**
      * Sets the emission color for this material.
      * @param emission Emission color.
      */
    void setEmission(RgbaColor emission);

    /**
      * Loads a texture for this material.
      * @param fileName File name of the texture.
      * @param display Current display.
      */
    void loadTexture(QString fileName, Display& display);

protected:
    RgbaColor _ambientReflection;
    RgbaColor _diffuseReflection;
    RgbaColor _specularReflection;
    float _shininess;
    RgbaColor _emission;

    bool _hasTexture;
    QImage _texture;
    GLuint _glTexture;
};

class ChromeMaterial : public Material {
public:
    ChromeMaterial()
        : Material() {
        _ambientReflection = RgbaColor(0.25, 0.25, 0.25, 1.0);
        _diffuseReflection = RgbaColor(0.40, 0.40, 0.40, 1.0);
        _specularReflection = RgbaColor(0.77, 0.77, 0.77, 1.0);
        _shininess = 76.8;
    }
};

class GoldMaterial : public Material {
public:
    GoldMaterial()
        : Material() {
        _ambientReflection = RgbaColor(0.25, 0.20, 0.07, 1.0);
        _diffuseReflection = RgbaColor(0.75, 0.61, 0.23, 1.0);
        _specularReflection = RgbaColor(0.63, 0.65, 0.37, 1.0);
        _shininess = 51.2;
    }
};

class GoldPolishedMaterial : public Material {
public:
    GoldPolishedMaterial()
        : Material() {
        _ambientReflection = RgbaColor(0.25, 0.22, 0.06, 1.0);
        _diffuseReflection = RgbaColor(0.35, 0.31, 0.09, 1.0);
        _specularReflection = RgbaColor(0.80, 0.72, 0.21, 1.0);
        _shininess = 83.2;
    }
};

class CopperMaterial : public Material {
public:
    CopperMaterial()
        : Material() {
        _ambientReflection = RgbaColor(0.19, 0.07, 0.02, 1.0);
        _diffuseReflection = RgbaColor(0.70, 0.27, 0.08, 1.0);
        _specularReflection = RgbaColor(0.26, 0.14, 0.09, 1.0);
        _shininess = 12.8;
    }
};

class PearlMaterial : public Material {
public:
    PearlMaterial()
        : Material() {
        _ambientReflection = RgbaColor(0.25, 0.21, 0.21, 0.9);
        _diffuseReflection = RgbaColor(0.99, 0.83, 0.83, 0.9);
        _specularReflection = RgbaColor(0.30, 0.30, 0.30, 0.9);
        _shininess = 11.3;
    }
};

} // namespace Glee3D

#endif // G3D_MATERIAL_H
