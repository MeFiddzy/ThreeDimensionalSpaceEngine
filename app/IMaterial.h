#pragma once
#include "ShaderMethods.h"

class IMaterial {
protected:
    Shader m_shader;
public:
    Shader &shader() { return m_shader; }

    virtual ~IMaterial() = default;

    IMaterial() = default;

    virtual void onDraw() {}
};
