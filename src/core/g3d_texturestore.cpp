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

// Own includes
#include "g3d_texturestore.h"

namespace Glee3D {

    TextureStore::TextureStore() {
    }

    bool TextureStore::loadTexture(Display& display, QString fileName, QString textureId) {
        LoadedTexture loadedTexture;
        display.makeCurrent();
        if(loadedTexture._image.load(fileName)) {
            loadedTexture._glHandle = display.bindTexture(loadedTexture._image);
            _loadedTextures[textureId] = loadedTexture;
            return true;
        } else {
            return false;
        }
    }

    void TextureStore::activateTexture(QString textureId) {
        if(!textureId.isEmpty()
        && _loadedTextures.contains(textureId)) {
            glBindTexture(GL_TEXTURE_2D, _loadedTextures[textureId]._glHandle);
            glEnable(GL_TEXTURE_2D);
        } else {
            glBindTexture(GL_TEXTURE_2D, GL_NONE);
            glDisable(GL_TEXTURE_2D);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }
} // namespace Glee3D
