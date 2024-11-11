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
    ball.confirm_next();

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
    double distance = phys::calculate_distance_between(point1, point2);

    EXPECT_EQ(distance, 5);
}

TEST(collisionsBetweenBallAndContainer, givenSuchCollision_WhenResolveFunctionCalled_ExpectCorrectFinalPosition)
{
    Ball movingBall;
    movingBall.position[0] = 0;
    movingBall.position[1] = 0;
    movingBall.position[2] = 0;
    movingBall.radius = 1;
    movingBall.nextPosition[0] = 0;
    movingBall.nextPosition[1] = 0;
    movingBall.nextPosition[2] = 0;
    Ball container;
    container.position[0] = 0;
    container.position[1] = 0;
    container.position[2] = 0;
    container.radius = 5;
    container.nextPosition[0] = 0;
    container.nextPosition[1] = 0;
    container.nextPosition[2] = 0;
    double distanceToImpact = container.radius - movingBall.radius;

    movingBall.nextPosition[0] = distanceToImpact + 1;

    phys::resolve_collision_between_moving_ball_and_container(movingBall, container);

    EXPECT_TRUE(movingBall.nextPosition[0] == distanceToImpact);
}

TEST(collisionsBetweenBallAndContainer, givenSuchCollision_WhenResolveFunctionCalled_ExpectVelocityFlipped)
{
    double velocity{5};
    Ball movingBall;
    movingBall.position[0] = 0;
    movingBall.position[1] = 0;
    movingBall.position[2] = 0;
    movingBall.radius = 1;
    movingBall.elasticity = 1;
    movingBall.nextPosition[0] = 0;
    movingBall.nextPosition[1] = 0;
    movingBall.nextPosition[2] = 0;
    movingBall.nextVelocity[0] = velocity;
    Ball container;
    container.position[0] = 0;
    container.position[1] = 0;
    container.position[2] = 0;
    container.radius = 5;
    container.elasticity = 1;
    container.nextPosition[0] = 0;
    container.nextPosition[1] = 0;
    container.nextPosition[2] = 0;
    double distanceToImpact = container.radius - movingBall.radius;

    movingBall.nextPosition[0] = distanceToImpact + 1;

    phys::resolve_collision_between_moving_ball_and_container(movingBall, container);

    EXPECT_TRUE(movingBall.nextVelocity[0] == -velocity);
}
