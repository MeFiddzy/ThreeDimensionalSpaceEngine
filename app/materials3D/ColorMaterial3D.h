#pragma once
#include "IMaterial3D.h"
#include "../Color.h"
#include "../IMaterial.h"
#include "../../helper/Direction.h"
#include "glm/glm.hpp"

class ColorMaterial3D : public IMaterial3D {
private:
    Color m_color;
    Vec3 m_lightDir{.0, .3, .0};
public:
    ColorMaterial3D(const Color &color, const glm::mat4 &mvp);

    [[nodiscard]] Color getColor() const;

    void setColor(const Color &color);

    void setLightDir(const Vec3 &dir);
};
