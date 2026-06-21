#pragma once
#include "../IMaterial.h"
#include "../Texture.h"
#include "glm/glm.hpp"

class TextureMaterial : public IMaterial {
public:
    TextureMaterial() = default;
    explicit TextureMaterial(const Texture &texture, glm::mat4 proj, UInt slot = 0);
    explicit TextureMaterial(Texture &&texture, glm::mat4 proj, UInt slot = 0);

    void setProjMat(const glm::mat4 &proj);
    [[nodiscard]] glm::mat4 getProjMat() const;

    Texture &getTexture();

    [[nodiscard]] UInt getSlot() const;
    void setSlot(UInt slot);

    void onDraw() override;
private:
    UInt m_slot{};
    glm::mat4 m_projMat{};
    Texture m_texture;
};
