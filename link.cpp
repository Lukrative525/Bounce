#include "link.hpp"

Link::Link(int index1, int index2):
    index1{index1},
    index2{index2}
{
}

QJsonObject Link::write_to_json() const
{
    QJsonObject json;
    json["index1"] = index1;
    json["index2"] = index2;
    return json;
}

void Link::read_from_json(const QJsonObject& json)
{
    index1 = json["index1"].toInt();
    index2 = json["index2"].toInt();
}
