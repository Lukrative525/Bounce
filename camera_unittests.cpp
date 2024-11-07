#include "camera.hpp"
#include "extrema.hpp"
#include <gtest/gtest.h>
#include <QSize>

TEST(cameraCentering, givenWideWindowAndObjectExtrema_WhenCameraCentered_ExpectCameraMaintainsWindowAspectRatioAndFitsObjects)
{
    Camera camera;
    QSize frameSize{1600, 900};
    Extrema viewerExtents{0, 0, 10, 10};
    camera.center_camera(frameSize, viewerExtents);
    float width = camera.get_width();
    float height = camera.get_height();

    EXPECT_TRUE(width >= viewerExtents.maximumX - viewerExtents.minimumX);
    EXPECT_TRUE(height == viewerExtents.maximumY - viewerExtents.minimumY);
    EXPECT_NEAR(
        static_cast<double>(width) / static_cast<double>(height),
        static_cast<double>(frameSize.width()) / static_cast<double>(frameSize.height()),
        0.000001
    );
}

TEST(cameraCentering, givenTallWindowAndObjectExtrema_WhenCameraCentered_ExpectCameraMaintainsWindowAspectRatioAndFitsObjects)
{
    Camera camera;
    QSize frameSize{900, 1600};
    Extrema viewerExtents{0, 0, 10, 10};
    camera.center_camera(frameSize, viewerExtents);
    float width = camera.get_width();
    float height = camera.get_height();

    EXPECT_TRUE(width == viewerExtents.maximumX - viewerExtents.minimumX);
    EXPECT_TRUE(height >= viewerExtents.maximumY - viewerExtents.minimumY);
    EXPECT_NEAR(
        static_cast<double>(width) / static_cast<double>(height),
        static_cast<double>(frameSize.width()) / static_cast<double>(frameSize.height()),
        0.000001
    );
}
