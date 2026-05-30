#include "../helper/VecSpherical.h"
#include <cmath>
#include "HelperVectors.h"

Vec3 VecSpherical::getRectangleCoords() const {
    return {
        m_rho * std::sin(m_phi) * std::sin(m_theta),
        m_rho * std::sin(m_phi) * std::cos(m_theta),
        m_rho * std::cos(m_phi)
    };
}

VecSpherical::VecSpherical(float theta, float phi, float rho) {
    this->m_theta = theta;
    this->m_phi = phi;
    this->m_rho = rho;
}

VecSpherical::VecSpherical(Vec3 v) {
    this->m_rho = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    this->m_theta = std::atan(v.y / v.x);
    this->m_phi = std::atan(v.z / this->m_rho);
}
