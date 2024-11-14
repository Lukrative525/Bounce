#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include "ball.hpp"

class Simulation: ISaveableObject
{
public:
    Simulation(int maxNumberBalls = 100);
    QJsonObject write_to_json() const override;
    void read_from_json(const QJsonObject& json) override;
    void add_ball(Ball newBall);
    void add_ball(double x = 0, double y = 0, double z = 0, double radius = 0.1);
    void set_container(double x = 0, double y = 0, double z = 0, double radius = 10);
    void set_gravity(double x = 0, double y = 0, double z = -9.81);
    void set_time_step(double timeStep);
    const std::vector<Ball>& readBallCollection() const;
    const Ball& readContainer() const;
    void update();

    int maxNumberBalls;

private:
    void resolve_collisions();
    void resolve_all_collisions_with_container();
    void resolve_all_collisions_between_balls();

    std::vector<Ball> ballCollection;
    Ball container;
    Vector3D gravity;
    double timeStep;
};

#endif // SIMULATION_HPP
