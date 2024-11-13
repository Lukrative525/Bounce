#include "jsonreadwritefunctions.hpp"

namespace jsonrw
{
    QJsonObject write_to_json(const glm::vec2& vec2) {
        QJsonObject json;
        json["x"] = vec2.x;
        json["y"] = vec2.y;
        return json;
    }

    QJsonObject write_to_json(const glm::vec3& vec3) {
        QJsonObject json;
        json["x"] = vec3.x;
        json["y"] = vec3.y;
        json["z"] = vec3.z;
        return json;
    }

    QJsonObject write_to_json(const glm::vec4& vec4) {
        QJsonObject json;
        json["x"] = vec4.x;
        json["y"] = vec4.y;
        json["z"] = vec4.z;
        json["w"] = vec4.w;
        return json;
    }

    void read_from_json(const QJsonObject& json, glm::vec2& vec2) {
        vec2.x = json["x"].toDouble();
        vec2.y = json["y"].toDouble();
    }

    void read_from_json(const QJsonObject& json, glm::vec3& vec3) {
        vec3.x = json["x"].toDouble();
        vec3.y = json["y"].toDouble();
        vec3.z = json["z"].toDouble();
    }

    void read_from_json(const QJsonObject& json, glm::vec4& vec4) {
        vec4.x = json["x"].toDouble();
        vec4.y = json["y"].toDouble();
        vec4.z = json["z"].toDouble();
        vec4.w = json["w"].toDouble();
    }
}
