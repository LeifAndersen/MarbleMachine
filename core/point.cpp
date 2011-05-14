#include "point.h"

Point::Point()
{
    x = y = z = 0.0f;
}

Point::Point(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Point Point::operator +(const Point & other)
{
    Point p;
    p.x = x + other.x;
    p.y = y + other.y;
    p.z = z + other.z;
    return p;
}

Point Point::operator -(const Point & other)
{
    Point p;
    p.x = x - other.x;
    p.y = y - other.y;
    p.z = z - other.z;
    return p;
}

Point Point::operator *(const float scale)
{
    Point p;
    p.x = x * scale;
    p.y = y * scale;
    p.z = z * scale;
    return p;
}

Point & Point::operator +=(const Point & other)
{
    return *this;
}

Point & Point::operator -=(const Point & other)
{
    return *this;
}

Point & Point::operator *=(const float scale)
{
    return *this;
}
