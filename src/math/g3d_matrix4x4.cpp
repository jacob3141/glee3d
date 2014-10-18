///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of glee3d.                                           //
//    Copyright (C) 2012-2015 Jacob Dawid, jacob.dawid@omg-it.works          //
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
#include "g3d_matrix4x4.h"

namespace Glee3D {

Matrix4x4::Matrix4x4() :
    Logging("Matrix4x4") {
    // First column
    _data[0]  = 1.0;
    _data[1]  = 0.0;
    _data[2]  = 0.0;
    _data[3]  = 0.0;

    // Second column
    _data[4]  = 0.0;
    _data[5]  = 1.0;
    _data[6]  = 0.0;
    _data[7]  = 0.0;

    // Third column
    _data[8]  = 0.0;
    _data[9]  = 0.0;
    _data[10] = 1.0;
    _data[11] = 0.0;

    // Fourth column
    _data[12] = 0.0;
    _data[13] = 0.0;
    _data[14] = 0.0;
    _data[15] = 1.0;
}

Matrix4x4::Matrix4x4(const Matrix4x4& other)
    : Logging("Matrix4x4") {
    for(int i = 0; i < 16; i++) {
        _data[i] = other._data[i];
    }
}

QString Matrix4x4::className() {
    return "Matrix4x4";
}

QJsonObject Matrix4x4::serialize() {
    QJsonObject jsonObject;
    jsonObject["class"] = className();

    QJsonArray array;
    for(int i = 0; i < 16; i++) {
        array[i] = _data[i];
    }
    jsonObject["data"] = array;
    return jsonObject;
}

bool Matrix4x4::deserialize(QJsonObject json) {
    if(!json.contains("class")) {
        _deserializationError = Serializable::NoClassSpecified;
        return false;
    }

    if(json.contains("data")) {
        if(json["class"] == className()) {
            QJsonArray array = json["data"].toArray();
            for(int i = 0; i < 16; i++) {
                _data[i] = array[i].toDouble();
            }
            _deserializationError = Serializable::NoError;
            return true;
        } else {
            _deserializationError = Serializable::WrongClass;
            return false;
        }
    } else {
        _deserializationError = Serializable::MissingElements;
        return false;
    }
}

Matrix4x4 Matrix4x4::multiplicate(Matrix4x4 with) {
    Matrix4x4 result;
    int i, j;

    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            result._data[i * 4 + j] =
                    _data[i * 4 + 0] * with._data[0 * 4 + j] +
                    _data[i * 4 + 1] * with._data[1 * 4 + j] +
                    _data[i * 4 + 2] * with._data[2 * 4 + j] +
                    _data[i * 4 + 3] * with._data[3 * 4 + j];
        }
    }
    return result;
}

Vector4D Matrix4x4::multiplicate(Vector4D with) {
    Vector4D result;

    result.setX(with.x() * _data[0] + with.y() * _data[4] + with.z() * _data[8] + with.w() * _data[12]);
    result.setY(with.x() * _data[1] + with.y() * _data[5] + with.z() * _data[9] + with.w() * _data[13]);
    result.setZ(with.x() * _data[2] + with.y() * _data[6] + with.z() * _data[10] + with.w() * _data[14]);
    result.setW(with.x() * _data[3] + with.y() * _data[7] + with.z() * _data[11] + with.w() * _data[15]);

    return result;
}

bool Matrix4x4::invert(Matrix4x4 *result) {
    double inverse[16], determinant;
    inverse[0] =  _data[5]*_data[10]*_data[15] - _data[5]*_data[11]*_data[14] - _data[9]*_data[6]*_data[15]
            + _data[9]*_data[7]*_data[14] + _data[13]*_data[6]*_data[11] - _data[13]*_data[7]*_data[10];
    inverse[4] =  -_data[4]*_data[10]*_data[15] + _data[4]*_data[11]*_data[14] + _data[8]*_data[6]*_data[15]
            - _data[8]*_data[7]*_data[14] - _data[12]*_data[6]*_data[11] + _data[12]*_data[7]*_data[10];
    inverse[8] =   _data[4]*_data[9]*_data[15] - _data[4]*_data[11]*_data[13] - _data[8]*_data[5]*_data[15]
            + _data[8]*_data[7]*_data[13] + _data[12]*_data[5]*_data[11] - _data[12]*_data[7]*_data[9];
    inverse[12] = -_data[4]*_data[9]*_data[14] + _data[4]*_data[10]*_data[13] + _data[8]*_data[5]*_data[14]
            - _data[8]*_data[6]*_data[13] - _data[12]*_data[5]*_data[10] + _data[12]*_data[6]*_data[9];
    inverse[1] =  -_data[1]*_data[10]*_data[15] + _data[1]*_data[11]*_data[14] + _data[9]*_data[2]*_data[15]
            - _data[9]*_data[3]*_data[14] - _data[13]*_data[2]*_data[11] + _data[13]*_data[3]*_data[10];
    inverse[5] =   _data[0]*_data[10]*_data[15] - _data[0]*_data[11]*_data[14] - _data[8]*_data[2]*_data[15]
            + _data[8]*_data[3]*_data[14] + _data[12]*_data[2]*_data[11] - _data[12]*_data[3]*_data[10];
    inverse[9] =  -_data[0]*_data[9]*_data[15] + _data[0]*_data[11]*_data[13] + _data[8]*_data[1]*_data[15]
            - _data[8]*_data[3]*_data[13] - _data[12]*_data[1]*_data[11] + _data[12]*_data[3]*_data[9];
    inverse[13] =  _data[0]*_data[9]*_data[14] - _data[0]*_data[10]*_data[13] - _data[8]*_data[1]*_data[14]
            + _data[8]*_data[2]*_data[13] + _data[12]*_data[1]*_data[10] - _data[12]*_data[2]*_data[9];
    inverse[2] =   _data[1]*_data[6]*_data[15] - _data[1]*_data[7]*_data[14] - _data[5]*_data[2]*_data[15]
            + _data[5]*_data[3]*_data[14] + _data[13]*_data[2]*_data[7] - _data[13]*_data[3]*_data[6];
    inverse[6] =  -_data[0]*_data[6]*_data[15] + _data[0]*_data[7]*_data[14] + _data[4]*_data[2]*_data[15]
            - _data[4]*_data[3]*_data[14] - _data[12]*_data[2]*_data[7] + _data[12]*_data[3]*_data[6];
    inverse[10] =  _data[0]*_data[5]*_data[15] - _data[0]*_data[7]*_data[13] - _data[4]*_data[1]*_data[15]
            + _data[4]*_data[3]*_data[13] + _data[12]*_data[1]*_data[7] - _data[12]*_data[3]*_data[5];
    inverse[14] = -_data[0]*_data[5]*_data[14] + _data[0]*_data[6]*_data[13] + _data[4]*_data[1]*_data[14]
            - _data[4]*_data[2]*_data[13] - _data[12]*_data[1]*_data[6] + _data[12]*_data[2]*_data[5];
    inverse[3] =  -_data[1]*_data[6]*_data[11] + _data[1]*_data[7]*_data[10] + _data[5]*_data[2]*_data[11]
            - _data[5]*_data[3]*_data[10] - _data[9]*_data[2]*_data[7] + _data[9]*_data[3]*_data[6];
    inverse[7] =   _data[0]*_data[6]*_data[11] - _data[0]*_data[7]*_data[10] - _data[4]*_data[2]*_data[11]
            + _data[4]*_data[3]*_data[10] + _data[8]*_data[2]*_data[7] - _data[8]*_data[3]*_data[6];
    inverse[11] = -_data[0]*_data[5]*_data[11] + _data[0]*_data[7]*_data[9] + _data[4]*_data[1]*_data[11]
            - _data[4]*_data[3]*_data[9] - _data[8]*_data[1]*_data[7] + _data[8]*_data[3]*_data[5];
    inverse[15] =  _data[0]*_data[5]*_data[10] - _data[0]*_data[6]*_data[9] - _data[4]*_data[1]*_data[10]
            + _data[4]*_data[2]*_data[9] + _data[8]*_data[1]*_data[6] - _data[8]*_data[2]*_data[5];

    determinant = _data[0] * inverse[0] + _data[1] * inverse[4] + _data[2] * inverse[8] + _data[3] * inverse[12];
    if(determinant == 0) {
        return false;
    }

    determinant = 1.0 / determinant;

    if(result) {
        for(int i = 0; i < 16; i++)
            result->_data[i] = inverse[i] * determinant;
    }

    return true;
}

double Matrix4x4::value(int row, int column) {
    if(row < 0 || row > 3 || column < 0 || column > 3) {
        warning(QString("Accessing matrix outside of range: %1/%2").arg(row).arg(column));
        return 0.0;
    }
    return _data[column * 4 + row];
}

void Matrix4x4::setValue(int row, int column, double value) {
    if(row < 0 || row > 3 || column < 0 || column > 3) {
        warning(QString("Accessing matrix outside of range: %1/%2").arg(row).arg(column));
        return;
    }
    _data[column * 4 + row] = value;
}

double *Matrix4x4::glDataPointer() {
    return _data;
}

void Matrix4x4::setXAxis(Vector3D axis) {
    setLeft(axis);
}

void Matrix4x4::setLeft(Vector3D left) {
    _data[0] = left.x();
    _data[4] = left.y();
    _data[8] = left.z();
}

void Matrix4x4::setYAxis(Vector3D axis) {
    setUp(axis);
}

void Matrix4x4::setUp(Vector3D up) {
    _data[1] = up.x();
    _data[5] = up.y();
    _data[9] = up.z();
}

void Matrix4x4::setZAxis(Vector3D axis) {
    setForward(axis);
}

void Matrix4x4::setForward(Vector3D forward) {
    _data[2] = forward.x();
    _data[6] = forward.y();
    _data[10] = forward.z();
}

void Matrix4x4::setTranslation(Vector3D translation) {
    _data[12] = translation.x();
    _data[13] = translation.y();
    _data[14] = translation.z();
}

Matrix4x4& Matrix4x4::withRotation(Vector3D xAxis,
                                   Vector3D yAxis,
                                   Vector3D zAxis) {
    Matrix4x4 rotationMatrix;
    rotationMatrix.setXAxis(xAxis);
    rotationMatrix.setYAxis(yAxis);
    rotationMatrix.setZAxis(zAxis);
    return (*this) = multiplicate(rotationMatrix);
}

Matrix4x4& Matrix4x4::withRotation(double angle, Vector3D axis) {
    double angleInRadians = angle * M_PI / 180.0;

    double s = sin(angleInRadians);
    double c = cos(angleInRadians);

    axis.normalize();

    double xy = axis.x() * axis.y();
    double yz = axis.y() * axis.z();
    double zx = axis.z() * axis.x();

    double xs = axis.x() * s;
    double ys = axis.y() * s;
    double zs = axis.z() * s;

    Matrix4x4 rotationMatrix;
    rotationMatrix._data[0] = ((1.0 - c) * axis.x() * axis.x()) + c;
    rotationMatrix._data[1] = ((1.0 - c) * xy) + zs;
    rotationMatrix._data[2] = ((1.0 - c) * zx) - ys;

    rotationMatrix._data[4] = ((1.0 - c) * xy) - zs;
    rotationMatrix._data[5] = ((1.0 - c) * axis.y() * axis.y()) + c;
    rotationMatrix._data[6] = ((1.0 - c) * yz) + xs;

    rotationMatrix._data[8] = ((1.0 - c) * zx) + ys;
    rotationMatrix._data[9] = ((1.0 - c) * yz) - xs;
    rotationMatrix._data[10] = ((1.0 - c) * axis.z() * axis.z()) + c;

    return (*this) = multiplicate(rotationMatrix);
}

Matrix4x4& Matrix4x4::withTranslation(Vector3D translation) {
    Matrix4x4 translationMatrix;
    translationMatrix.setTranslation(translation);
    return (*this) = multiplicate(translationMatrix);
}

} // namespace Glee3D
