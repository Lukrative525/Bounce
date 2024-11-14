#ifndef LINK_H
#define LINK_H

#include "isaveableobject.hpp"

class Link: ISaveableObject
{
public:
    Link(int index1 = 0, int index2 = 1);
    QJsonObject write_to_json() const;
    void read_from_json(const QJsonObject& json);

    int index1;
    int index2;
};

#endif // LINK_H
