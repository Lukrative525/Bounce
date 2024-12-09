#ifndef PHYSICSFUNCTIONS_HPP
#define PHYSICSFUNCTIONS_HPP

class Vector3D;
class Ball;

namespace phys
{
void update_next_state_implicit_euler(const double& timeStep, Ball& ball, const Vector3D& acceleration);
void reflect_vector(Vector3D& vectorToFlip, const Vector3D &normal);
double calculate_distance_between(const Vector3D& point1, const Vector3D& point2);
bool detect_collision_with_container(const Ball& ball, const Ball& container);
bool detect_collision_between_balls(const Ball& ball1, const Ball& ball2);
void resolve_collision(Ball& ball1, Ball& ball2);
void resolve_link(Ball& ball1, Ball& ball2);
void resolve_collision_with_container(Ball& ball, const Ball& container);
void resolve_interaction_between_movable_balls(Ball& ball1, Ball& ball2, bool shiftProportionalToMass);
void resolve_collision_between_movable_balls(Ball& ball1, Ball& ball2);
void resolve_link_between_movable_balls(Ball& ball1, Ball& ball2);
void resolve_collision_with_immovable_ball(Ball& movableBall, const Ball& immovableBall);
}

#endif // PHYSICSFUNCTIONS_HPP
