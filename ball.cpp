#include "ball.hpp"

Ball::Ball(double x, double y, double z, double radius):
    position{x, y, z},
    nextPosition{x, y, z},
    radius{radius} {}

void Ball::confirm_next()
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

    color.a = opacity;
}

void Ball::set_color(float R, float G, float B, float a)
{
    color.r = R;
    color.g = G;
    color.b = B;
    color.a = a;
}
