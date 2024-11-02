#include <glm/gtc/matrix_transform.hpp>
#include "camera.hpp"

Camera::Camera()
{
    recalculate_aspect_ratio();
}

void Camera::recalculate_aspect_ratio()
{
    aspectRatio = width / height;
}

void Camera::set_width(float newWidth)
{
    width = newWidth;
}

void Camera::set_height(float newHeight)
{
    height = newHeight;
}

void Camera::set_near_plane(float newNearPlane)
{
    nearPlane = newNearPlane;
}

void Camera::set_far_plane(float newFarPlane)
{
    farPlane = newFarPlane;
}

void Camera::build_projection_matrix()
{
    projectionMatrix = glm::ortho
    (
        -width / 2,
        width / 2,
        -height / 2,
        height / 2,
        nearPlane,
        farPlane
    );
}

glm::mat4 Camera::get_projection_matrix()
{
    return projectionMatrix;
}

void Camera::set_camera_position(float x, float y, float z)
{
    cameraPosition[0] = x;
    cameraPosition[1] = y;
    cameraPosition[2] = z;
}

void Camera::set_camera_target(float dx, float dy, float dz)
{
    cameraTarget[0] = cameraPosition[0] + dx;
    cameraTarget[1] = cameraPosition[1] + dy;
    cameraTarget[2] = cameraPosition[2] + dz;
}

void Camera::set_camera_up_direction(float dx, float dy, float dz)
{
    cameraUpDirection[0] = dx;
    cameraUpDirection[1] = dy;
    cameraUpDirection[2] = dz;
}

void Camera::build_view_matrix()
{
    viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUpDirection);
}

glm::mat4 Camera::get_view_matrix()
{
    return viewMatrix;
}
