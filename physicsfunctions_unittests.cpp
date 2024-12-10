#include "gtest/gtest.h"
#include "ball.hpp"
#include "physicsfunctions.hpp"
#include "vector3d.hpp"

class UpdateNextImplicitEuler : public ::testing::Test
{
protected:
    Vector3D acceleration{1, 1, 1};
    Ball ball{0};
    double timeStep{0.1};

    void SetUp() override
    {
        phys::update_next_state_implicit_euler(timeStep, ball, acceleration);
    }
};

TEST_F(UpdateNextImplicitEuler, givenBallAtRestUnderAcceleration_WhenNextStateUpdated_ExpectAppropriateNextPositionAndVelocity)
{
    EXPECT_TRUE(ball.nextVelocity.x == timeStep);
    EXPECT_TRUE(ball.nextVelocity.y == timeStep);
    EXPECT_TRUE(ball.nextVelocity.z == timeStep);
    EXPECT_TRUE(ball.nextPosition.x == timeStep * timeStep);
    EXPECT_TRUE(ball.nextPosition.y == timeStep * timeStep);
    EXPECT_TRUE(ball.nextPosition.z == timeStep * timeStep);
}

TEST_F(UpdateNextImplicitEuler, givenBallAtRestUnderAcceleration_WhenNextStateUpdatedAndConfirmed_ExpectAppropriatePositionAndVelocity)
{
    ball.make_next_state_current();

    EXPECT_TRUE(ball.velocity.x == timeStep);
    EXPECT_TRUE(ball.velocity.y == timeStep);
    EXPECT_TRUE(ball.velocity.z == timeStep);
    EXPECT_TRUE(ball.position.x == timeStep * timeStep);
    EXPECT_TRUE(ball.position.y == timeStep * timeStep);
    EXPECT_TRUE(ball.position.z == timeStep * timeStep);
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

class DetectCollisionWithContainer : public ::testing::Test
{
protected:
    Ball movingBall{0};
    Ball container{0};

    void SetUp() override
    {
        movingBall.radius = 1;
        container.radius = 2;
    }
};

TEST_F(DetectCollisionWithContainer, givenNonOverlapping_WhenFunctionCalled_ExpectFalse)
{
    bool collisionDetected = phys::detect_collision_with_container(movingBall, container);

    EXPECT_FALSE(collisionDetected);
}

TEST_F(DetectCollisionWithContainer, givenOverlapping_WhenFunctionCalled_ExpectTrue)
{
    movingBall.nextPosition.x = 1.75;

    bool collisionDetected = phys::detect_collision_with_container(movingBall, container);

    EXPECT_TRUE(collisionDetected);
}

class CollisionsBetweenBallAndContainer : public ::testing::Test
{
protected:
    Ball movingBall{0};
    Ball container{0};
    double distanceToImpact;

    void SetUp() override
    {
        movingBall.radius = 1;
        container.radius = 5;

        distanceToImpact = 4;

        movingBall.nextPosition[0] = distanceToImpact + 1;
    }
};

TEST_F(CollisionsBetweenBallAndContainer, givenSuchCollision_WhenResolveFunctionCalled_ExpectCorrectFinalPosition)
{
    phys::resolve_collision_with_container(movingBall, container);

    EXPECT_TRUE(movingBall.nextPosition[0] == distanceToImpact);
}

TEST_F(CollisionsBetweenBallAndContainer, givenSuchCollision_WhenResolveFunctionCalled_ExpectVelocityFlipped)
{
    double velocity{5};
    movingBall.nextVelocity[0] = velocity;

    phys::resolve_collision_with_container(movingBall, container);

    EXPECT_TRUE(movingBall.nextVelocity[0] == -velocity);
}
