#include "../math_physics/VecSpherical.h"
#include <cmath>
#include "HelperVectors.h"

Vec3 VecSpherical::getRectangleCoords() const {
    return {
        rho * std::sin(phi) * std::sin(theta),
        rho * std::sin(phi) * std::cos(theta),
        rho * std::cos(phi)
    };
}

VecSpherical::VecSpherical(float theta, float phi, float rho) {
    this->theta = theta;
    this->phi = phi;
    this->rho = rho;
}

VecSpherical::VecSpherical(Vec3 v) {
    this->rho = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    this->theta = std::atan(v.y / v.x);
    this->phi = std::atan(v.z / this->rho);
}
