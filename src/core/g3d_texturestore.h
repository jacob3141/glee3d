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

#ifndef G3D_TEXTURESTORE_H
#define G3D_TEXTURESTORE_H

// Own includes
#include "g3d_display.h"

// Qt includes
#include <QString>
#include <QImage>
#include <QMap>

namespace Glee3D {

class TextureStore {
public:
    struct LoadedTexture {
        QImage _image;
        int _glHandle;
    };

    static TextureStore& instance() {
        static TextureStore textureStore;
        return textureStore;
    }

    /**
      * Loads a texture.
      * @param fileName File name of the texture.
      * @param display Current display.
      */
    bool loadTexture(Display& display, QString fileName, QString textureId);

    /**
     * Activates the specified texture for rendering.
     * @brief activateTexture
     * @param textureId
     */
    void activateTexture(QString textureId);

private:
    TextureStore();

    QMap<QString, LoadedTexture> _loadedTextures;
};

} // namespace Glee3D

#endif // G3D_TEXTURESTORE_H
