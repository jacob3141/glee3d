///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of glee3d.                                           //
//    Copyright (C) 2012-2014 Jacob Dawid, jacob.dawid@cybercatalyst.net     //
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

#ifndef G3D_TERRAIN_H
#define G3D_TERRAIN_H

// Own includes
#include "g3d_entity.h"

// Qt includes
#include <QString>
#include <QHash>
#include <QPair>

namespace Glee3D {
    /**
      * @class Terrain
      * @author Jacob Dawid (jacob.dawid@cybercatalyst.net)
      * @date 18.08.2013
      */
    class Terrain :
        public Anchored,
        public Renderable,
        public Texturizable,
        public Serializable {
    public:
        enum Encoding {
            RedComponent,
            GreenComponent,
            BlueComponent
        };

        enum Result {
            Ok,
            FileLoadError,
            InvalidImageSize
        };

        explicit Terrain();
        virtual ~Terrain();

        Result generate(QString fileName,
                        Encoding heightEncoding = RedComponent,
                        Encoding textureEncoding = GreenComponent);
        Result generate(QImage image,
                        Encoding heightEncoding = RedComponent,
                        Encoding textureEncoding = GreenComponent);

        void setTilingOffset(float tilingOffset);
        void setScale(float scale);

        float scale();
        int width();
        int height();

        void render(RenderMode renderMode = Textured);

        QString className();
        QJsonObject serialize();
        bool deserialize(QJsonObject json);

    protected:

    private:
        void allocateMemory();
        void freeMemory();

        float _scale;
        QHash<QPair<int, int>, float> _terrain;
        QHash<QPair<int, int>, int> _tileIDs;
        QHash<QPair<int, int>, RealVector3D> _normals;
        float _tilingOffset;
        int _width;
        int _height;

        GLfloat *_vertexBuffer;
        GLfloat *_textureCoordinatesBuffer;
        GLfloat *_normalsBuffer;
    };
} // namespace Glee3D

#endif // G3D_TERRAIN_H
