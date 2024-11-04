#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <QSize>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_transform.hpp>

class Camera
{
public:
    Camera();
    Camera(float x, float y, float z);
    void recalculate_aspect_ratio();
    void set_camera_position(float x, float y, float z);
    void set_camera_target(float dx, float dy, float dz);
    void set_camera_up_direction(float dx, float dy, float dz);
    void regenerate_projection_matrix();
    void regenerate_view_matrix();
    void center_camera(
        const QSize& frameSize,
        double minimumX,
        double minimumY,
        double maximumX,
        double maximumY
        );

    float aspectRatio;
    float width;
    float height;
    float nearPlane;
    float farPlane;
    glm::vec3 cameraPosition;
    glm::vec3 cameraTarget;
    glm::vec3 cameraUpDirection;
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
};

#endif // CAMERA_HPP
