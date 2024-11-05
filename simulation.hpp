#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include "ball.hpp"

class Simulation
{
public:
    Simulation(int maxNumberBalls = 100);
    void add_ball(double x = 0, double y = 0, double z = 0, double radius = 0.1);
    int maxNumberBalls;
    std::vector<Ball> ballCollection;
};

#endif // SIMULATION_HPP
