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
    Matrix4x4();
    Matrix4x4(const Matrix4x4& other);

    QString className();
    QJsonObject serialize();
    bool deserialize(QJsonObject json);

    /**
     * Multiplicates the given matrix with this matrix.
     * @param with The matrix to multiplicate with.
     * @returns the resulting matrix.
     */
    Matrix4x4 multiplicate(Matrix4x4 with);

    /**
     * Multiplicates the given vector with this matrix.
     * @param with The vector to multiplicate with.
     * @returns the resulting vector.
     */
    Vector4D multiplicate(Vector4D with);

    /**
     * Inverts the matrix and stores the result.
     * @param result If not zero, the result matrix will be stores in this parameter.
     * @return true, if the matrix inversion was possible.
     */
    bool invert(Matrix4x4 *result = 0);

    /**
     * Retrieves a value from the matrix. This does bounds-checking, so it may be slow.
     * If you are sure you are not violating any bounds, you may want to look into
     * reading and writing directly on the matrix memory.
     * @param row The row of the element you want to access.
     * @param column The column of the element you want to access.
     * @returns the requested element.
     */
    double value(int row, int column);

    /**
     * Stores a value in the matrix. This does bounds-checking, so it may be slow.
     * If you are sure you are not violating any bounds, you may want to look into
     * reading and writing directly on the matrix memory.
     * @param row The row of the element you want to access.
     * @param column The column of the element you want to access.
     */
    void setValue(int row, int column, double value);

    /**
     * @returns a pointer to the internal matrix structure. The internal
     * structure is compatible to the OpenGL matrices, ie. the data is aligned
     * like in OpenGL and can be modified using GL functions. Please be aware that
     * this is unsafe to do and should be avoided only if you know what you're doing
     * and/or you provide your own error checking code.
     */
    double *glDataPointer();

    /**
     * Sets the x axis in a right-handed coordinate system.
     * @param axis The axis vector.
     */
    void setXAxis(Vector3D axis);

    /**
     * Same as setXAxis();
     */
    void setLeft(Vector3D left);

    /**
     * Sets the y axis in a right-handed coordinate system.
     * @param axis The axis vector.
     */
    void setYAxis(Vector3D axis);

    /**
     * Same as setYAxis();
     */
    void setUp(Vector3D up);

    /**
     * Sets the z axis in a right-handed coordinate system.
     * @param axis The axis vector.
     */
    void setZAxis(Vector3D axis);

    /**
     * Same as setZAxis();
     */
    void setForward(Vector3D forward);

    /**
     * Sets the translation vector.
     * @param translation The translation vector.
     */
    void setTranslation(Vector3D translation);

    /**
     * Creates a rotation matrix calculated from a base. That means that
     * it will rotate relative to the identity.
     * @attention Please understand that consecutive operations will be
     * processed in reverse order, ie. the action you apply last will be
     * executed first. If you have a translation T and a rotation R and
     * you do C = I x T x R, the rotation will take place first, then the
     * translation.
     * @param xAxis Relative x-axis of the rotated coordinate system.
     * @param yAxis Relative y-axis of the rotated coordinate system.
     * @param zAxis Relative z-axis of the rotated coordinate system.
     * @returns a reference to itself, so you can chain calls.
     */
    Matrix4x4& withRotation(Vector3D xAxis,
                            Vector3D yAxis,
                            Vector3D zAxis);

    /**
     * Creates a rotation matrix calculated from a rotational axis and
     * an angle.
     * @param angle The rotation angle in degrees.
     * @param axis The rotational axis.
     * @return
     */
    Matrix4x4& withRotation(double angle, Vector3D axis);

    /**
     * Creates a translation matrix with the given value and multiplies
     * it on this matrix.
     * @attention Please understand that consecutive operations will be
     * processed in reverse order, ie. the action you apply last will be
     * executed first. If you have a translation T and a rotation R and
     * you do C = I x T x R, the rotation will take place first, then the
     * translation.
     * @param translation The relative translation vector.
     * @returns a reference to itself, so you can chain calls.
     */
    Matrix4x4&  withTranslation(Vector3D translation);

private:
    /**
     * @attention data is order column-wise, which can lead to confusion
     * when operating on this with OpenGL function, ie. index 0-3 represent
     * the first column, not the first row, like this:
     *  0  4  8  12
     *  1  5  9  13
     *  2  6  10 14
     *  3  7  11 15
     */
    double _data[16];
};

} // namespace Glee3D

#endif // G3D_MATRIX4X4_H
