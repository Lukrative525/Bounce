#ifndef BALL_HPP
#define BALL_HPP

#include <glm/glm.hpp>
#include "vector3d.hpp"

class Ball
{
public:
    Ball(double x = 0, double y = 0, double z = 0, double radius = 1);
    void confirmNext();
    void set_color(float brightness, float opacity);
    void set_color(glm::vec4 color);
    Vector3D position;
    Vector3D nextPosition;
    Vector3D velocity;
    Vector3D nextVelocity;
    double radius;
    glm::vec4 color;
};

#endif // BALL_HPP
