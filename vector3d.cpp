#include <cmath>
#include <stdexcept>
#include "vector3d.hpp"

Vector3D::Vector3D(const double newX, const double newY, const double newZ):
    x{newX},
    y{newY},
    z{newZ}
{
}

Vector3D::Vector3D(const Vector3D& vectorToCopy):
    x{vectorToCopy.x},
    y{vectorToCopy.y},
    z{vectorToCopy.z}
{
}

QJsonObject Vector3D::write_to_json() const
{
    QJsonObject json;
    json["x"] = x;
    json["y"] = y;
    json["z"] = z;
    return json;
}

void Vector3D::read_from_json(const QJsonObject& json)
{
    x = json["x"].toDouble();
    y = json["y"].toDouble();
    z = json["z"].toDouble();
}

double Vector3D::calculate_magnitude_squared() const
{
    double magnitudeSquared = pow(x, 2) + pow(y, 2) + pow(z, 2);

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
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

double Vector3D::dot(const Vector3D& secondVector) const
{
    double dotProduct{x * secondVector.x + y * secondVector.y + z * secondVector.z};

    return dotProduct;
}

Vector3D Vector3D::cross(const Vector3D& secondVector) const
{
    Vector3D crossProduct;
    crossProduct.x = y * secondVector.z - z * secondVector.y;
    crossProduct.y = z * secondVector.x - x * secondVector.z;
    crossProduct.z = x * secondVector.y - y * secondVector.x;

    return crossProduct;
}

Vector3D& Vector3D::operator=(const Vector3D& vectorToCopy)
{
    x = vectorToCopy.x;
    y = vectorToCopy.y;
    z = vectorToCopy.z;

    return *this;
}

bool Vector3D::operator==(const Vector3D& secondVector) const
{
    if (x == secondVector.x && y == secondVector.y && z == secondVector.z)
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
    switch (index)
    {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    default:
        throw std::out_of_range("subscript out of range");
    }
}

double Vector3D::operator[](const int index) const
{
    switch (index)
    {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    default:
        throw std::out_of_range("subscript out of range");
    }
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
    Vector3D newVector;
    newVector.x = firstVectorToAdd.x + secondVectorToAdd.x;
    newVector.y = firstVectorToAdd.y + secondVectorToAdd.y;
    newVector.z = firstVectorToAdd.z + secondVectorToAdd.z;

    return newVector;
}

Vector3D operator+(const Vector3D& vectorToAdd, const double scalar)
{
    Vector3D newVector;
    newVector.x = vectorToAdd.x + scalar;
    newVector.y = vectorToAdd.y + scalar;
    newVector.z = vectorToAdd.z + scalar;

    return newVector;
}

Vector3D operator+(const double scalar, const Vector3D& vectorToAdd)
{
    Vector3D newVector;
    newVector.x = scalar + vectorToAdd.x;
    newVector.y = scalar + vectorToAdd.y;
    newVector.z = scalar + vectorToAdd.z;

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
    Vector3D newVector;
    newVector.x = firstVectorToSubtract.x - secondVectorToSubtract.x;
    newVector.y = firstVectorToSubtract.y - secondVectorToSubtract.y;
    newVector.z = firstVectorToSubtract.z - secondVectorToSubtract.z;

    return newVector;
}

Vector3D operator-(const Vector3D& vectorToSubtract, const double scalar)
{
    Vector3D newVector;
    newVector.x = vectorToSubtract.x - scalar;
    newVector.y = vectorToSubtract.y - scalar;
    newVector.z = vectorToSubtract.z - scalar;

    return newVector;
}

Vector3D operator-(const double scalar, const Vector3D& vectorToSubtract)
{
    Vector3D newVector;
    newVector.x = scalar - vectorToSubtract.x;
    newVector.y = scalar - vectorToSubtract.y;
    newVector.z = scalar - vectorToSubtract.z;

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
    Vector3D newVector;
    newVector.x = vectorToMultiply.x * factor;
    newVector.y = vectorToMultiply.y * factor;
    newVector.z = vectorToMultiply.z * factor;

    return newVector;
}

Vector3D operator*(const double factor, const Vector3D& vectorToMultiply)
{
    Vector3D newVector;
    newVector.x = factor * vectorToMultiply.x;
    newVector.y = factor * vectorToMultiply.y;
    newVector.z = factor * vectorToMultiply.z;

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
    Vector3D newVector;
    newVector.x = vectorToDivide.x / denominator;
    newVector.y = vectorToDivide.y / denominator;
    newVector.z = vectorToDivide.z / denominator;

    return newVector;
}

Vector3D operator/(const double numerator, const Vector3D& vectorToDivide)
{
    if (vectorToDivide.x == 0 || vectorToDivide.y == 0 || vectorToDivide.z == 0)
    {
        throw std::domain_error("Division by zero");
    }
    Vector3D newVector;
    newVector.x = numerator / vectorToDivide.x;
    newVector.y = numerator / vectorToDivide.y;
    newVector.z = numerator / vectorToDivide.z;

    return newVector;
}
