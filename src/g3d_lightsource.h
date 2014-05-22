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

#ifndef G3D_LIGHTSOURCE_H
#define G3D_LIGHTSOURCE_H

// Own includes
#include "g3d_entity.h"
#include "g3d_rgbacolor.h"

// Qt includes
#include <QGLWidget>

namespace Glee3D {
/**
  * @class LightSource
  * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
  * @date 02.12.2012
  * Represents a light source in the virtual environment.
  */
class LightSource : public Entity {
public:
    enum LightSourceType {
        Punctual,
        Spotlight
    };

    /**
      * Creates a new light source.
      */
    LightSource(Entity *parent = 0);

    /**
      * Sets this light to be switched on.
      */
    void setSwitchedOn(bool on = true);

    /**
      * @returns true, when this light is switched on.
      */
    bool switchedOn() const;

    /**
      * Switches this light on if it has been off and vice versa.
      */
    void switchOnOff();

    /**
      * Activates the light as the given GL light.
      * @param glLight Open GL light index.
      */
    void activate(int glLight);

    /**
      * Sets the type of light source.
      * @param lightSourceType The type of light source.
      * @see LightSourceType
      */
    void setLightSourceType(LightSourceType lightSourceType);

    /**
      * Sets the ambient light color.
      * @param ambientLight Color of the ambient light.
      */
    void setAmbientLight(RgbaColor ambientLight);

    /**
      * Sets the diffuse light color.
      * @param diffuseLight Color of the diffuse light.
      */
    void setDiffuseLight(RgbaColor diffuseLight);

    /**
      * Sets the specular light color.
      * @param specularLight Color of the specular light.
      */
    void setSpecularLight(RgbaColor specularLight);

    /**
      * Sets the spot direction.
      * @param spotDirection The direction of the spot.
      * @note This will only affect spotlights.
      * @see LightSourceType
      */
    void setSpotDirecton(RealVector3D spotDirection);

    /**
      * Sets the spots cutoff.
      * @param spotCutoff The cutoff of the spot.
      * @note This will only affect spotlights.
      * @see LightSourceType
      */
    void setSpotCutoff(double spotCutoff);

    /**
      * Sets the spots exponent.
      * @param spotExponent The exponent of the spot.
      * @note This will only affect spotlights.
      * @see LightSourceType
      */
    void setSpotExponent(double spotExponent);

    /** @returns The spots direction. */
    RealVector3D spotDirection();

    /** @returns The spots cutoff. */
    double spotCutoff();

    /** @returns The spots exponent. */
    double spotExponent();

    /** @returns light source type. */
    LightSourceType lightSourceType();

    /** @returns Color of the ambient light. */
    RgbaColor ambientLight();

    /** @returns Color of the diffuse light. */
    RgbaColor diffuseLight();

    /** @returns Color of the specular light. */
    RgbaColor specularLight();

private:
    bool _switchedOn;

    RgbaColor _ambientLight;
    RgbaColor _diffuseLight;
    RgbaColor _specularLight;

    RealVector3D _spotDirection;
    double _spotCutoff;
    double _spotExponent;

    LightSourceType _lightSourceType;
};

} // namespace Glee3D

#endif // G3D_LIGHTSOURCE_H
