#include <math.h>
#include "point.h"

Point::Point() :
    x(0.0f),
    y(0.0f),
    z(0.0f)
{
}

Point::Point(float x, float y, float z) :
    x(x),
    y(y),
    z(z)
{
}

Point::Point(vec2_t point) :
    x(point.x),
    y(point.y),
    z(0.0f)
{
}

Point::Point(vec3_t point) :
    x(point.x),
    y(point.y),
    z(point.z)
{
}

Point Point::operator +(const Point & other) const
{
    return Point(x+other.x, y+other.y, z+other.z);
}

Point Point::operator -(const Point & other) const
{
    return Point(x-other.x, y-other.y, z-other.z);
}

float Point::operator *(const Point & other) const
{
    return (x*other.x) + (y*other.y) + (z*other.z);
}

Point Point::operator *(const float scale) const
{
    return Point(x*scale, y*scale, z*scale);
}

Point Point::operator /(const float scale) const
{
    return Point(x/scale, y/scale, z/scale);
}

Point & Point::operator =(const float scale)
{
    x = y = z = scale;
    return *this;
}

Point & Point::operator =(const vec2_t point)
{
    x = point.x;
    y = point.y;
    z = 0;
    return *this;
}

Point & Point::operator =(const vec3_t point)
{
    x = point.x;
    y = point.y;
    z = point.z;
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
