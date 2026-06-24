#pragma once
#include "../IMaterial.h"
#include "glm/glm.hpp"

class IMaterial3D : public IMaterial {
protected:
    glm::mat4 m_MVP{1.};
    glm::mat4 m_model{1.};
public:
    IMaterial3D() = default;

    glm::mat4 &getMVP();
    void setMVP(const glm::mat4 &MVP);
    void setModel(const glm::mat4 &model);
};
