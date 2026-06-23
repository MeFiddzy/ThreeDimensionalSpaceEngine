#pragma once
#include "../Color.h"
#include "../IMaterial.h"
#include "glm/glm.hpp"

class ColorMaterial : public IMaterial {
private:
    Color m_color;
    glm::mat4 mvp;
public:
    ColorMaterial(const Color &color, const glm::mat4 &mvp);

    [[nodiscard]] Color getColor() const;
    [[nodiscard]] glm::mat4 getMVPMat() const;

    void setColor(const Color &color);
    void setMVPMat(const glm::mat4 &proj);
};
