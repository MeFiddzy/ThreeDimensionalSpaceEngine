#pragma once
#include "HelperVectors.h"
#include "VecSpherical.h"

class Direction : public VecSpherical {
public:
    void setRho(float) { m_rho = 1; }

    Direction() = default;

    Direction(const float theta, const float phi): VecSpherical(theta, phi, 1) {}
};
