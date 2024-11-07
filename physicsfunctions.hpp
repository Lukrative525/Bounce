#ifndef PHYSICSFUNCTIONS_HPP
#define PHYSICSFUNCTIONS_HPP

class Vector3D;
class Ball;

namespace phys
{
void update_next_implicit_euler(const double& timeStep, Ball& ball, const Vector3D& acceleration);
void reflect_vector(Vector3D& vectorToFlip, const Vector3D &normal);
double distance_between(const Vector3D& point1, const Vector3D& point2);
}

#endif // PHYSICSFUNCTIONS_HPP
