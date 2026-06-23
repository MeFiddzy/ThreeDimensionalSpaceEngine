#include "ColorMaterial.h"

ColorMaterial::ColorMaterial(const Color &color, const glm::mat4 &mvp) :
    m_color(color), mvp(mvp) {

    m_shader = Shader("2D/color_shader.glsl");

    m_shader.addUniform("u_MVP");
    m_shader.addUniform("u_color");

    m_shader.setUniform("u_color", glUniform4f, color.r, color.g, color.b, color.a);
    m_shader.setUniform("u_MVP", glUniformMatrix4fv, 1, GL_FALSE, &mvp[0][0]);
}

Color ColorMaterial::getColor() const {
    return m_color;
}

glm::mat4 ColorMaterial::getMVPMat() const {
    return mvp;
}

void ColorMaterial::setColor(const Color &color) {
    m_color = color;
    m_shader.setUniform("u_color", glUniform4f, color.r, color.g, color.b, color.a);
}

void ColorMaterial::setMVPMat(const glm::mat4 &proj) {
    mvp = proj;
    m_shader.setUniform("u_MVP", glUniformMatrix4fv, 1, GL_FALSE, &proj[0][0]);
}
