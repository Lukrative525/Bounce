#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <vector>

class Vector3D
{
private:
    std::vector<double> components;
public:
    Vector3D();
    Vector3D(const double newX, const double newY, const double newZ);
    Vector3D(const Vector3D& vectorToCopy);
    double get_x() const;
    double get_y() const;
    double get_z() const;
    void set_x(const double newX);
    void set_y(const double newY);
    void set_z(const double newZ);
    double calculate_magnitude_squared() const;
    double calculate_magnitude() const;
    void normalize();
    double dot(const Vector3D& secondVector) const;
    Vector3D cross(const Vector3D& secondVector) const;
    bool operator==(const Vector3D& secondVector) const;
    bool operator!=(const Vector3D& secondVector) const;
    double& operator[](const int index);
    double operator[](const int index) const;
};

Vector3D operator+(const Vector3D& firstVectorToAdd, const Vector3D& secondVectorToAdd);
Vector3D operator+(const Vector3D& vectorToAdd, const double scalar);
Vector3D operator+(const double scalar, const Vector3D& vectorToAdd);
Vector3D operator-(const Vector3D& firstVectorToSubtract, const Vector3D& secondVectorToSubtract);
Vector3D operator-(const Vector3D& vectorToSubtract, const double scalar);
Vector3D operator-(const double scalar, const Vector3D& vectorToSubtract);
Vector3D operator*(const Vector3D& vectorToMultiply, const double factor);
Vector3D operator*(const double factor, const Vector3D& vectorToMultiply);
Vector3D operator/(const Vector3D& vectorToDivide, const double denominator);
Vector3D operator/(const double numerator, const Vector3D& vectorToDivide);

#endif
