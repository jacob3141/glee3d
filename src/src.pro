#    This file is part of glee3d.
#
#    glee3d is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    glee3d is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with glee3d.  If not, see <http://www.gnu.org/licenses/>.

TEMPLATE = lib
TARGET = glee3d
CONFIG += debug_and_release staticlib

QT += opengl

DEFINES += GL_GLEXT_PROTOTYPES

CONFIG(release, debug|release) {
    DESTDIR =       ../bin/release
    OBJECTS_DIR =   ../bin/release/obj
    MOC_DIR =       ../bin/release/moc
    RCC_DIR =       ../bin/release/rcc
    UI_DIR =        ../bin/release/ui
    INCLUDEPATH += .
}

CONFIG(debug, debug|release) {
    DESTDIR =       ../bin/debug
    OBJECTS_DIR =   ../bin/debug/obj
    MOC_DIR =       ../bin/debug/moc
    RCC_DIR =       ../bin/debug/rcc
    UI_DIR =        ../bin/debug/ui
    INCLUDEPATH += .
    DEFINES += DEBUG
}

HEADERS += \
    g3d_bloomeffect.h \
    g3d_camera.h \
    g3d_configuration.h \
    g3d_cube.h \
    g3d_cylinder.h \
    g3d_display.h \
    g3d_effect.h \
    g3d_entity.h \
    g3d_framebuffer.h \
    g3d_lightsource.h \
    g3d_material.h \
    g3d_matrixstate.h \
    g3d_mesh.h \
    g3d_object.h \
    g3d_objloader.h \
    g3d_program.h \
    g3d_rgbacolor.h \
    g3d_scene.h \
    g3d_skybox.h \
    g3d_terrain.h \
    g3d_vector2d.h \
    g3d_vector3d.h \
    g3d_vector4d.h \
    g3d_serializable.h \
    g3d_texturestore.h

SOURCES += \
    g3d_bloomeffect.cpp \
    g3d_camera.cpp \
    g3d_cube.cpp \
    g3d_cylinder.cpp \
    g3d_display.cpp \
    g3d_entity.cpp \
    g3d_framebuffer.cpp \
    g3d_lightsource.cpp \
    g3d_material.cpp \
    g3d_matrixstate.cpp \
    g3d_mesh.cpp \
    g3d_object.cpp \
    g3d_objloader.cpp \
    g3d_program.cpp \
    g3d_scene.cpp \
    g3d_skybox.cpp \
    g3d_terrain.cpp \
    g3d_texturestore.cpp

