#include "physicsfunctions.hpp"
#include "vector3d.hpp"
#include "ball.hpp"

namespace phys
{
    void update_next_implicit_euler(const double& timeStep, Ball& ball, const Vector3D& acceleration)
    {
        ball.nextVelocity = ball.velocity + acceleration * timeStep;
        ball.nextPosition = ball.position + ball.nextVelocity * timeStep;
    }

    void reflect_vector(Vector3D& vectorToReflect, const Vector3D& normal)
    {
        vectorToReflect = vectorToReflect - 2 * (vectorToReflect.dot(normal / normal.calculate_magnitude()) * normal / normal.calculate_magnitude());
    }

    double distance_between(const Vector3D& point1, const Vector3D& point2)
    {
        double distance = (point1 - point2).calculate_magnitude();

        return distance;
    }
}
