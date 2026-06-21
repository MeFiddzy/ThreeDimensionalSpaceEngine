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
    App(int width, int height);

    void loop();

    ~App();

    [[nodiscard]] const GLFWwindow *getWindow() const { return m_window; }

    [[nodiscard]] double getDeltaTIme() const { return m_deltaTime; }

    static Vec2 px(const Vec2 &vec);
    static Vec2 u(const Vec2 &vec);
    static Vec2 ub(UInt x, UInt y);
private:
    static int s_width;
    static int s_height;

    void handleDT();

    GLFWwindow* m_window;

    Texture m_texture;

    Renderer<TexturedShape> m_renderer;

    static float s_span;

    double m_lastTime{};
    double m_deltaTime{};
};
