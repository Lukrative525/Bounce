#include "gtest/gtest.h"
#include "vector3d.hpp"

TEST(defaultConstructor, givenInitializedWithoutParameters_WhenComponentsAccessed_ExpectAccessedComponentsEqualToZero)
{
    Vector3D testVector{};
    EXPECT_TRUE(testVector.get_x() == 0);
    EXPECT_TRUE(testVector.get_y() == 0);
    EXPECT_TRUE(testVector.get_z() == 0);
}

TEST(parameterizedConstructor, givenInitializedWithParameters_WhenComponentsAccessed_ExpectAccessedComponentsEqualToInputParameters)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    Vector3D testVector{xComponent, yComponent, zComponent};
    EXPECT_TRUE(testVector.get_x() == xComponent);
    EXPECT_TRUE(testVector.get_y() == yComponent);
    EXPECT_TRUE(testVector.get_z() == zComponent);
}

TEST(copyConstructor, givenInitializedByCopy_WhenComponentsAccessed_ExpectAccessedComponentsEqualToComponentsOfOriginal)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    Vector3D originalTestVector{xComponent, yComponent, zComponent};
    Vector3D copiedTestVector{originalTestVector};
    EXPECT_TRUE(copiedTestVector.get_x() == xComponent);
    EXPECT_TRUE(copiedTestVector.get_y() == yComponent);
    EXPECT_TRUE(copiedTestVector.get_z() == zComponent);
}

TEST(copyConstructor, givenVector_WhenAssigningNewVectorValuesOfVector_ExpectNewVectorToHaveSameComponents)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    Vector3D testVector1{xComponent, yComponent, zComponent};
    Vector3D testVector2 = testVector1;
    EXPECT_EQ(testVector1[0], testVector2[0]);
    EXPECT_EQ(testVector1[1], testVector2[1]);
    EXPECT_EQ(testVector1[2], testVector2[2]);
}

TEST(copyConstructor, givenVector_WhenAssigningNewVectorValuesOfVectorAndChangingValuesOfOriginal_ExpectVectorsToHaveDifferentComponents)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    Vector3D testVector1{xComponent, yComponent, zComponent};
    Vector3D testVector2 = testVector1;
    testVector1.set_x(testVector1[0] + 1);
    EXPECT_FALSE(testVector1[0] == testVector2[0]);
}

TEST(setters, givenInitializedWithoutParameters_WhenComponentsSet_ExpectAccessedComponentsEqualToSetValues)
{
    Vector3D testVector{};
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    testVector.set_x(xComponent);
    testVector.set_y(yComponent);
    testVector.set_z(zComponent);
    EXPECT_TRUE(testVector.get_x() == xComponent);
    EXPECT_TRUE(testVector.get_y() == yComponent);
    EXPECT_TRUE(testVector.get_z() == zComponent);
}

TEST(calculateMagnitudeSquaredClassMethod, givenVector_WhenMethodCalled_ExpectScalarEqualToSquareOfMagnitude)
{
    double xComponent{1};
    double yComponent{4};
    double zComponent{8};
    Vector3D testVector{xComponent, yComponent, zComponent};
    double magnitudeSquared = 9 * 9;
    EXPECT_DOUBLE_EQ(testVector.calculate_magnitude_squared(), magnitudeSquared);
}

TEST(calculateMagnitudeClassMethod, givenVector_WhenMethodCalled_ExpectScalarEqualToMagnitudeOfVector)
{
    double xComponent{1};
    double yComponent{4};
    double zComponent{8};
    Vector3D testVector{xComponent, yComponent, zComponent};
    double magnitude = 9;
    EXPECT_DOUBLE_EQ(testVector.calculate_magnitude(), magnitude);
}

TEST(normalizeVectorClassMethod, givenVectorWithNormNotEqualOne_WhenMethodCalled_ExpectNormNowEqualToOne)
{
    double xComponent{1};
    double yComponent{4};
    double zComponent{8};
    Vector3D testVector{xComponent, yComponent, zComponent};
    testVector.normalize();
    EXPECT_DOUBLE_EQ(testVector.calculate_magnitude(), 1);
}

TEST(subscriptOperator, givenInitializedWithParameters_WhenComponentsAccessedWithSubscriptOperator_ExpectComponentsEqualToInputParameters)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    Vector3D testVector{xComponent, yComponent, zComponent};
    EXPECT_TRUE(testVector[0] == xComponent);
    EXPECT_TRUE(testVector[1] == yComponent);
    EXPECT_TRUE(testVector[2] == zComponent);
}

TEST(subscriptOperator, givenVector_WhenModifyingComponentBySubscript_ExpectComponentValueUpdatedWithNewValue)
{
    Vector3D testVector;
    double changedValue{1};
    testVector[0] = changedValue;
    EXPECT_DOUBLE_EQ(testVector[0], changedValue);
}

TEST(assignmentOperator, givenTwoVectors_WhenSettingOneEqualToOther_ExpectComponentsToOccupyDifferentSpotsInMemory)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    Vector3D testVector1{xComponent, yComponent, zComponent};
    Vector3D testVector2;
    testVector2 = testVector1;
    EXPECT_TRUE(testVector1[0] == testVector2[0]);
    testVector1[0] = xComponent + 1;
    EXPECT_FALSE(testVector1[0] == testVector2[0]);
}

TEST(equalityComparisonOperator, givenTwoVectors_WhenVectorsAreCompared_ExpectTrueIfAllComponentsAreEqual)
{
    double xComponent{1};
    double yComponent{2};
    double zComponent{3};
    Vector3D testVector1{xComponent, yComponent, zComponent};
    Vector3D testVector2{xComponent, yComponent, zComponent};
    EXPECT_TRUE(testVector1 == testVector2);
}

TEST(equalityComparisonOperator, givenTwoVectors_WhenVectorsAreCompared_ExpectFalseIfNotAllComponentsAreEqual)
{
    double xComponent{1};
    double yComponent{2};
    double zComponent{3};
    Vector3D testVector1{xComponent, yComponent, zComponent};
    Vector3D testVector2{xComponent, yComponent, zComponent};
    testVector1[1] = testVector1[1] + 1;
    EXPECT_FALSE(testVector1 == testVector2);
}

TEST(inequalityComparisonOperator, givenTwoVectors_WhenVectorsAreCompared_ExpectFalseIfAllComponentsAreEqual)
{
    double xComponent{1};
    double yComponent{2};
    double zComponent{3};
    Vector3D testVector1{xComponent, yComponent, zComponent};
    Vector3D testVector2{xComponent, yComponent, zComponent};
    EXPECT_FALSE(testVector1 != testVector2);
}

TEST(additionOperator, givenTwoVectors_WhenAddedTogether_ExpectResultVectorWithComponentsEqualToSumOfRespectiveComponents)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    Vector3D testVector1{xComponent, yComponent, zComponent};
    Vector3D testVector2{xComponent, yComponent, zComponent};
    Vector3D testVector3 = testVector1 + testVector2;
    EXPECT_TRUE(testVector3[0] == 2 * xComponent);
    EXPECT_TRUE(testVector3[1] == 2 * yComponent);
    EXPECT_TRUE(testVector3[2] == 2 * zComponent);
}

TEST(additionOperator, givenVectorAndDouble_WhenAddedTogether_ExpectResultVectorWithAllComponentsIncrementedByDouble)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    Vector3D testVector{xComponent, yComponent, zComponent};
    double valueToAdd{1};
    Vector3D testVector2 = testVector + valueToAdd;
    EXPECT_TRUE(testVector2[0] == xComponent + valueToAdd);
    EXPECT_TRUE(testVector2[1] == yComponent + valueToAdd);
    EXPECT_TRUE(testVector2[2] == zComponent + valueToAdd);
}

TEST(additionOperator, givenDoubleAndVector_WhenAddedTogether_ExpectResultVectorWithAllComponentsIncrementedByDouble)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    Vector3D testVector{xComponent, yComponent, zComponent};
    double valueToAdd{1};
    Vector3D testVector2 = valueToAdd + testVector;
    EXPECT_TRUE(testVector2[0] == xComponent + valueToAdd);
    EXPECT_TRUE(testVector2[1] == yComponent + valueToAdd);
    EXPECT_TRUE(testVector2[2] == zComponent + valueToAdd);
}

TEST(subtractionOperator, givenTwoVectors_WhenSubtracted_ExpectResultVectorWithComponentsEqualToDifferenceOfRespectiveComponents)
{
    double xComponent1{1.5};
    double yComponent1{5};
    double zComponent1{99999};
    double xComponent2{3};
    double yComponent2{3.14159};
    double zComponent2{111};
    Vector3D testVector1{xComponent1, yComponent1, zComponent1};
    Vector3D testVector2{xComponent2, yComponent2, zComponent2};
    Vector3D testVector3 = testVector1 - testVector2;
    EXPECT_TRUE(testVector3[0] == xComponent1 - xComponent2);
    EXPECT_TRUE(testVector3[1] == yComponent1 - yComponent2);
    EXPECT_TRUE(testVector3[2] == zComponent1 - zComponent2);
}

TEST(subtractionOperator, givenVectorAndDouble_WhenSubtracted_ExpectResultVectorWithComponentsEqualToDifferenceOfComponentsAndDouble)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    double valueToSubtract{5};
    Vector3D testVector1{xComponent, yComponent, zComponent};
    Vector3D testVector2 = testVector1 - valueToSubtract;
    EXPECT_TRUE(testVector2[0] == xComponent - valueToSubtract);
    EXPECT_TRUE(testVector2[1] == yComponent - valueToSubtract);
    EXPECT_TRUE(testVector2[2] == zComponent - valueToSubtract);
}

TEST(subtractionOperator, givenDoubleAndVector_WhenSubtracted_ExpectResultVectorWithComponentsEqualToDifferenceOfDoubleAndComponents)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    double valueToSubtract{5};
    Vector3D testVector1{xComponent, yComponent, zComponent};
    Vector3D testVector2 = valueToSubtract - testVector1;
    EXPECT_TRUE(testVector2[0] == valueToSubtract - xComponent);
    EXPECT_TRUE(testVector2[1] == valueToSubtract - yComponent);
    EXPECT_TRUE(testVector2[2] == valueToSubtract - zComponent);
}

TEST(multiplicationOperator, givenVectorAndDouble_WhenMultiplied_ExpectResultVectorWithComponentsEqualToRespectiveComponentsTimesDouble)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    double factor{5};
    Vector3D testVector1{xComponent, yComponent, zComponent};
    Vector3D testVector2 = testVector1 * factor;
    EXPECT_TRUE(testVector2[0] == xComponent * factor);
    EXPECT_TRUE(testVector2[1] == yComponent * factor);
    EXPECT_TRUE(testVector2[2] == zComponent * factor);
}

TEST(multiplicationOperator, givenDoubleAndVector_WhenMultiplied_ExpectResultVectorWithComponentsEqualToDoubleTimesRespectiveComponents)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    double factor{5};
    Vector3D testVector1{xComponent, yComponent, zComponent};
    Vector3D testVector2 = factor * testVector1;
    EXPECT_TRUE(testVector2[0] == factor * xComponent);
    EXPECT_TRUE(testVector2[1] == factor * yComponent);
    EXPECT_TRUE(testVector2[2] == factor * zComponent);
}

TEST(divisionOperator, givenVectorAndDouble_WhenDivided_ExpectResultVectorWithComponentsEqualToRespectiveComponentsDividedByDouble)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    double denominator{5};
    Vector3D testVector1{xComponent, yComponent, zComponent};
    Vector3D testVector2 = testVector1 / denominator;
    EXPECT_TRUE(testVector2[0] == xComponent / denominator);
    EXPECT_TRUE(testVector2[1] == yComponent / denominator);
    EXPECT_TRUE(testVector2[2] == zComponent / denominator);
}

TEST(divisionOperator, givenDoubleAndVector_WhenDivided_ExpectResultVectorWithComponentsEqualToDoubleDividedByRespectiveComponents)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    double numerator{5};
    Vector3D testVector1{xComponent, yComponent, zComponent};
    Vector3D testVector2 = numerator / testVector1;
    EXPECT_TRUE(testVector2[0] == numerator / xComponent);
    EXPECT_TRUE(testVector2[1] == numerator / yComponent);
    EXPECT_TRUE(testVector2[2] == numerator / zComponent);
}

TEST(divisionOperator, givenVector_WhenDividedByZero_ExpectThrowDomainErrorException)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{99999};
    Vector3D testVector{xComponent, yComponent, zComponent};
    EXPECT_THROW(testVector / 0, std::domain_error);
}

TEST(divisionOperator, givenVectorWithAtLeastOneComponentEqualToZero_WhenDoubleDividedByVector_ExpectThrowDomainErrorException)
{
    double xComponent{1.5};
    double yComponent{5};
    double zComponent{0};
    Vector3D testVector{xComponent, yComponent, zComponent};
    EXPECT_THROW(1 / testVector, std::domain_error);
}

TEST(dotProduct, givenTwoVectors_WhenDottedTogether_ExpectOutputDoubleOfCorrectValue)
{
    double xComponent1{1};
    double yComponent1{2};
    double zComponent1{3};
    double xComponent2{12};
    double yComponent2{6};
    double zComponent2{4};
    Vector3D testVector1{xComponent1, yComponent1, zComponent1};
    Vector3D testVector2{xComponent2, yComponent2, zComponent2};
    EXPECT_TRUE(testVector1.dot(testVector2) == 36);
}

TEST(crossProduct, givenTwoVectors_WhencrossedTogether_ExpectOutputVectorWithCorrectValues)
{
    double xComponent1{1};
    double yComponent1{2};
    double zComponent1{3};
    double xComponent2{12};
    double yComponent2{6};
    double zComponent2{4};
    Vector3D goldVector{-10, 32, -18};
    Vector3D testVector1{xComponent1, yComponent1, zComponent1};
    Vector3D testVector2{xComponent2, yComponent2, zComponent2};
    EXPECT_TRUE(testVector1.cross(testVector2) == goldVector);
}
