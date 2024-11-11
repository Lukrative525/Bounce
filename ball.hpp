#ifndef BALL_HPP
#define BALL_HPP

#include <glm/glm.hpp>
#include "vector3d.hpp"

class Ball
{
public:
    Ball(double x = 0, double y = 0, double z = 0, double radius = 1);
    void confirm_next();
    void set_color(float brightness, float opacity);
    void set_color(float R, float G, float B, float a);
    Vector3D position;
    Vector3D nextPosition;
    Vector3D velocity;
    Vector3D nextVelocity;
    double radius;
    double elasticity{1};
    glm::vec4 color{1.0, 1.0, 1.0, 1.0};
};

#endif // BALL_HPP
