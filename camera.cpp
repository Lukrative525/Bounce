#include <qdebug.h>
#include "camera.hpp"
#include "extrema.hpp"
#include "vector3d.hpp"

Camera::Camera() {}

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
    cameraPosition.x = x;
    cameraPosition.y = y;
    cameraPosition.z = z;
}

void Camera::set_camera_target(Vector3D target)
{
    cameraTarget.x = target[0];
    cameraTarget.y = target[1];
    cameraTarget.z = target[2];
}

void Camera::set_camera_up_direction(float dx, float dy, float dz)
{
    cameraUpDirection.x = dx;
    cameraUpDirection.y = dy;
    cameraUpDirection.z = dz;
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

void Camera::center_camera(const QSize& frameSize, const Extrema& viewerExtents)
{
    double frameAspectRatio{static_cast<double>(frameSize.width()) / static_cast<double>(frameSize.height())};
    double screenXSpan{viewerExtents.maximumX - viewerExtents.minimumX};
    double screenYSpan{viewerExtents.maximumY - viewerExtents.minimumY};
    double spanAspectRatio{screenXSpan / screenYSpan};

    if (spanAspectRatio >= frameAspectRatio)
    {
        width = screenXSpan;
        height = screenYSpan / frameAspectRatio;
    }
    else
    {
        height = screenYSpan;
        width = screenXSpan * frameAspectRatio;
    }
    cameraPosition.x = viewerExtents.minimumX + screenXSpan / 2;
    cameraPosition.z = viewerExtents.minimumY + screenYSpan / 2;
}

float Camera::get_width()
{
    return width;
}

float Camera::get_height()
{
    return height;
}

glm::mat4 Camera::get_projection_matrix()
{
    return projectionMatrix;
}

glm::mat4 Camera::get_view_matrix()
{
    return viewMatrix;
}
