#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D
{
public:
    Vector3D(const double newX = 0, const double newY = 0, const double newZ = 0);
    Vector3D(const Vector3D& vectorToCopy);
    double x{0};
    double y{0};
    double z{0};
    double calculate_magnitude_squared() const;
    double calculate_magnitude() const;
    void normalize();
    double dot(const Vector3D& secondVector) const;
    Vector3D cross(const Vector3D& secondVector) const;
    Vector3D& operator=(const Vector3D& vectorToCopy);
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
