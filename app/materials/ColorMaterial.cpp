#include "ColorMaterial.h"

ColorMaterial::ColorMaterial(const Color &color, glm::mat4 &proj) :
    m_color(color), m_projMat(proj) {

    m_shader = Shader("color_shader.glsl");

    m_shader.addUniform("u_MVP");
    m_shader.addUniform("u_color");

    m_shader.setUniform("u_color", glUniform4f, color.r, color.g, color.b, color.a);
    m_shader.setUniform("u_MVP", glUniformMatrix4fv, 1, GL_FALSE, &proj[0][0]);
}

Color ColorMaterial::getColor() const {
    return m_color;
}

glm::mat4 ColorMaterial::getProjMat() const {
    return m_projMat;
}

void ColorMaterial::setColor(const Color &color) {
    m_color = color;
    m_shader.setUniform("u_color", glUniform4f, color.r, color.g, color.b, color.a);
}

void ColorMaterial::setProjMat(const glm::mat4 &proj) {
    m_projMat = proj;
    m_shader.setUniform("u_MVP", glUniformMatrix4fv, 1, GL_FALSE, &proj[0][0]);
}
