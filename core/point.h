#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point();
    Point(float x, float y, float z);

    /**
      * Vector Addition
      */
    Point operator +(const Point & other);

    /**
      * Vector Subtraction
      */
    Point operator -(const Point & other);

    /**
      * Scaler Multiplication
      */
    Point operator *(const float scale);

    /**
      * Vector Adition
      */
    Point & operator +=(const Point & other);

    /**
      * Vector Subraction
      */
    Point & operator -=(const Point & other);

    /**
      * Scaler Multiplication
      */
    Point & operator *=(const float scale);

    float x;
    float y;
    float z;
};

#endif // POINT_H
