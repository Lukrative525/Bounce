#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <QSize>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_transform.hpp>

class Extrema;
class Vector3D;

class Camera
{
public:
    Camera();
    void set_width(float width);
    void set_height(float height);
    void set_near_plane(float distance = 0);
    void set_far_plane(float distance = 10);
    void set_camera_position(float x = 0, float y = 0, float z = 0);
    void set_camera_target(float dx = 0, float dy = 1, float dz = 0);
    void set_camera_target(Vector3D target);
    void set_camera_up_direction(float dx = 0, float dy = 0, float dz = 1);
    void regenerate_projection_matrix();
    void regenerate_view_matrix();
    void center_camera(const QSize& frameSize, const Extrema& viewerExtents);
    float get_width();
    float get_height();
    float get_near_plane();
    float get_far_plane();
    glm::mat4 get_projection_matrix();
    glm::mat4 get_view_matrix();

private:
    float width{0};
    float height{0};
    float nearPlane{0};
    float farPlane{0};
    glm::vec3 cameraPosition;
    glm::vec3 cameraTarget;
    glm::vec3 cameraUpDirection;
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
};

#endif // CAMERA_HPP
