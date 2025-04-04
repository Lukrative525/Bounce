#include "ball.hpp"
#include "jsonreadwritefunctions.hpp"

Ball::Ball(double x, double y, double z):
    position{x, y, z},
    nextPosition{x, y, z}
{
}

QJsonObject Ball::write_to_json() const
{
    QJsonObject json;
    json["position"] = position.write_to_json();
    json["nextPosition"] = nextPosition.write_to_json();
    json["velocity"] = velocity.write_to_json();
    json["nextVelocity"] = nextVelocity.write_to_json();
    json["radius"] = radius;
    json["elasticity"] = elasticity;
    json["color"] = jsonrw::write_to_json(color);
    json["isMovable"] = isMovable;
    return json;
}

void Ball::read_from_json(const QJsonObject& json)
{
    position.read_from_json(json["position"].toObject());
    nextPosition.read_from_json(json["nextPosition"].toObject());
    velocity.read_from_json(json["velocity"].toObject());
    nextVelocity.read_from_json(json["nextVelocity"].toObject());
    radius = json["radius"].toDouble();
    elasticity = json["elasticity"].toDouble();
    jsonrw::read_from_json(json["color"].toObject(), color);
    isMovable = json["isMovable"].toBool();
}

void Ball::make_next_state_current()
{
    position = nextPosition;
    velocity = nextVelocity;
}
