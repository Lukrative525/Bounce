#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include "ball.hpp"

class Simulation
{
public:
    Simulation(int maxNumberBalls = 100);
    void add_ball(Ball newBall);
    void add_ball(double x = 0, double y = 0, double z = 0, double radius = 0.1);
    void set_container(double x = 0, double y = 0, double z = 0, double radius = 10);
    void set_gravity(double x = 0, double y = 0, double z = -9.81);
    void set_time_step(double timeStep);
    void update();
    std::vector<Ball> ballCollection;
    Ball container;
    int maxNumberBalls;

private:
    void resolve_collisions();
    void resolve_all_collisions_with_container();
    void resolve_all_collisions_between_balls();
    bool detect_single_collision_with_container(Ball& ball);
    bool detect_single_collision_between_balls(Ball& ball1, Ball& ball2);
    Vector3D gravity;
    double timeStep;
};

#endif // SIMULATION_HPP
