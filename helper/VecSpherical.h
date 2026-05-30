#pragma once

struct Vec3;

class VecSpherical {
protected:
    float m_theta, m_phi, m_rho;
public:
    [[nodiscard]] float getTheta() const { return m_theta; }
    [[nodiscard]] float getPhi() const { return m_phi; }
    [[nodiscard]] float getRho() const { return m_rho; }

    void setTheta(const float _) { m_theta = _; }
    void setPhi(const float _) { m_phi = _; }
    void setRho(const float _) { m_rho = _; }

    [[nodiscard]] Vec3 getRectangleCoords() const;

    VecSpherical(float theta, float phi, float rho);

    VecSpherical(Vec3 v);
};