#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point();
    Point(float x, float y, float z);

    Point operator +(const Point & other);
    Point operator -(const Point & other);
    Point operator *(const float scale);
    Point & operator +=(const Point & other);
    Point & operator -=(const Point & other);
    Point & operator *=(const float scale);
    float x;
    float y;
    float z;
};

#endif // POINT_H
