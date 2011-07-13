#include <math.h>
#include "Point.h"

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

Point Point::operator +(const Point & other) const
{
    Point p;
    p.x = x + other.x;
    p.y = y + other.y;
    p.z = z + other.z;
    return p;
}

Point Point::operator -(const Point & other) const
{
    Point p;
    p.x = x - other.x;
    p.y = y - other.y;
    p.z = z - other.z;
    return p;
}

float Point::operator *(const Point & other) const
{
    return (x*other.x) + (y*other.y) + (z*other.z);
}

Point Point::operator *(const float scale) const
{
    Point p;
    p.x = x * scale;
    p.y = y * scale;
    p.z = z * scale;
    return p;
}

Point Point::operator /(const float scale) const
{
    Point p;
    p.x = x / scale;
    p.y = y / scale;
    p.z = z / scale;
    return p;
}

Point & Point::operator =(const float scale)
{
    x = y = z = scale;
    return *this;
}

Point & Point::operator +=(const Point & other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Point & Point::operator -=(const Point & other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Point & Point::operator *=(const float scale)
{
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
}

Point & Point::operator /=(const float scale)
{
    x /= scale;
    y /= scale;
    z /= scale;
    return *this;
}

float Point::magnitude() const
{
    return sqrt((x*x)+(y*y)+(z*z));
}

float Point::magnitudeSquared() const
{
    return (x*x)+(y*y)+(z*z);
}

void Point::normalize()
{
    float mag = magnitude();
    x = x/mag;
    y = y/mag;
    z = z/mag;
}

Point Point::normal_vector() const
{
    Point p;
    float mag = magnitude();
    p.x = x/mag;
    p.y = y/mag;
    p.z = z/mag;
    return p;
}

float Point::angle(const Point & other) const
{
    return acos(((*this)*other)/(magnitude()*(other.magnitude())));
}

Point Point::cross_product(const Point & other) const
{
    Point p;
    p.x = (y*other.z) - (z*other.y);
    p.y = (z*other.x) - (x*other.z);
    p.z = (x*other.y) - (y*other.x);
    return p;
}
