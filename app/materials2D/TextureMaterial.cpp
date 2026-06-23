#include "TextureMaterial.h"

TextureMaterial::TextureMaterial(const Texture &texture, const glm::mat4 &mvp, const UInt slot) {
    m_texture = texture;
    m_slot = slot;

    m_shader = Shader("2D/texture_shader.glsl");
    m_shader.addUniform("u_textureSlot");
    m_shader.addUniform("u_MVP");
    m_shader.setUniform("u_textureSlot", glUniform1i, slot);
    m_shader.setUniform("u_MVP", glUniformMatrix4fv, 1, GL_FALSE, &mvp[0][0]);
}

TextureMaterial::TextureMaterial(Texture &&texture, glm::mat4 &mvp, const UInt slot) {
    m_texture = std::move(texture);
    m_slot = slot;

    m_shader = Shader("2D/texture_shader.glsl");
    m_shader.addUniform("u_textureSlot");
    m_shader.addUniform("u_MVP");
    m_shader.setUniform("u_textureSlot", glUniform1i, slot);
    m_shader.setUniform("u_MVP", glUniformMatrix4fv, 1, GL_FALSE, &mvp[0][0]);
}

void TextureMaterial::setProjMat(const glm::mat4 &proj) {
    m_mvp = proj;
    m_shader.setUniform("u_MVP", glUniformMatrix4fv, 1, GL_FALSE, &proj[0][0]);
}

glm::mat4 TextureMaterial::getProjMat() const {
    return m_mvp;
}

Texture & TextureMaterial::getTexture() {
    return m_texture;
}

UInt TextureMaterial::getSlot() const {
    return m_slot;
}

void TextureMaterial::setSlot(const UInt slot) {
    m_slot = slot;
    m_shader.setUniform("u_textureSlot", glUniform1i, slot);
}

void TextureMaterial::onDraw() {
    m_texture.bind(m_slot);
}
