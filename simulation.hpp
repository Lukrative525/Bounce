#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include "ball.hpp"

class Simulation
{
public:
    Simulation(int maxNumberBalls = 100);
    void add_ball(double x = 0, double y = 0, double z = 0, double radius = 0.1);
    void set_gravity(Vector3D gravity);
    void set_time_step(float timeStep);
    void update();
    std::vector<Ball> ballCollection;
    int maxNumberBalls;

private:
    Vector3D gravity;
    float timeStep;
};

#endif // SIMULATION_HPP
