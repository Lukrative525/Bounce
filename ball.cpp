#include "ball.hpp"

Ball::Ball(double x, double y, double z, double radius):
    position{x, y, z},
    nextPosition{},
    velocity{},
    nextVelocity{},
    radius{radius} {}

void Ball::confirmNext()
{
    position = nextPosition;
    velocity = nextVelocity;
}

void Ball::set_color(float brightness, float opacity)
{
    for (int i{0}; i < 3; i++)
    {
        color[i] = brightness;
    }

    color[3] = opacity;
}

void Ball::set_color(glm::vec4 color)
{
    this->color = color;
}
