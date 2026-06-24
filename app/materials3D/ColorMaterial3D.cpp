#include "ColorMaterial3D.h"

ColorMaterial3D::ColorMaterial3D(const Color &color, const glm::mat4 &mvp) :
    m_color(color) {

    this->m_MVP = mvp;

    m_shader = Shader("3D/color_shader3D.glsl");

    m_shader.addUniform("u_MVP");
    m_shader.addUniform("u_color");
    m_shader.addUniform("u_model");
    m_shader.addUniform("u_lightDir");

    m_shader.setUniform("u_color", glUniform4f, color.r, color.g, color.b, color.a);
    m_shader.setUniform("u_MVP", glUniformMatrix4fv, 1, GL_FALSE, &mvp[0][0]);
    m_shader.setUniform("u_lightDir", glUniform3f, m_lightDir.x, m_lightDir.y, m_lightDir.z);
}

Color ColorMaterial3D::getColor() const {
    return m_color;
}

void ColorMaterial3D::setColor(const Color &color) {
    m_color = color;
    m_shader.setUniform("u_color", glUniform4f, color.r, color.g, color.b, color.a);
}

void ColorMaterial3D::setLightDir(const Vec3 &dir) {
    m_lightDir = dir;
    m_shader.setUniform("u_lightDir", glUniform3f, dir.x, dir.y, dir.z);
}
