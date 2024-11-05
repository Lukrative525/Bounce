#ifndef PHYSICSFUNCTIONS_HPP
#define PHYSICSFUNCTIONS_HPP

class Vector3D;

namespace phys
{
    Vector3D calculate_function_change(double timeStep, const Vector3D& functionDerivative);
}

#endif // PHYSICSFUNCTIONS_HPP
