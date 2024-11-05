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

void Simulation::set_gravity(Vector3D gravity)
{
    this->gravity = gravity;
}

void Simulation::set_time_step(float timeStep)
{
    this->timeStep = timeStep;
}

void Simulation::update()
{
    for (int i{0}; i < ballCollection.size(); i++)
    {
        phys::update_next_implicit_euler(timeStep, ballCollection[i], gravity);
    }

    // check for collisions

    for (int i{0}; i < ballCollection.size(); i++)
    {
        ballCollection[i].confirmNext();
    }
}
