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
    effects/g3d_postrendereffect.h \
    core/g3d_anchored.h \
    core/g3d_camera.h \
    core/g3d_framebuffer.h \
    core/g3d_lightsource.h \
    core/g3d_display.h \
    core/g3d_material.h \
    core/g3d_mesh.h \
    core/g3d_oriented.h \
    core/g3d_program.h \
    core/g3d_renderable.h \
    core/g3d_rgbacolor.h \
    core/g3d_scene.h \
    core/g3d_skybox.h \
    core/g3d_terrain.h \
    core/g3d_texturestore.h \
    core/g3d_texturizable.h \
    objects/g3d_cube.h \
    objects/g3d_cylinder.h \
    io/g3d_serializable.h \
    io/g3d_objloader.h \
    core/g3d_entity.h \
    math/g3d_vector2d.h \
    math/g3d_vector3d.h \
    math/g3d_vector4d.h \
    math/g3d_plane3d.h \
    math/g3d_line3d.h \
    core/g3d_compiledmesh.h \
    core/g3d_log.h \
    core/g3d_logging.h \
    core/g3d_utilities.h \
    math/g3d_matrix4x4.h

SOURCES += \
    core/g3d_anchored.cpp \
    core/g3d_camera.cpp \
    core/g3d_display.cpp \
    core/g3d_framebuffer.cpp \
    core/g3d_lightsource.cpp \
    core/g3d_material.cpp \
    core/g3d_mesh.cpp \
    core/g3d_oriented.cpp \
    core/g3d_program.cpp \
    core/g3d_scene.cpp \
    core/g3d_skybox.cpp \
    core/g3d_terrain.cpp \
    core/g3d_texturestore.cpp \
    objects/g3d_cube.cpp \
    objects/g3d_cylinder.cpp \
    io/g3d_objloader.cpp \
    core/g3d_entity.cpp \
    core/g3d_compiledmesh.cpp \
    core/g3d_log.cpp \
    core/g3d_utilities.cpp \
    math/g3d_matrix4x4.cpp \
    math/g3d_line3d.cpp \
    math/g3d_plane3d.cpp \
    math/g3d_vector2d.cpp \
    math/g3d_vector3d.cpp \
    math/g3d_vector4d.cpp

RESOURCES += \
    g3d.qrc
