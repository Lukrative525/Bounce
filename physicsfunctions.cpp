#include "physicsfunctions.hpp"
#include "vector3d.hpp"

namespace phys
{
    Vector3D calculate_function_change(double timeStep, const Vector3D& functionDerivative)
    {
        Vector3D functionChange{timeStep * functionDerivative};

        return functionChange;
    }
}
