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

// Own includes
#include "g3d_objloader.h"

// Qt includes
#include <QFile>

namespace Glee3D {

ObjLoader::ObjLoader() {
}

QList<Mesh*> ObjLoader::readObjFile(QString fileName) {
    QList<Mesh*> meshes;
    QString fileContents;

    QFile file(fileName);
    file.open(QFile::ReadOnly);
    if(file.isOpen()) {
        fileContents = QString(file.readAll());
        file.close();
    } else {
        return QList<Mesh*>();
    }

    QList<RealVector3D> vertices;
    QList<Triangle> triangles;

    // Remove all comments from the file.
    fileContents.replace(QRegExp("#.*$"), "");

    // Split file into lines (split at line endings).
    QStringList lines = fileContents.split(QRegExp("$"), QString::SkipEmptyParts);

    // Process every line.
    foreach(QString line, lines) {

        // Split line at whitespaces.
        QStringList command = line.split(QRegExp("\\s"), QString::SkipEmptyParts);

        // If there is anything to interpret, do that.
        if(command.size() > 0) {
            // "object"-command, creates a new object.
            if(command[0] == "o") {
                if(!vertices.isEmpty()  && !triangles.isEmpty()) {
                    Mesh *mesh = new Mesh(vertices.count(), triangles.count());
                    for(int i = 0; i < vertices.count(); i++) {
                        mesh->setVertex(i, vertices[i]);
                    }
                    for(int i = 0; i < triangles.count(); i++) {
                        mesh->setTriangle(i, triangles[i]);
                    }
                    meshes.append(mesh);
                    vertices.clear();
                    triangles.clear();
                }

            // "vertex"-command, defines a new vertex.
            } else if(command[0] == "v") {
                if(command.size() > 3) {

                }
            }
        }
    }

    return meshes;
}

} // namespace Glee3D
