#include "simulation.hpp"

Simulation::Simulation(): Simulation(100) {}

Simulation::Simulation(int maxNumberBalls):maxNumberBalls{maxNumberBalls}
{
    ballCollection.reserve(maxNumberBalls);
}

void Simulation::add_ball()
{
    add_ball(0, 0, 0, 0.1);
}

void Simulation::add_ball(double x, double y, double z, double radius)
{
    ballCollection.emplace_back(x, y, z, radius);
}
