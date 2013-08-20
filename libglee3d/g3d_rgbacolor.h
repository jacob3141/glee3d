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

#ifndef G3D_RGBACOLOR_H
#define G3D_RGBACOLOR_H

namespace Glee3D {
/**
  * @struct RgbaColor
  * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
  * @date 02.12.2012
  * Defines a color after the rgba color model.
  */
struct RgbaColor {
    /** Initialization of color struct. */
    RgbaColor() {
        _red = 0.0;
        _green = 0.0;
        _blue = 0.0;
        _alpha = 1.0;
    }

    /** Initialization of color struct. */
    RgbaColor(float red, float green, float blue, float alpha) {
        _red = red;
        _green = green;
        _blue = blue;
        _alpha = alpha;
    }

    float _red;
    float _green;
    float _blue;
    float _alpha;
};

} // namespace Glee3D

#endif // G3D_RGBACOLOR_H
