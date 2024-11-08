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
    resolve_all_collisions_between_balls();
}

void Simulation::resolve_all_collisions_with_container()
{
    for (Ball& ball: ballCollection)
    {
        if (detect_single_collision_with_container(ball))
        {
            resolve_single_collision_with_container(ball);
        }
    }
}

void Simulation::resolve_all_collisions_between_balls()
{
    for (int outer{0}; outer < ballCollection.size(); outer++)
    {
        for (int inner{outer + 1}; inner < ballCollection.size(); inner++)
        {
            if (detect_single_collision_between_balls(ballCollection[outer], ballCollection[inner]))
            {
                resolve_single_collision_between_balls(ballCollection[outer], ballCollection[inner]);
            }
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

void Simulation::resolve_single_collision_between_balls(Ball& ball1, Ball& ball2)
{
    Vector3D contactNormal = ball2.nextPosition - ball1.nextPosition;
    contactNormal = contactNormal / contactNormal.calculate_magnitude();
    double maximumAllowedDistanceBetween = ball1.radius + ball2.radius;
    double totalShiftAmount = maximumAllowedDistanceBetween - phys::distance_between(ball1.nextPosition, ball2.nextPosition);
    // for now, move each away by half (later, make inversely proportional to radius^3)
    ball1.nextPosition = ball1.nextPosition - (totalShiftAmount / 2) * contactNormal;
    ball2.nextPosition = ball2.nextPosition + (totalShiftAmount / 2) * contactNormal;

    // this is the wrong way to determine velocity (doesn't conserve momentum)
    phys::reflect_vector(ball1.nextVelocity, contactNormal);
    phys::reflect_vector(ball2.nextVelocity, contactNormal);
    ball1.nextVelocity = ball1.elasticity * ball1.nextVelocity;
    ball2.nextVelocity = ball2.elasticity * ball2.nextVelocity;
}

bool Simulation::detect_single_collision_with_container(Ball& ball)
{
    bool collisionDetected = phys::distance_between(ball.nextPosition, container.position) > (container.radius - ball.radius);

    return collisionDetected;
}

bool Simulation::detect_single_collision_between_balls(Ball& ball1, Ball& ball2)
{
    bool collisionDetected = phys::distance_between(ball1.nextPosition, ball2.nextPosition) < (ball1.radius + ball2.radius);

    return collisionDetected;
}
