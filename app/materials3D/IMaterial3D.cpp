#include "IMaterial3D.h"

glm::mat4 & IMaterial3D::getMVP() {
    return m_MVP;
}

void IMaterial3D::setMVP(const glm::mat4 &MVP) {
    m_MVP = MVP;
    m_shader.setUniform("u_MVP", glUniformMatrix4fv, 1, GL_FALSE, &MVP[0][0]);
}
