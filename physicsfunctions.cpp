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
}
