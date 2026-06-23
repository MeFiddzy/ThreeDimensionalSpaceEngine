#include "IMaterial3D.h"

glm::mat4 & IMaterial3D::getMVP() {
    return m_MVP;
}

void IMaterial3D::setMVP(const glm::mat4 &MVP) {
    m_MVP = MVP;
}
