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
    DESTDIR =       bin/release
    OBJECTS_DIR =   bin/release/obj
    MOC_DIR =       bin/release/moc
    RCC_DIR =       bin/release/rcc
    UI_DIR =        bin/release/ui
    INCLUDEPATH += .
}

CONFIG(debug, debug|release) {
    DESTDIR =       bin/debug
    OBJECTS_DIR =   bin/debug/obj
    MOC_DIR =       bin/debug/moc
    RCC_DIR =       bin/debug/rcc
    UI_DIR =        bin/debug/ui
    INCLUDEPATH += .
    DEFINES += DEBUG
}

HEADERS += \
    camera.h \
    configuration.h \
    cube.h \
    display.h \
    entity.h \
    lightsource.h \
    object.h \
    rgbacolor.h \
    scene.h \
    vector3d.h \
    vector4d.h \
    vector2d.h \
    cylinder.h \
    skybox.h \
    particle.h \
    program.h \
    effect.h \
    bloomeffect.h \
    framebuffer.h \
    matrixstate.h \
    material.h \
    mesh.h \
    objloader.h

SOURCES += \
    camera.cpp \
    cube.cpp \
    display.cpp \
    entity.cpp \
    lightsource.cpp \
    object.cpp \
    scene.cpp \
    cylinder.cpp \
    skybox.cpp \
    particle.cpp \
    program.cpp \
    bloomeffect.cpp \
    framebuffer.cpp \
    matrixstate.cpp \
    material.cpp \
    mesh.cpp \
    objloader.cpp

RESOURCES +=
