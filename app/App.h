#pragma once
#include <string>

#include "Buffer.h"
#include "Render.h"
#include "Renderer.h"
#include "ShaderMethods.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "VertexArray.h"

struct TexturedShape;
struct GLFWwindow;

class App {
public:
    App(int width, int height);

    void loop();

    ~App();

    [[nodiscard]] const GLFWwindow *getWindow() const { return m_window; }

    [[nodiscard]] double getDeltaTIme() const { return m_deltaTime; }
private:
    static int s_width;
    static int s_height;

    void handleDT();

    GLFWwindow* m_window;

    Texture m_texture;

    Renderer<TexturedShape> m_renderer;

    glm::mat4 m_proj;
    glm::mat4 m_view;

    glm::mat4 m_mvp;

    double m_lastTime{};
    double m_deltaTime{};
};
