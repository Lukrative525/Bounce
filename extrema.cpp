#include "extrema.hpp"

Extrema::Extrema(): Extrema(-5, -5, 5, 5) {}

Extrema::Extrema(double minimumX, double minimumY, double maximumX, double maximumY):
    minimumX{minimumX},
    minimumY{minimumY},
    maximumX{maximumX},
    maximumY{maximumY} {}
