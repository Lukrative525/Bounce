#include <cmath>
#include <stdexcept>
#include "vector3d.hpp"

Vector3D::Vector3D(const double newX, const double newY, const double newZ):
    components{newX, newY, newZ} {}

Vector3D::Vector3D(const Vector3D& vectorToCopy):
    components{vectorToCopy[0], vectorToCopy[1], vectorToCopy[2]} {}

double Vector3D::get_x() const
{
    return components[0];
}

double Vector3D::get_y() const
{
    return components[1];
}

double Vector3D::get_z() const
{
    return components[2];
}

void Vector3D::set_x(double newX)
{
    components[0] = newX;
}

void Vector3D::set_y(double newY)
{
    components[1] = newY;
}

void Vector3D::set_z(double newZ)
{
    components[2] = newZ;
}

double Vector3D::calculate_magnitude_squared() const
{
    double magnitudeSquared = pow(components[0], 2) + pow(components[1], 2) + pow(components[2], 2);

    return magnitudeSquared;
}

double Vector3D::calculate_magnitude() const
{
    double magnitude = sqrt(calculate_magnitude_squared());

    return magnitude;
}

void Vector3D::normalize()
{
    double magnitude = calculate_magnitude();
    components[0] /= magnitude;
    components[1] /= magnitude;
    components[2] /= magnitude;
}

double Vector3D::dot(const Vector3D& secondVector) const
{
    double xProduct{components[0] * secondVector[0]};
    double yProduct{components[1] * secondVector[1]};
    double zProduct{components[2] * secondVector[2]};
    double dotProduct{xProduct + yProduct + zProduct};

    return dotProduct;
}

Vector3D Vector3D::cross(const Vector3D& secondVector) const
{
    Vector3D crossProduct;
    double xComponent{components[1] * secondVector[2] - components[2] * secondVector[1]};
    double yComponent{components[2] * secondVector[0] - components[0] * secondVector[2]};
    double zComponent{components[0] * secondVector[1] - components[1] * secondVector[0]};
    crossProduct[0] = xComponent;
    crossProduct[1] = yComponent;
    crossProduct[2] = zComponent;

    return crossProduct;
}

bool Vector3D::operator==(const Vector3D& secondVector) const
{
    if (components[0] == secondVector[0] && components[1] == secondVector[1] && components[2] == secondVector[2])
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Vector3D::operator!=(const Vector3D& secondVector) const
{
    return !(*this == secondVector);
}

double& Vector3D::operator[](const int index)
{
    return components[index];
}

double Vector3D::operator[](const int index) const
{
    return components[index];
}

/*
   #     ######   ######
  # #    #     #  #     #
 #   #   #     #  #     #
#######  #     #  #     #
#     #  #     #  #     #
#     #  #     #  #     #
#     #  ######   ######
*/

Vector3D operator+(const Vector3D& firstVectorToAdd, const Vector3D& secondVectorToAdd)
{
    double newX = firstVectorToAdd[0] + secondVectorToAdd[0];
    double newY = firstVectorToAdd[1] + secondVectorToAdd[1];
    double newZ = firstVectorToAdd[2] + secondVectorToAdd[2];
    Vector3D newVector{newX, newY, newZ};

    return newVector;
}

Vector3D operator+(const Vector3D& vectorToAdd, const double scalar)
{
    double newX = vectorToAdd[0] + scalar;
    double newY = vectorToAdd[1] + scalar;
    double newZ = vectorToAdd[2] + scalar;
    Vector3D newVector{newX, newY, newZ};

    return newVector;
}

Vector3D operator+(const double scalar, const Vector3D& vectorToAdd)
{
    double newX = scalar + vectorToAdd[0];
    double newY = scalar + vectorToAdd[1];
    double newZ = scalar + vectorToAdd[2];
    Vector3D newVector{newX, newY, newZ};

    return newVector;
}

/*
 #####   #     #  ######   #######  ######      #      #####   #######
#     #  #     #  #     #     #     #     #    # #    #     #     #
#        #     #  #     #     #     #     #   #   #   #           #
 #####   #     #  ######      #     ######   #######  #           #
      #  #     #  #     #     #     #   #    #     #  #           #
#     #  #     #  #     #     #     #    #   #     #  #     #     #
 #####    #####   ######      #     #     #  #     #   #####      #
*/

Vector3D operator-(const Vector3D& firstVectorToSubtract, const Vector3D& secondVectorToSubtract)
{
    double newX = firstVectorToSubtract[0] - secondVectorToSubtract[0];
    double newY = firstVectorToSubtract[1] - secondVectorToSubtract[1];
    double newZ = firstVectorToSubtract[2] - secondVectorToSubtract[2];
    Vector3D newVector{newX, newY, newZ};

    return newVector;
}

Vector3D operator-(const Vector3D& vectorToSubtract, const double scalar)
{
    double newX = vectorToSubtract[0] - scalar;
    double newY = vectorToSubtract[1] - scalar;
    double newZ = vectorToSubtract[2] - scalar;
    Vector3D newVector{newX, newY, newZ};

    return newVector;
}

Vector3D operator-(const double scalar, const Vector3D& vectorToSubtract)
{
    double newX = scalar - vectorToSubtract[0];
    double newY = scalar - vectorToSubtract[1];
    double newZ = scalar - vectorToSubtract[2];
    Vector3D newVector{newX, newY, newZ};

    return newVector;
}

/*
#     #  #     #  #        #######  #######  ######   #        #     #
##   ##  #     #  #           #        #     #     #  #         #   #
# # # #  #     #  #           #        #     #     #  #          # #
#  #  #  #     #  #           #        #     ######   #           #
#     #  #     #  #           #        #     #        #           #
#     #  #     #  #           #        #     #        #           #
#     #   #####   #######     #     #######  #        #######     #
*/

Vector3D operator*(const Vector3D& vectorToMultiply, const double factor)
{
    double newX = vectorToMultiply[0] * factor;
    double newY = vectorToMultiply[1] * factor;
    double newZ = vectorToMultiply[2] * factor;
    Vector3D newVector{newX, newY, newZ};

    return newVector;
}

Vector3D operator*(const double factor, const Vector3D& vectorToMultiply)
{
    double newX = factor * vectorToMultiply[0];
    double newY = factor * vectorToMultiply[1];
    double newZ = factor * vectorToMultiply[2];
    Vector3D newVector{newX, newY, newZ};

    return newVector;
}

/*
######   #######  #     #  #######  ######   #######
#     #     #     #     #     #     #     #  #
#     #     #     #     #     #     #     #  #
#     #     #     #     #     #     #     #  ####
#     #     #      #   #      #     #     #  #
#     #     #       # #       #     #     #  #
######   #######     #     #######  ######   #######
*/

Vector3D operator/(const Vector3D& vectorToDivide, const double denominator)
{
    if (denominator == 0)
    {
        throw std::domain_error("Division by zero");
    }
    double newX = vectorToDivide[0] / denominator;
    double newY = vectorToDivide[1] / denominator;
    double newZ = vectorToDivide[2] / denominator;
    Vector3D newVector{newX, newY, newZ};

    return newVector;
}

Vector3D operator/(const double numerator, const Vector3D& vectorToDivide)
{
    if (vectorToDivide[0] == 0 || vectorToDivide[1] == 0 || vectorToDivide[2] == 0)
    {
        throw std::domain_error("Division by zero");
    }
    double newX = numerator / vectorToDivide[0];
    double newY = numerator / vectorToDivide[1];
    double newZ = numerator / vectorToDivide[2];
    Vector3D newVector{newX, newY, newZ};

    return newVector;
}
