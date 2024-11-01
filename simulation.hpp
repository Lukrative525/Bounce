#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include "ball.hpp"

class Simulation
{
public:
    Simulation();
    Simulation(int maxNumberBalls);
    int maxNumberBalls;
    void add_ball();
    void add_ball(double x, double y, double z, double radius);
    std::vector<Ball> ballCollection;
};

#endif // SIMULATION_HPP
