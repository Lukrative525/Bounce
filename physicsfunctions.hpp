#ifndef PHYSICSFUNCTIONS_HPP
#define PHYSICSFUNCTIONS_HPP

class Vector3D;
class Ball;

namespace phys
{
void update_next_implicit_euler(const double& timeStep, Ball& ball, const Vector3D& acceleration);
}

#endif // PHYSICSFUNCTIONS_HPP
