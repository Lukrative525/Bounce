#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include "ball.hpp"
#include "link.hpp"

class Simulation: ISaveableObject
{
public:
    Simulation();
    QJsonObject write_to_json() const override;
    void read_from_json(const QJsonObject& json) override;
    void add_ball(Ball newBall);
    void remove_ball(Ball* ballToRemove);
    void add_link(Link newLink);
    void add_link(int index1, int index2);
    bool is_new_link_unique(int index1, int index2);
    void set_container(double, double, double, double radius);
    void set_gravity(double, double, double z);
    void set_max_number_balls(int newMaxNumberBalls);
    void reset();
    void update();

    std::vector<Ball> ballCollection;
    std::vector<Link> linkCollection;
    Ball container{0};
    Vector3D gravity{0};
    double timeStep;

private:
    void resolve_collisions();
    void resolve_all_collisions_with_container();
    void resolve_all_collisions_between_balls();
    void resolve_links();

    int maxNumberBalls;
};

#endif // SIMULATION_HPP
