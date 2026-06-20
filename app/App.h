#pragma once
#include <string>

#include "Buffer.h"
#include "Render.h"
#include "Renderer.h"
#include "ShaderMethods.h"
#include "Texture.h"
#include "VertexArray.h"

struct TexturedShape;
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

    Texture m_texture;

    Renderer<TexturedShape> m_renderer;

    Render<TexturedShape> m_render;

    double m_lastTime{};
    double m_deltaTime{};
};
