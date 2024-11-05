#include "gtest/gtest.h"
#include "ball.hpp"
#include "physicsfunctions.hpp"
#include "vector3d.hpp"

TEST(updateNextImplicitEuler, givenBallAtRestUnderAcceleration_WhenNextUpdated_ExpectAppropriateNextPositionAndVelocity)
{
    Vector3D acceleration{1, 1, 1};
    Ball ball{};
    double timeStep{0.1};

    phys::update_next_implicit_euler(timeStep, ball, acceleration);

    EXPECT_TRUE(ball.nextVelocity[0] == timeStep);
    EXPECT_TRUE(ball.nextVelocity[1] == timeStep);
    EXPECT_TRUE(ball.nextVelocity[2] == timeStep);
    EXPECT_TRUE(ball.nextPosition[0] == timeStep * timeStep);
    EXPECT_TRUE(ball.nextPosition[1] == timeStep * timeStep);
    EXPECT_TRUE(ball.nextPosition[2] == timeStep * timeStep);
}
