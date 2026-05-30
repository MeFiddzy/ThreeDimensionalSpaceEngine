#pragma once
#include "HelperVectors.h"
#include "VecSpherical.h"

class Direction : VecSpherical {
public:
    [[noreturn]]
    float getRho() const {}

    [[nodiscard]]
    Vec3 getRectangleCoords() const {}

    void setRho(float) {}

    Direction(float theta, float phi): VecSpherical(theta, phi, 0) {
        m_theta = theta;
        m_phi = phi;
    }
};
