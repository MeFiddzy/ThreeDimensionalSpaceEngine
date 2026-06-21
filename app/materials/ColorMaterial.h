#pragma once
#include "../Color.h"
#include "../IMaterial.h"
#include "glm/glm.hpp"

class ColorMaterial : public IMaterial {
private:
    Color m_color;
    glm::mat4 m_projMat;
public:
    ColorMaterial(const Color &color, glm::mat4 &proj);

    [[nodiscard]] Color getColor() const;
    [[nodiscard]] glm::mat4 getProjMat() const;

    void setColor(const Color &color);
    void setProjMat(const glm::mat4 &proj);
};
