#pragma once

struct Vec3;

class VecSpherical {
    float theta, phi, rho;
public:
    [[nodiscard]] Vec3 getRectangleCoords() const;

    VecSpherical(float theta, float phi, float rho);

    VecSpherical(Vec3 v);
};