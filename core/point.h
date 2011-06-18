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
    Point operator +(const Point & other) const;

    /**
      * Vector Subtraction
      */
    Point operator -(const Point & other) const;

    /**
      * Dot product
      */
    float operator *(const Point & other) const;

    /**
      * Scaler Multiplication
      */
    Point operator *(const float scale) const;

    /**
      * Scaler Division
      */
    Point operator /(const float scale) const;

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

    /**
      * Scaler Division
      */
    Point & operator /=(const float scale);

    /**
      * Returns the vector magnitude
      */
    float magnitude() const;

    /**
      * Returns the vector magnitude squared (faster than magnitude).
      */
    float magnitudeSquared() const;

    /**
      * Normalize THIS vector
      */
    void normalize();

    /**
      * Return a vector that is the normal of this vector
      */
    Point normal_vector() const;

    /**
      * Return the angle between two points
      */
    float angle(const Point & other) const;

    /**
      * Calculate the cross product in right hand space
      */
    Point cross_product(const Point & other) const;

    /**
      * Coordinates
      */
    float x;
    float y;
    float z;
};

#endif // POINT_H
