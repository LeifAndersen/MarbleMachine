#include "matrix.h"
#include <cmath>
Matrix::Matrix()
{
    matrix.reserve(16);
    for(int i = 0; i < 16; i++)
        matrix.push_back(0);
}

void Matrix::scale(float sx, float sy, float sz) {
    matrix[0 * 4 + 0] *= sx;
    matrix[0 * 4 + 1] *= sx;
    matrix[0 * 4 + 2] *= sx;
    matrix[0 * 4 + 3] *= sx;

    matrix[1 * 4 + 0] *= sy;
    matrix[1 * 4 + 1] *= sy;
    matrix[1 * 4 + 2] *= sy;
    matrix[1 * 4 + 3] *= sy;

    matrix[2 * 4 + 0] *= sz;
    matrix[2 * 4 + 1] *= sz;
    matrix[2 * 4 + 2] *= sz;
    matrix[2 * 4 + 3] *= sz;
}

void Matrix::loadIdentity()
{
    for(int i = 0; i < 16; i++)
        matrix[i] = 0.0f;
    matrix[0 * 4 + 0] = 1.0f;
    matrix[1 * 4 + 1] = 1.0f;
    matrix[2 * 4 + 2] = 1.0f;
    matrix[3 * 4 + 3] = 1.0f;
    matrix[4 * 4 + 4] = 1.0f;
}


void Matrix::perspective(float fovy, float aspect, float nearZ, float farZ) {
    float frustumW, frustumH;

    frustumH = (float) tan(fovy / 360.0 * M_2_PI) * nearZ;
    frustumW = frustumH * aspect;

    frustum(-frustumW, frustumW, -frustumH, frustumH, nearZ, farZ);
}

void Matrix::ortho(float left, float right, float bottom, float top,
                   float nearZ, float farZ) {
    float deltaX = right - left;
    float deltaY = top - bottom;
    float deltaZ = farZ - nearZ;
    Matrix orthoMat;
    orthoMat.loadIdentity();

    if ((deltaX == 0.0f) || (deltaY == 0.0f) || (deltaZ == 0.0f))
        return;

    orthoMat.matrix[0 * 4 + 0] = 2.0f / deltaX;
    orthoMat.matrix[3 * 4 + 0] = -(right + left) / deltaX;
    orthoMat.matrix[1 * 4 + 1] = 2.0f / deltaY;
    orthoMat.matrix[3 * 4 + 1] = -(top + bottom) / deltaY;
    orthoMat.matrix[2 * 4 + 2] = -2.0f / deltaZ;
    orthoMat.matrix[3 * 4 + 2] = -(nearZ + farZ) / deltaZ;

    matrix = (orthoMat*(*this)).matrix;
}

void Matrix::frustum(float left, float right, float bottom, float top,
                     float nearZ, float farZ) {
    float deltaX = right - left;
    float deltaY = top - bottom;
    float deltaZ = farZ - nearZ;
    Matrix frust;

    if ((nearZ <= 0.0f) || (farZ <= 0.0f) || (deltaX <= 0.0f)
            || (deltaY <= 0.0f) || (deltaZ <= 0.0f))
        return;

    frust.matrix[0 * 4 + 0] = 2.0f * nearZ / deltaX;
    frust.matrix[0 * 4 + 1] = frust.matrix[0 * 4 + 2] =
            frust.matrix[0 * 4 + 3] = 0.0f;

    frust.matrix[1 * 4 + 1] = 2.0f * nearZ / deltaY;
    frust.matrix[1 * 4 + 0] = frust.matrix[1 * 4 + 2] =
            frust.matrix[1 * 4 + 3] = 0.0f;

    frust.matrix[2 * 4 + 0] = (right + left) / deltaX;
    frust.matrix[2 * 4 + 1] = (top + bottom) / deltaY;
    frust.matrix[2 * 4 + 2] = -(nearZ + farZ) / deltaZ;
    frust.matrix[2 * 4 + 3] = -1.0f;

    frust.matrix[3 * 4 + 2] = -2.0f * nearZ * farZ / deltaZ;
    frust.matrix[3 * 4 + 0] = frust.matrix[3 * 4 + 1] =
            frust.matrix[3 * 4 + 3] = 0.0f;

    matrix = (frust*(*this)).matrix;
}

void Matrix::rotate(float angle, float x, float y, float z) {
    float sinAngle, cosAngle;
    float mag = sqrt(x * x + y * y + z * z);

    sinAngle = sin(angle * M_PI / 180.0);
    cosAngle = cos(angle * M_PI / 180.0);
    if (mag > 0.0f) {
        float xx, yy, zz, xy, yz, zx, xs, ys, zs;
        float oneMinusCos;
        Matrix rotMat;

        x /= mag;
        y /= mag;
        z /= mag;

        xx = x * x;
        yy = y * y;
        zz = z * z;
        xy = x * y;
        yz = y * z;
        zx = z * x;
        xs = x * sinAngle;
        ys = y * sinAngle;
        zs = z * sinAngle;
        oneMinusCos = 1.0f - cosAngle;

        rotMat.matrix[0 * 4 + 0] = (oneMinusCos * xx) + cosAngle;
        rotMat.matrix[0 * 4 + 1] = (oneMinusCos * xy) - zs;
        rotMat.matrix[0 * 4 + 2] = (oneMinusCos * zx) + ys;
        rotMat.matrix[0 * 4 + 3] = 0.0F;

        rotMat.matrix[1 * 4 + 0] = (oneMinusCos * xy) + zs;
        rotMat.matrix[1 * 4 + 1] = (oneMinusCos * yy) + cosAngle;
        rotMat.matrix[1 * 4 + 2] = (oneMinusCos * yz) - xs;
        rotMat.matrix[1 * 4 + 3] = 0.0F;

        rotMat.matrix[2 * 4 + 0] = (oneMinusCos * zx) - ys;
        rotMat.matrix[2 * 4 + 1] = (oneMinusCos * yz) + xs;
        rotMat.matrix[2 * 4 + 2] = (oneMinusCos * zz) + cosAngle;
        rotMat.matrix[2 * 4 + 3] = 0.0F;

        rotMat.matrix[3 * 4 + 0] = 0.0F;
        rotMat.matrix[3 * 4 + 1] = 0.0F;
        rotMat.matrix[3 * 4 + 2] = 0.0F;
        rotMat.matrix[3 * 4 + 3] = 1.0F;

        matrix = (rotMat*(*this)).matrix;
    }
}

void Matrix::translate(float tx, float ty, float tz) {
    for(int i = 0; i < 4; i++)
        matrix[3 * 4 + i] += (matrix[0 * 4 + i] * tx + matrix[1 * 4 + i]
                          * ty + matrix[2 * 4 + i] * tz);
}

Matrix Matrix::operator *(Matrix & other)
{
    Matrix temp;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            temp.matrix[i*4+j] =
                    (matrix[i * 4 + 0] * other.matrix[0 * 4 + j])
                    + (matrix[i * 4 + 1] * other.matrix[1 * 4 + j])
                    + (matrix[i * 4 + 2] * other.matrix[2 * 4 + j])
                    + (matrix[i * 4 + 3] * other.matrix[3 * 4 + j]);

    return temp;
}
