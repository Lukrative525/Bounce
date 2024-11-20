#include "physicsfunctions.hpp"
#include "vector3d.hpp"
#include "ball.hpp"

// TODO: finish unit tests for these functions

namespace phys
{
    void update_next_state_implicit_euler(const double& timeStep, Ball& ball, const Vector3D& acceleration)
    {
        if (ball.isMovable)
        {
            ball.nextVelocity = ball.velocity + acceleration * timeStep;
            ball.nextPosition = ball.position + ball.nextVelocity * timeStep;
        }
    }

    void reflect_vector(Vector3D& vectorToReflect, const Vector3D& normal)
    {
        vectorToReflect = vectorToReflect - 2 * (vectorToReflect.dot(normal / normal.calculate_magnitude()) * normal / normal.calculate_magnitude());
    }

    double calculate_distance_between(const Vector3D& point1, const Vector3D& point2)
    {
        double distance = (point1 - point2).calculate_magnitude();

        return distance;
    }

    bool detect_collision_with_container(const Ball& ball, const Ball& container)
    {
        bool collisionDetected = calculate_distance_between(ball.nextPosition, container.position) > (container.radius - ball.radius);

        return collisionDetected;
    }

    bool detect_collision_between_balls(const Ball& ball1, const Ball& ball2)
    {
        bool collisionDetected = calculate_distance_between(ball1.nextPosition, ball2.nextPosition) < (ball1.radius + ball2.radius);

        return collisionDetected;
    }

    void resolve_collision(Ball& ball1, Ball& ball2)
    {
        if (ball1.isMovable && ball2.isMovable)
        {
            resolve_collision_between_movable_balls(ball1, ball2);
        }
        else if (ball1.isMovable)
        {
            resolve_collision_with_immovable_ball(ball1, ball2);
        }
        else if (ball2.isMovable)
        {
            resolve_collision_with_immovable_ball(ball2, ball1);
        }
    }

    void resolve_collision_with_container(Ball& movingBall, const Ball& container)
    {
        Vector3D contactNormal = container.position - movingBall.nextPosition;
        contactNormal.normalize();
        double maximumAllowedDistanceFromCenter = container.radius - movingBall.radius;
        double ballShiftAmount = calculate_distance_between(movingBall.nextPosition, container.position) - maximumAllowedDistanceFromCenter;
        movingBall.nextPosition = movingBall.nextPosition + ballShiftAmount * contactNormal;
        reflect_vector(movingBall.nextVelocity, contactNormal);
        movingBall.nextVelocity = movingBall.elasticity * movingBall.nextVelocity;
    }

    void resolve_collision_between_movable_balls(Ball& ball1, Ball& ball2)
    {
        Vector3D contactNormal = ball2.nextPosition - ball1.nextPosition;
        contactNormal.normalize();
        double maximumAllowedDistanceBetween = ball1.radius + ball2.radius;
        double totalShiftAmount = maximumAllowedDistanceBetween - calculate_distance_between(ball1.nextPosition, ball2.nextPosition);
        double mass1 = pow(ball1.radius, 3);
        double mass2 = pow(ball2.radius, 3);
        ball1.nextPosition = ball1.nextPosition - (mass2 * totalShiftAmount / (mass1 + mass2)) * contactNormal;
        ball2.nextPosition = ball2.nextPosition + (mass1 * totalShiftAmount / (mass1 + mass2)) * contactNormal;

        Vector3D relativeVelocity = ball1.nextVelocity - ball2.nextVelocity;
        double impulse = (1 + (ball1.elasticity + ball2.elasticity) / 2) * relativeVelocity.dot(contactNormal) / (1 / mass1 + 1 / mass2);
        ball1.nextVelocity = ball1.nextVelocity - impulse / mass1 * contactNormal;
        ball2.nextVelocity = ball2.nextVelocity + impulse / mass2 * contactNormal;
    }

    void resolve_collision_with_immovable_ball(Ball& movableBall, const Ball& immovableBall)
    {
        Vector3D contactNormal = immovableBall.position - movableBall.nextPosition;
        contactNormal.normalize();
        double maximumAllowedDistanceBetween = immovableBall.radius + movableBall.radius;
        double ballShiftAmount = calculate_distance_between(movableBall.nextPosition, immovableBall.position) - maximumAllowedDistanceBetween;
        movableBall.nextPosition = movableBall.nextPosition + ballShiftAmount * contactNormal;
        reflect_vector(movableBall.nextVelocity, contactNormal);
        movableBall.nextVelocity = movableBall.elasticity * movableBall.nextVelocity;
    }
}
