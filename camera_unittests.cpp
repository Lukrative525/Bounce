#include "camera.hpp"
#include <gtest/gtest.h>
#include <QSize>

TEST(cameraCentering, givenWideWindowAndObjectExtrema_WhenCameraCentered_ExpectCameraMaintainsWindowAspectRatioAndFitsObjects)
{
    Camera camera;
    QSize frameSize{1600, 900};
    double minimumX{0};
    double minimumY{0};
    double maximumX{10};
    double maximumY{10};
    camera.center_camera(frameSize, minimumX, minimumY, maximumX, maximumY);
    float width = camera.width;
    float height = camera.height;

    EXPECT_TRUE(width >= maximumX - minimumX);
    EXPECT_TRUE(height == maximumY - minimumY);
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
    double minimumX{0};
    double minimumY{0};
    double maximumX{10};
    double maximumY{10};
    camera.center_camera(frameSize, minimumX, minimumY, maximumX, maximumY);
    float width = camera.width;
    float height = camera.height;

    EXPECT_TRUE(width == maximumX - minimumX);
    EXPECT_TRUE(height >= maximumY - minimumY);
    EXPECT_NEAR(
        static_cast<double>(width) / static_cast<double>(height),
        static_cast<double>(frameSize.width()) / static_cast<double>(frameSize.height()),
        0.000001
    );
}
