#pragma once
#include "math.h"

class Vector
{
public:
    float x, y;

    Vector(float x = 0, float y = 0)
    {
        this->x = x;
        this->y = y;
    }

    float radians(float degrees)
    {
        return degrees * M_PI / 180;
    }

    float degrees(float radians)
    {
        return radians * 180 / M_PI;
    }

    float getMagnitude()
    {
        return hypot(x, y);
    }

    void add(Vector obj)
    {
        x += obj.x;
        y += obj.y;
    }

    Vector getAdded(Vector obj)
    {
        return Vector{x + obj.x, y + obj.y};
    }

    void subtract(Vector obj)
    {
        x -= obj.x;
        y -= obj.y;
    }

    Vector getSubtracted(Vector obj)
    {

        return Vector{x - obj.x, y - obj.y};
    }

    void scale(float k)
    {
        x *= k;
        y *= k;
    }

    Vector getScaled(float k)
    {
        return Vector{x * k, y * k};
    }

    void divide(float k)
    {
        x /= k;
        y /= k;
    }

    Vector getDivided(float k)
    {
        return Vector{x / k, y / k};
    }

    float getAngle()
    {
        return degrees(atan2(x, y));
    }

    void rotateCCW(float angle)
    {
        angle = radians(angle);
        *this = Vector{x * cos(angle) - y * sin(angle), y * cos(angle) + x * sin(angle)};
    }

    // return this vector rotated by the given angle
    Vector getRotatedCCW(float angle)
    {
        angle = radians(angle);
        return Vector{x * cos(angle) - y * sin(angle), y * cos(angle) + x * sin(angle)};
    }

    // reset the vector to {0, 0}
    void reset()
    {
        x = 0;
        y = 0;
    }
};

/*
includes the abs() function for Vectors
*/
namespace t2D {
    // return the magnitude of a Vector
    float abs(Vector obj) {
        return std::hypot(obj.x, obj.y);
    }
}