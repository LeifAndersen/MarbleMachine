#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
    Matrix();
    void loadIdentity();
    void scale(float sx, float sy, float sz);
    void perspective(float fovy, float aspect, float nearZ, float farZ);
    void ortho(float left, float right, float bottom, float top,
               float nearZ, float farZ);
    void frustum(float left, float right, float bottom, float top,
                 float nearZ, float farZ);
private:
    float matrix[16];
};

#endif // MATRIX_H
