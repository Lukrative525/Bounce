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

TEST(ballConfirmNext, givenBallAtRestUnderAcceleration_WhenNextUpdatedAndConfirmed_ExpectAppropriatePositionAndVelocity)
{
    Vector3D acceleration{1, 1, 1};
    Ball ball{};
    double timeStep{0.1};

    phys::update_next_implicit_euler(timeStep, ball, acceleration);
    ball.confirmNext();

    EXPECT_TRUE(ball.velocity[0] == timeStep);
    EXPECT_TRUE(ball.velocity[1] == timeStep);
    EXPECT_TRUE(ball.velocity[2] == timeStep);
    EXPECT_TRUE(ball.position[0] == timeStep * timeStep);
    EXPECT_TRUE(ball.position[1] == timeStep * timeStep);
    EXPECT_TRUE(ball.position[2] == timeStep * timeStep);
}

TEST(reflectVector, givenAVectorAndNormal_WhenVectorFlipped_ExpectCorrectResult)
{
    Vector3D vector{4, 3, 0};
    Vector3D normal{1, 1, 0};

    phys::reflect_vector(vector, normal);

    EXPECT_NEAR(vector[0], -3, 0.000000001);
    EXPECT_NEAR(vector[1], -4, 0.000000001);
}

TEST(calculateDistanceBetween, givenTwoVectors_WhenDistanceBetweenCalculated_ExpectCorrectResult)
{
    Vector3D point1{-1, 1, 0};
    Vector3D point2{3, 4, 0};
    double distance = phys::distance_between(point1, point2);

    EXPECT_EQ(distance, 5);
}
