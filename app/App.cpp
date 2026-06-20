#include "App.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Helper.h"
#include "Render.h"
#include "ShaderMethods.h"
#include "TexturedShape.h"
#include "../helper/HelperVectors.h"

App::App(std::string &&title, const int width, const int height) {
    if (!glfwInit()) {
        m_window = nullptr;
        return;
    }
    m_window = glfwCreateWindow(width, height, std::move(title).c_str(), nullptr, nullptr);

    if (!m_window) {
        glfwTerminate();
        m_window = nullptr;
        return;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwDestroyWindow(m_window);
        glfwTerminate();
        m_window = nullptr;
        return;
    }

    m_render.addVertex(TexturedShape({-0.5f, -0.5f}, {0.f, 0.f}));
    m_render.addVertex(TexturedShape({0.5f, -0.5f}, {1.f, 0.f}));
    m_render.addVertex(TexturedShape({0.5f, 0.5f}, {1.f, 1.f}));
    m_render.addVertex(TexturedShape({-0.5f, 0.5f}, {0.f, 1.f}));

    m_render.addTriangle(Triangle<UInt>(0, 1, 2));
    m_render.addTriangle(Triangle<UInt>(2, 3, 0));

    m_render.genBuffers(GL_STATIC_DRAW);

    m_render.addShader(Shader("texture_shader.glsl"));

    m_texture = Texture("resources/textures/thumbs_up.png");
    m_texture.bind();
    m_render.shader().addUniform("u_textureSlot");
    m_render.shader().setUniform("u_textureSlot", glUniform1i, 0);

    m_renderer.addRender(&m_render);
}


void App::loop() {
    while (!glfwWindowShouldClose(m_window)) {
        m_renderer.render(m_window);

        handleDT();
    }
}

App::~App() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void App::handleDT() {
    m_deltaTime = glfwGetTime() - m_lastTime;
    m_lastTime = glfwGetTime();
}
