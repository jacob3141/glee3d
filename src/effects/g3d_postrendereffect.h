///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of glee3d.                                           //
//    Copyright (C) 2012-2014 Jacob Dawid, jacob.dawid@omg-it.works          //
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

#ifndef G3D_POSTRENDEREFFECT_H
#define G3D_POSTRENDEREFFECT_H

// Own includes
#include "core/g3d_framebuffer.h"

// Qt includes
#include <QImage>
#include <QGLWidget>

namespace Glee3D {

/**
  * @class
  * @author Jacob Dawid (jacob.dawid@omg-it.works)
  * @date 02.12.2012
  */
class PostRenderEffect {
public:
    PostRenderEffect() { }
    virtual ~PostRenderEffect() { }

    /**
      * @note Post-render effects need framebuffer objects, which can only be
      * created when a valid rendering context is available. That's why we
      * cannot initialize the effect in the constructor, but we have to rely
      * on the framework that it calls the initialize method whenever it's
      * appropriate.
      */
    virtual void initialize() = 0;

    /** Applies the effect to the framebuffer. */
    virtual void apply(FrameBuffer *frameBuffer) = 0;
};

} // namespace Glee3D
#endif // G3D_POSTRENDEREFFECT_H
