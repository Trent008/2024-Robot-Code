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

    Vector operator+(Vector obj)
    {
        return Vector{x + obj.x, y + obj.y};
    }

    Vector operator-(Vector obj)
    {

        return Vector{x - obj.x, y - obj.y};
    }

    Vector operator*(float k)
    {
        return Vector{x * k, y * k};
    }

    Vector operator/(float k)
    {
        return Vector{x / k, y / k};
    }

    float getMagnitude()
    {
        return std::hypot(x, y);
    }

    float getAngle()
    {
        return atan2(x, y)*180/M_PI;
    }

    Vector getRotatedCCW(float angle)
    {
        angle = angle*M_PI/180;
        return Vector{x * cos(angle) - y * sin(angle), y * cos(angle) + x * sin(angle)};
    }
};