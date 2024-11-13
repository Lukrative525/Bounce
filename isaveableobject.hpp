#ifndef ISAVEABLEOBJECT_HPP
#define ISAVEABLEOBJECT_HPP

#include <QJsonObject>

class ISaveableObject
{
public:
    virtual QJsonObject write_to_json() const = 0;
    virtual void read_from_json(const QJsonObject& json) = 0;
};

#endif // ISAVEABLEOBJECT_HPP
