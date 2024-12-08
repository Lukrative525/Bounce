#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include "ball.hpp"
#include "link.hpp"

class Simulation: ISaveableObject
{
public:
    Simulation(int maxNumberBalls = 100);
    QJsonObject write_to_json() const override;
    void read_from_json(const QJsonObject& json) override;
    void add_ball(Ball newBall);
    void add_ball(double x = 0, double y = 0, double z = 0, double radius = 0.1);
    void add_link(Link newLink);
    void add_link(int index1, int index2);
    bool is_new_link_unique(int index1, int index2);
    void set_container(double x = 0, double y = 0, double z = 0, double radius = 10);
    void set_gravity(double x = 0, double y = 0, double z = -9.81);
    void set_time_step(double timeStep);
    std::vector<Ball> ballCollection;
    std::vector<Link> linkCollection;
    Ball container;
    void update();

    int maxNumberBalls;
    Vector3D gravity{0, 0, -9.81};
    double timeStep{1.0 / 600.0};

private:
    void resolve_collisions();
    void resolve_all_collisions_with_container();
    void resolve_all_collisions_between_balls();
    void resolve_links();
};

#endif // SIMULATION_HPP
