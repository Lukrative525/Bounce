#include "ball.hpp"

Ball::Ball(double x, double y, double z, double radius):
    position{x, y, z},
    nextPosition{},
    velocity{},
    nextVelocity{},
    radius{radius} {}
