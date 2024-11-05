#include <qdebug.h>
#include "camera.hpp"

Camera::Camera()
{
    set_camera_position();
    set_near_plane();
    set_far_plane();
    set_camera_target();
    set_camera_up_direction();
}

void Camera::set_width(float width)
{
    this->width = width;
}

void Camera::set_height(float height)
{
    this->height = height;
}

void Camera::set_near_plane(float nearPlane)
{
    this->nearPlane = nearPlane;
}

void Camera::set_far_plane(float farPlane)
{
    this->farPlane = farPlane;
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

void Camera::regenerate_projection_matrix()
{
    projectionMatrix = glm::ortho(
        -width / 2,
        width / 2,
        -height / 2,
        height / 2,
        nearPlane,
        farPlane
    );
}

void Camera::regenerate_view_matrix()
{
    viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUpDirection);
}

void Camera::center_camera(
    QSize frameSize,
    double minimumX,
    double minimumY,
    double maximumX,
    double maximumY
    )
{
    double frameAspectRatio{static_cast<double>(frameSize.width()) / static_cast<double>(frameSize.height())};
    double xSpan{maximumX - minimumX};
    double ySpan{maximumY - minimumY};
    double spanAspectRatio{xSpan / ySpan};

    if (spanAspectRatio >= frameAspectRatio)
    {
        width = xSpan;
        height = ySpan / frameAspectRatio;
    }
    else
    {
        height = ySpan;
        width = xSpan * frameAspectRatio;
    }
    cameraPosition.x = minimumX + xSpan / 2;
    cameraPosition.z = minimumY + ySpan / 2;
}

float Camera::get_width()
{
    return width;
}

float Camera::get_height()
{
    return height;
}

float Camera::get_near_plane()
{
    return nearPlane;
}

float Camera::get_far_plane()
{
    return farPlane;
}

glm::mat4 Camera::get_projection_matrix()
{
    return projectionMatrix;
}

glm::mat4 Camera::get_view_matrix()
{
    return viewMatrix;
}
