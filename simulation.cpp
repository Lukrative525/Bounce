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

const std::vector<Ball>& Simulation::readBallCollection() const
{
    return ballCollection;
}

const Ball& Simulation::readContainer() const
{
    return container;
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
        if (phys::detect_single_collision_with_container(ball, container))
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
            if (phys::detect_single_collision_between_balls(ballCollection[outer], ballCollection[inner]))
            {
                phys::resolve_collision_between_moving_balls(ballCollection[outer], ballCollection[inner]);
            }
        }
    }
}
