#include "ball.hpp"

Ball::Ball(double x, double y, double z, double radius):
    position{x, y, z},
    nextPosition{x, y, z},
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

void Ball::set_color(float R, float G, float B, float a)
{
    color[0] = R;
    color[1] = G;
    color[2] = B;
    color[3] = a;
}
