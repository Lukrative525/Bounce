#ifndef JSONREADWRITEFUNCTIONS_HPP
#define JSONREADWRITEFUNCTIONS_HPP

#include <glm/glm.hpp>
#include <QJsonObject>

namespace jsonrw
{
QJsonObject write_to_json(const glm::vec2& vec2);
QJsonObject write_to_json(const glm::vec3& vec3);
QJsonObject write_to_json(const glm::vec4& vec4);
void read_from_json(const QJsonObject& json, glm::vec2& vec2);
void read_from_json(const QJsonObject& json, glm::vec3& vec3);
void read_from_json(const QJsonObject& json, glm::vec4& vec4);
}

#endif // JSONREADWRITEFUNCTIONS_HPP
