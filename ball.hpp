#ifndef BALL_HPP
#define BALL_HPP

#include "vector3d.hpp"

class Ball
{
public:
    Ball(double x = 0, double y = 0, double z = 0, double radius = 1);
    Vector3D position;
    Vector3D nextPosition;
    Vector3D velocity;
    Vector3D nextVelocity;
    double radius;
};

#endif // BALL_HPP
