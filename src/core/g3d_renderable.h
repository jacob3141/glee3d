///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of glee3d.                                           //
//    Copyright (C) 2014 Jacob Dawid, jacob.dawid@omg-it.works          //
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

#ifndef G3D_RENDERABLE_H
#define G3D_RENDERABLE_H

/**
 *
 */
namespace Glee3D {

     /**
     * @brief The Renderable class
     */
    class Renderable {
    public:
        enum RenderMode {
            MeshOnly,
            Solid,
            Textured
        };

        Renderable() {
            _visible = true;
        }

        virtual ~Renderable() { }

        /** Sets whether this object shall be visible or not.
          * @param on true, if this object shall be visible.
          */
        void setVisible(bool on = true) {
            _visible = on;
        }

        /** @returns true, when this object is set to be visible. */
        bool visible() {
            return _visible;
        }

        virtual void render(RenderMode renderMode = Renderable::Textured) = 0;

    protected:
        bool _visible;
    };

} // namespace Glee3D

#endif // G3D_RENDERABLE_H
