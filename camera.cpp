#include "camera.hpp"

Camera::Camera()
{
    recalculate_aspect_ratio();
}

void Camera::recalculate_aspect_ratio()
{
    aspectRatio = width / height;
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
    const QSize& frameSize,
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
    cameraPosition.y = minimumY + ySpan / 2;
}
