#include "App.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Helper.h"
#include "Render.h"
#include "ShaderMethods.h"
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

    m_render.addVertex(Vec2(-0.8f, -0.5f));
    m_render.addVertex(Vec2( 0.8f, -0.5f));
    m_render.addVertex(Vec2( 0.4f,  0.5f));
    m_render.addVertex(Vec2(-0.4f,  0.5f));

    m_render.addTriangle(Triangle<UInt>(0, 1, 2));
    m_render.addTriangle(Triangle<UInt>(2, 3, 0));

    m_render.genBuffers(GL_STATIC_DRAW);

    m_shader = Shader("basic.glsl");
    m_shader.addUniform("u_coef");
    m_shader.setUniform("u_coef", glUniform1f, 1.2f);
}


void App::loop() {
    while (!glfwWindowShouldClose(m_window)) {
        glCall(glClear(GL_COLOR_BUFFER_BIT));

        m_shader.use();
        m_render.draw();

        glfwSwapBuffers(m_window);

        glfwPollEvents();

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
