#pragma once
#include <string>

#include "Buffer.h"
#include "Render.h"
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
    void handleDT();

    GLFWwindow* m_window;

    VertexArray m_vao;

    Render<Vec2> m_render;

    Buffer m_vertexBuffer;
    Buffer m_indexBuffer;

    double m_lastTime{};
    double m_deltaTime{};

    Shader m_shader;
};
