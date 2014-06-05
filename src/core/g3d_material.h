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
#include "io/g3d_serializable.h"

// Qt includes
#include <QString>

namespace Glee3D {
    /**
      * @class Material
      * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
      * @date 02.12.2012
      * Defines a material.
      */
    class Material : public Serializable {
    public:
        enum StandardMaterial{
            BlackRubber,
            BlackPlastic,
            Bronze,
            BronzePolished,
            Chrome,
            Copper,
            CopperPolished,
            Gold,
            GoldPolished,
            Pearl,
            Ruby,
            Silver,
            SilverPolished
        };

        static Material* standardMaterial(StandardMaterial standardMaterial);

        /** Creates a new material. */
        Material();

        Material(QString textureId,
            RgbaColor ambientReflection,
            RgbaColor diffuseReflection,
            RgbaColor specularReflection,
            float shininess,
            RgbaColor emission);

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

        /** The texture ID for this material. */
        QString textureId();

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
         * Sets the texture id for this material.
         * @param textureId
         */
        void setTextureId(QString textureId);

        /** @overload */
        QString className();

        /** @overload */
        QJsonObject serialize();

        /** @overload */
        bool deserialize(QJsonObject jsonObject);

    protected:
        RgbaColor _ambientReflection;
        RgbaColor _diffuseReflection;
        RgbaColor _specularReflection;
        float _shininess;
        RgbaColor _emission;
        QString _textureId;
    };

} // namespace Glee3D

#endif // G3D_MATERIAL_H
