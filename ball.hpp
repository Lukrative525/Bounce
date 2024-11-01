#ifndef BALL_HPP
#define BALL_HPP

#include "vector3d.hpp"

class Ball
{
public:
    Ball(double x, double y, double z, double radius);
    Vector3D position;
    double radius;
};

#endif // BALL_HPP
