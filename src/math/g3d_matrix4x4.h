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

#ifndef G3D_MATRIX4X4_H
#define G3D_MATRIX4X4_H

// Own includes
#include "math/g3d_vector3d.h"
#include "math/g3d_vector4d.h"
#include "io/g3d_serializable.h"
#include "core/g3d_logging.h"

namespace Glee3D {

class Matrix4x4 :
    public Serializable,
    public Logging {
public:
    /** Creates a new matrix. It will be an identity matrix by default. */
    Matrix4x4() :
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

    Matrix4x4(const Matrix4x4& other)
        : Logging("Matrix4x4") {
        for(int i = 0; i < 16; i++) {
            _data[i] = other._data[i];
        }
    }

    QString className() {
        return "Matrix4x4";
    }

    QJsonObject serialize() {
        QJsonObject jsonObject;
        jsonObject["class"] = className();

        QJsonArray array;
        for(int i = 0; i < 16; i++) {
            array[i] = _data[i];
        }
        jsonObject["data"] = array;
        return jsonObject;
    }

    bool deserialize(QJsonObject json) {
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

    /**
     * Multiplicates the given matrix with this matrix.
     * @param with The matrix to multiplicate with.
     * @returns the resulting matrix.
     */
    Matrix4x4 multiplicate(Matrix4x4 with) {
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

    /**
     * Multiplicates the given vector with this matrix.
     * @param with The vector to multiplicate with.
     * @returns the resulting vector.
     */
    Vector4D multiplicate(Vector4D with) {
        Vector4D result;

        result._x = with._x * _data[0] + with._y * _data[4] + with._z * _data[8] + with._w * _data[12];
        result._y = with._x * _data[1] + with._y * _data[5] + with._z * _data[9] + with._w * _data[13];
        result._z = with._x * _data[2] + with._y * _data[6] + with._z * _data[10] + with._w * _data[14];
        result._w = with._x * _data[3] + with._y * _data[7] + with._z * _data[11] + with._w * _data[15];

        return result;
    }

    /**
     * Inverts the matrix and stores the result.
     * @param result If not zero, the result matrix will be stores in this parameter.
     * @return true, if the matrix inversion was possible.
     */
    bool invert(Matrix4x4 *result = 0) {
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

    /**
     * Retrieves a value from the matrix. This does bounds-checking, so it may be slow.
     * If you are sure you are not violating any bounds, you may want to look into
     * reading and writing directly on the matrix memory.
     * @param row The row of the element you want to access.
     * @param column The column of the element you want to access.
     * @returns the requested element.
     */
    double value(int row, int column) {
        if(row < 0 || row > 3 || column < 0 || column > 3) {
            warning(QString("Accessing matrix outside of range: %1/%2").arg(row).arg(column));
            return 0.0;
        }
        return _data[column * 4 + row];
    }

    /**
     * Stores a value in the matrix. This does bounds-checking, so it may be slow.
     * If you are sure you are not violating any bounds, you may want to look into
     * reading and writing directly on the matrix memory.
     * @param row The row of the element you want to access.
     * @param column The column of the element you want to access.
     */
    void setValue(int row, int column, double value) {
        if(row < 0 || row > 3 || column < 0 || column > 3) {
            warning(QString("Accessing matrix outside of range: %1/%2").arg(row).arg(column));
            return;
        }
        _data[column * 4 + row] = value;
    }

    /**
     * @returns a pointer to the internal matrix structure. The internal
     * structure is compatible to the OpenGL matrices, ie. the data is aligned
     * like in OpenGL and can be modified using GL functions. Please be aware that
     * this is unsafe to do and should be avoided only if you know what you're doing
     * and/or you provide your own error checking code.
     */
    double *data() {
        return _data;
    }

    /**
     * Sets the x axis in a right-handed coordinate system.
     * @param axis The axis vector.
     */
    void setXAxis(Vector3D axis) {
        setLeft(axis);
    }

    /**
     * Same as setXAxis();
     */
    void setLeft(Vector3D left) {
        _data[0] = left._x;
        _data[4] = left._y;
        _data[8] = left._z;
    }

    /**
     * Sets the y axis in a right-handed coordinate system.
     * @param axis The axis vector.
     */
    void setYAxis(Vector3D axis) {
        setUp(axis);
    }

    /**
     * Same as setYAxis();
     */
    void setUp(Vector3D up) {
        _data[1] = up._x;
        _data[5] = up._y;
        _data[9] = up._z;
    }

    /**
     * Sets the z axis in a right-handed coordinate system.
     * @param axis The axis vector.
     */
    void setZAxis(Vector3D axis) {
        setForward(axis);
    }

    /**
     * Same as setZAxis();
     */
    void setForward(Vector3D forward) {
        _data[2] = forward._x;
        _data[6] = forward._y;
        _data[10] = forward._z;
    }

    /**
     * Sets the translation vector.
     * @param translation The translation vector.
     */
    void setTranslation(Vector3D translation) {
        _data[12] = translation._x;
        _data[13] = translation._y;
        _data[14] = translation._z;
    }

    void addRotation(Vector3D xAxis,
                     Vector3D yAxis,
                     Vector3D zAxis) {
        Matrix4x4 rotationMatrix;
        rotationMatrix.setXAxis(xAxis);
        rotationMatrix.setYAxis(yAxis);
        rotationMatrix.setZAxis(zAxis);
        (*this) = multiplicate(rotationMatrix);
    }

    void addTranslation(Vector3D translation) {
        Matrix4x4 translationMatrix;
        translationMatrix.setTranslation(translation);
        (*this) = multiplicate(translationMatrix);
    }

private:
    /**
     * @attention data is order column-wise, which can lead to confusion
     * when operating on this with OpenGL function, ie. index 0-3 represent
     * the first column, not the first row.
     */
    double _data[16];
};

} // namespace Glee3D

#endif // G3D_MATRIX4X4_H
