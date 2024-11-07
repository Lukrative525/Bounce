#include <QDebug>
#include "physicsfunctions.hpp"
#include "simulation.hpp"

Simulation::Simulation(int maxNumberBalls):maxNumberBalls{maxNumberBalls}
{
    ballCollection.reserve(maxNumberBalls);
}

void Simulation::add_ball(double x, double y, double z, double radius)
{
    if (ballCollection.size() < maxNumberBalls)
    {
        ballCollection.emplace_back(x, y, z, radius);
    }
}

void Simulation::set_container(double x, double y, double z, double radius)
{
    container.position[0] = x;
    container.position[1] = y;
    container.position[2] = z;
    container.radius = radius;
}

void Simulation::set_gravity(Vector3D gravity)
{
    this->gravity = gravity;
}

void Simulation::set_time_step(double timeStep)
{
    this->timeStep = timeStep;
}

void Simulation::update()
{
    for (int i{0}; i < ballCollection.size(); i++)
    {
        phys::update_next_implicit_euler(timeStep, ballCollection[i], gravity);
    }

    resolve_collisions();

    for (int i{0}; i < ballCollection.size(); i++)
    {
        ballCollection[i].confirmNext();
    }
}

void Simulation::resolve_collisions()
{
    resolve_all_collisions_with_container();
}

void Simulation::resolve_all_collisions_with_container()
{
    for (int i{0}; i < ballCollection.size(); i++)
    {
        if (detect_single_collision_with_container(ballCollection[i]))
        {
            resolve_single_collision_with_container(ballCollection[i]);
        }
    }
}

void Simulation::resolve_single_collision_with_container(Ball& ball)
{
    double initialDistance = phys::distance_between(ball.position, container.position);
    double finalDistance = phys::distance_between(ball.nextPosition, container.position);
    double traversalRatio = ((container.radius - ball.radius) - initialDistance) / (finalDistance - initialDistance);
    Vector3D positionDelta = ball.nextPosition - ball.position;
    ball.position = ball.position + traversalRatio * positionDelta;
    positionDelta = ball.nextPosition - ball.position;
    Vector3D normal = container.position - ball.position;
    phys::reflect_vector(positionDelta, normal);
    ball.nextPosition = ball.position + positionDelta;
    phys::reflect_vector(ball.nextVelocity, normal);

    // Vector3D normal = container.position - ball.nextPosition;
    // normal = normal / normal.calculate_magnitude();
    // ball.nextPosition = ball.nextPosition + normal * (container.radius - ball.radius) / phys::distance_between(ball.nextPosition, container.position);
    // phys::reflect_vector(ball.nextVelocity, normal);
}

bool Simulation::detect_single_collision_with_container(Ball& ball)
{
    bool collisionDetected = phys::distance_between(ball.nextPosition, container.position) >= (container.radius - ball.radius);

    return collisionDetected;
}

double Simulation::calculate_distance_to_container(Ball& ball)
{
    return 0;
}
