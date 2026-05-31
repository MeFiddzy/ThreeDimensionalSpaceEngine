#pragma once
#include <string>

#include "Buffer.h"
#include "ShaderMethods.h"
#include "VertexArray.h"

struct GLFWwindow;

class App {
public:
    App(std::string &&title, int width, int height);

    void loop();

    ~App();

    [[nodiscard]] const GLFWwindow *getWindow() const { return m_window; }

    [[nodiscard]] double getDeltaTIme() const { return m_deltaTime; }
private:
    GLFWwindow* m_window;

    VertexArray m_vao;

    Buffer<float> m_vertexBuffer;
    Buffer<unsigned int> m_indexBuffer;

    double m_lastTime{};
    double m_deltaTime{};

    Shader m_shader;
};
