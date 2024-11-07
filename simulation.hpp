#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include "ball.hpp"

class Simulation
{
public:
    Simulation(int maxNumberBalls = 100);
    void add_ball(double x = 0, double y = 0, double z = 0, double radius = 0.1);
    void set_container(double x = 0, double y = 0, double z = 0, double radius = 10);
    void set_gravity(Vector3D gravity);
    void set_time_step(double timeStep);
    void update();
    std::vector<Ball> ballCollection;
    Ball container;
    int maxNumberBalls;

private:
    void resolve_collisions();
    void resolve_all_collisions_with_container();
    void resolve_single_collision_with_container(Ball& ball);
    bool detect_single_collision_with_container(Ball& ball);
    double calculate_distance_to_container(Ball& ball);
    Vector3D gravity;
    double timeStep;
};

#endif // SIMULATION_HPP
