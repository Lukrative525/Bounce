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
    Ball& get_ball(int ballIndex);
    const std::vector<Ball>& get_ball_collection() const;
    void add_ball(Ball newBall);
    void remove_ball(Ball* ballToRemove);
    const std::vector<Link>& get_link_collection() const;
    void add_link(Link newLink);
    void add_link(Ball* ball1, Ball* ball2);
    void remove_links_on_ball(int ballIndex);
    void remove_links_on_ball(Ball* ball);
    bool is_new_link_unique(int index1, int index2);
    void set_max_number_balls(int newMaxNumberBalls);
    int get_max_number_links();
    void reset();
    void update();

    Ball container{0};
    Vector3D gravity{0};
    double timeStep;

private:
    void resolve_collisions();
    void resolve_all_collisions_with_container();
    void resolve_all_collisions_between_balls();
    void resolve_links();

    std::vector<Ball> ballCollection;
    std::vector<Link> linkCollection;
    std::vector<Ball>::iterator get_ball_iterator(Ball* ball);
    int get_ball_index(Ball* ball);
    int get_ball_index(std::vector<Ball>::iterator ballIterator);

    int maxNumberBalls;
};

#endif // SIMULATION_HPP
