#include "matrix.h"
#include <cmath>
Matrix::Matrix()
{
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

    matrixMultiply(orthoMat.matrix);
}

void Matrix::frustum(float left, float right, float bottom, float top,
                     float nearZ, float farZ) {
    float deltaX = right - left;
    float deltaY = top - bottom;
    float deltaZ = farZ - nearZ;
    float frust[16];

    if ((nearZ <= 0.0f) || (farZ <= 0.0f) || (deltaX <= 0.0f)
            || (deltaY <= 0.0f) || (deltaZ <= 0.0f))
        return;

    frust[0 * 4 + 0] = 2.0f * nearZ / deltaX;
    frust[0 * 4 + 1] = frust[0 * 4 + 2] = frust[0 * 4 + 3] = 0.0f;

    frust[1 * 4 + 1] = 2.0f * nearZ / deltaY;
    frust[1 * 4 + 0] = frust[1 * 4 + 2] = frust[1 * 4 + 3] = 0.0f;

    frust[2 * 4 + 0] = (right + left) / deltaX;
    frust[2 * 4 + 1] = (top + bottom) / deltaY;
    frust[2 * 4 + 2] = -(nearZ + farZ) / deltaZ;
    frust[2 * 4 + 3] = -1.0f;

    frust[3 * 4 + 2] = -2.0f * nearZ * farZ / deltaZ;
    frust[3 * 4 + 0] = frust[3 * 4 + 1] = frust[3 * 4 + 3] = 0.0f;

    matrixMultiply(frust);
}

