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

class DetectCollisionBetweenBalls : public ::testing::Test
{
protected:
    Ball ball1{0};
    Ball ball2{0};

    void SetUp() override
    {
        ball1.radius = 1;
        ball2.radius = 1;
    }
};

TEST_F(DetectCollisionBetweenBalls, givenTwoNonOverlappingBalls_WhenCollisionChecked_ExpectFalse)
{
    ball1.nextPosition.x = 1.1;
    ball2.nextPosition.x = -1.1;

    bool collisionDetected = phys::detect_collision_between_balls(ball1, ball2);

    EXPECT_FALSE(collisionDetected);
}

TEST_F(DetectCollisionBetweenBalls, givenTwoOverlappingBalls_WhenCollisionChecked_ExpectTrue)
{
    ball1.nextPosition.x = 0.9;
    ball2.nextPosition.x = -0.9;

    bool collisionDetected = phys::detect_collision_between_balls(ball1, ball2);

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

class InteractionsBetweenMovableBalls : public ::testing::Test
{
protected:
    Ball ball1{0};
    Ball ball2{0};

    void SetUp() override
    {
        ball1.radius = 1;
        ball2.radius = 2;

        ball1.nextPosition.y = 0.5;
        ball2.nextPosition.y = -1.5;

        ball1.nextVelocity.y = -9;
        ball2.nextVelocity.y = 0;
    }
};

TEST_F(InteractionsBetweenMovableBalls, givenDifferentSizedOverlappingBalls_WhenInteractionResolvedWithShiftNotProportionalToMass_ExpectBallsShiftedEqualAmounts)
{
    phys::resolve_interaction_between_movable_balls(ball1, ball2, false);

    EXPECT_TRUE(ball1.nextPosition.y == 1.0);
    EXPECT_TRUE(ball2.nextPosition.y == -2.0);
}

TEST_F(InteractionsBetweenMovableBalls, givenDifferentSizedOverlappingBalls_WhenInteractionResolvedWithShiftProportionalToMass_ExpectBallsShiftedDependingOnRadius)
{
    phys::resolve_interaction_between_movable_balls(ball1, ball2, true);

    double ball1FinalPosition = 0.5 + 8.0 / 9.0;
    double ball2FinalPosition = -1.5 - 1.0 / 9.0;

    EXPECT_TRUE(ball1.nextPosition.y == ball1FinalPosition);
    EXPECT_TRUE(ball2.nextPosition.y == ball2FinalPosition);
}

TEST_F(InteractionsBetweenMovableBalls, givenDifferentSizedOverlappingBalls_WhenInteractionResolved_ExpectMomentumConserved)
{
    phys::resolve_interaction_between_movable_balls(ball1, ball2, true);

    EXPECT_TRUE(ball1.nextVelocity.y == 7.0);
    EXPECT_TRUE(ball2.nextVelocity.y == -2.0);
}
