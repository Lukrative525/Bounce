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

void Simulation::set_gravity(double x, double y, double z)
{
    this->gravity = Vector3D{x, y, z};
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
    Vector3D contactNormal = container.position - ball.nextPosition;
    contactNormal = contactNormal / contactNormal.calculate_magnitude();
    double maximumAllowedDistanceFromCenter = container.radius - ball.radius;
    double ballShiftAmount = phys::distance_between(ball.nextPosition, container.position) - maximumAllowedDistanceFromCenter;
    ball.nextPosition = ball.nextPosition + ballShiftAmount * contactNormal;
    phys::reflect_vector(ball.nextVelocity, contactNormal);
    ball.nextVelocity = ball.elasticity * ball.nextVelocity;
}

bool Simulation::detect_single_collision_with_container(Ball& ball)
{
    bool collisionDetected = phys::distance_between(ball.nextPosition, container.position) >= (container.radius - ball.radius);

    return collisionDetected;
}
