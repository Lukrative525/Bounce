#ifndef BALL_HPP
#define BALL_HPP

#include <glm/glm.hpp>
#include "vector3d.hpp"

class Ball: public ISaveableObject
{
public:
    Ball(double = 0, double = 0, double = 0);
    QJsonObject write_to_json() const override;
    void read_from_json(const QJsonObject& json) override;
    void make_next_state_current();
    void set_color(float brightness, float opacity);
    void set_color(float R, float G, float B, float a);

    Vector3D position;
    Vector3D nextPosition;
    Vector3D velocity;
    Vector3D nextVelocity;
    double radius{1};
    double elasticity{1};
    glm::vec4 color{1.0, 1.0, 1.0, 1.0};
    bool isMovable{true};
};

#endif // BALL_HPP
