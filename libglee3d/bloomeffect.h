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

#ifndef BLOOMEFFECT_H
#define BLOOMEFFECT_H

// Own includes
#include "program.h"
#include "effect.h"

typedef enum {HORIZONTAL, VERTICAL} Direction;

namespace Glee3D {

/**
  * @class BloomEffect
  * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
  * @date 02.12.2012
  * Implements a post render bloom effect.
  */
class BloomEffect : public Effect {
public:
    BloomEffect();
    ~BloomEffect();

    void blur(FrameBuffer **from, FrameBuffer **to, Direction dir);
    void initialize();
    void apply(FrameBuffer *frameBuffer);

private:
    Program _blitProgram;
    Program _combineProgram;
    Program _filterProgram;
    int _filterDepth;
    int _kernelSize;
    float *_filterKernel;
    FrameBuffer **_passA;
    FrameBuffer **_passB;
};

}

#endif // BLOOMEFFECT_H
