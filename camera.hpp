#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Camera
{
public:
    Camera();
    void recalculate_aspect_ratio();
    void set_width(float newWidth);
    void set_height(float newHeight);
    void set_near_plane(float newNearPlane);
    void set_far_plane(float newFarPlane);
    void build_projection_matrix();
    glm::mat4 get_projection_matrix();

    void set_camera_position(float x, float y, float z);
    void set_camera_target(float dx, float dy, float dz);
    void set_camera_up_direction(float dx, float dy, float dz);
    void build_view_matrix();
    glm::mat4 get_view_matrix();

private:
    float aspectRatio;
    float width;
    float height;
    float nearPlane;
    float farPlane;
    glm::mat4 projectionMatrix;

    glm::vec3 cameraPosition;
    glm::vec3 cameraTarget;
    glm::vec3 cameraUpDirection;
    glm::mat4 viewMatrix;
};

#endif // CAMERA_HPP
