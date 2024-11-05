#include "gtest/gtest.h"
#include "physicsfunctions.hpp"
#include "vector3d.hpp"

TEST(calculateFunctionChange, givenZeroVector_WhenFunctionChangeCalculated_ExpectZeroVector)
{
    Vector3D zeroVector{};

    Vector3D testVector = phys::calculate_function_change(0.1, zeroVector);

    EXPECT_TRUE(testVector[0] == 0);
    EXPECT_TRUE(testVector[1] == 0);
    EXPECT_TRUE(testVector[2] == 0);
}

TEST(calculateFunctionChange, givenNonZeroVector_WhenFunctionChangeCalculated_ExpectAppropriateChange)
{
    Vector3D changeVector{1, 1, 1};

    double timeStep{0.1};
    Vector3D testVector = phys::calculate_function_change(timeStep, changeVector);

    EXPECT_TRUE(testVector[0] == timeStep);
    EXPECT_TRUE(testVector[1] == timeStep);
    EXPECT_TRUE(testVector[2] == timeStep);
}
