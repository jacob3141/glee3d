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

TEMPLATE = app
TARGET = world-editor
CONFIG += debug_and_release

QT += opengl

CONFIG(release, debug|release) {
    DESTDIR =       bin/release
    OBJECTS_DIR =   bin/release/obj
    MOC_DIR =       bin/release/moc
    RCC_DIR =       bin/release/rcc
    UI_DIR =        bin/release/ui
    INCLUDEPATH += . ../../src
    LIBS += -L../../bin/release -lglee3d
}

CONFIG(debug, debug|release) {
    DESTDIR =       bin/debug
    OBJECTS_DIR =   bin/debug/obj
    MOC_DIR =       bin/debug/moc
    RCC_DIR =       bin/debug/rcc
    UI_DIR =        bin/debug/ui
    INCLUDEPATH += . ../../src
    LIBS += -L../../bin/debug -lglee3d
    DEFINES += DEBUG
}

unix {
    LIBS += -lglut -lGLU -lGLEW
}

win32 {
    LIBS += -lglu32 -lopengl32 -lGLEW
}

HEADERS += \
    scene.h \
    worldeditor.h

SOURCES += \
    main.cpp \
    scene.cpp \
    worldeditor.cpp

FORMS += \
    worldeditor.ui
