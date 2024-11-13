#include <QDebug>
#include <QJsonArray>
#include "physicsfunctions.hpp"
#include "simulation.hpp"

Simulation::Simulation(int maxNumberBalls):maxNumberBalls{maxNumberBalls}
{
    ballCollection.reserve(maxNumberBalls);
}

QJsonObject Simulation::write_to_json() const
{
    QJsonObject json;
    QJsonArray ballsArray;
    for (const Ball& ball: ballCollection)
    {
        ballsArray.append(ball.write_to_json());
    }
    json["ballCollection"] = ballsArray;
    json["container"] = container.write_to_json();
    json["maxNumberBalls"] = maxNumberBalls;
    json["gravity"] = gravity.write_to_json();
    json["timeStep"] = timeStep;
    return json;
}

void Simulation::read_from_json(const QJsonObject& json)
{
    QJsonArray ballCollectionArray = json["ballCollection"].toArray();
    for (const QJsonValue& jsonValue: ballCollectionArray)
    {
        QJsonObject ballJsonObject = jsonValue.toObject();
        Ball newBall;
        newBall.read_from_json(ballJsonObject);
        add_ball(newBall);
    }
    container.read_from_json(json["container"].toObject());
    maxNumberBalls = json["maxNumberBalls"].toDouble();
    gravity.read_from_json(json["gravity"].toObject());
    timeStep = json["timeStep"].toDouble();
}

void Simulation::add_ball(Ball newBall)
{
    if (ballCollection.size() < maxNumberBalls)
    {
        ballCollection.emplace_back(newBall);
    }
}

void Simulation::add_ball(double x, double y, double z, double radius)
{
    if (ballCollection.size() < maxNumberBalls)
    {
        ballCollection.emplace_back(x, y, z, radius);
    }
}

void Simulation::set_container(double x, double y, double z, double radius)
{
    container.position.x = x;
    container.position.y = y;
    container.position.z = z;
    container.radius = radius;
}

void Simulation::set_gravity(double x, double y, double z)
{
    this->gravity = Vector3D{x, y, z};
}

void Simulation::set_time_step(double timeStep)
{
    this->timeStep = timeStep;
}

void Simulation::update()
{
    for (int i{0}; i < ballCollection.size(); i++)
    {
        phys::update_next_implicit_euler(timeStep, ballCollection[i], gravity);
    }

    resolve_collisions();

    for (int i{0}; i < ballCollection.size(); i++)
    {
        ballCollection[i].make_next_state_current();
    }
}

void Simulation::resolve_collisions()
{
    resolve_all_collisions_with_container();
    resolve_all_collisions_between_balls();
}

void Simulation::resolve_all_collisions_with_container()
{
    for (Ball& ball: ballCollection)
    {
        if (detect_single_collision_with_container(ball))
        {
            phys::resolve_collision_between_moving_ball_and_container(ball, container);
        }
    }
}

void Simulation::resolve_all_collisions_between_balls()
{
    for (int outer{0}; outer < ballCollection.size(); outer++)
    {
        for (int inner{outer + 1}; inner < ballCollection.size(); inner++)
        {
            if (detect_single_collision_between_balls(ballCollection[outer], ballCollection[inner]))
            {
                phys::resolve_collision_between_moving_balls(ballCollection[outer], ballCollection[inner]);
            }
        }
    }
}

bool Simulation::detect_single_collision_with_container(Ball& ball)
{
    bool collisionDetected = phys::calculate_distance_between(ball.nextPosition, container.position) > (container.radius - ball.radius);

    return collisionDetected;
}

bool Simulation::detect_single_collision_between_balls(Ball& ball1, Ball& ball2)
{
    bool collisionDetected = phys::calculate_distance_between(ball1.nextPosition, ball2.nextPosition) < (ball1.radius + ball2.radius);

    return collisionDetected;
}
