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

#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

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

    float aspectRatioInv = static_cast<float>(height) / static_cast<float>(width);

    glm::mat4 proj = glm::ortho<float>(-2.f, 2.f, -aspectRatioInv * 2.f, aspectRatioInv * 2.f, -1.f, 1.f);

    auto *render1 = new Render<TexturedShape>;
    auto *render2 = new Render<TexturedShape>;

    render1->addVertex(TexturedShape({-0.5f, -0.5f}, {0.f, 0.f}));
    render1->addVertex(TexturedShape({0.5f, -0.5f}, {1.f, 0.f}));
    render1->addVertex(TexturedShape({0.5f, 0.5f}, {1.f, 1.f}));
    render1->addVertex(TexturedShape({-0.5f, 0.5f}, {0.f, 1.f}));

    render2->addVertex(TexturedShape({-0.2f, -0.2f}, {0.f, 0.f}));
    render2->addVertex(TexturedShape({0.8f, -0.2f}, {1.f, 0.f}));
    render2->addVertex(TexturedShape({0.8f, 0.8f}, {1.f, 1.f}));
    render2->addVertex(TexturedShape({-0.2f, 0.8f}, {0.f, 1.f}));

    render1->addTriangle(Triangle<UInt>(0, 1, 2));
    render1->addTriangle(Triangle<UInt>(2, 3, 0));

    render2->addTriangle(Triangle<UInt>(0, 1, 2));
    render2->addTriangle(Triangle<UInt>(2, 3, 0));

    render1->genBuffers(GL_STATIC_DRAW);
    render2->genBuffers(GL_STATIC_DRAW);

    render1->addShader(Shader("color_shader.glsl"));
    render1->shader().addUniform("u_color");
    render1->shader().setUniform("u_color", glUniform4f, 1.f, 0.f, 0.f, .5f);
    render1->shader().setUniform("u_MVP", glUniformMatrix4fv, 1, GL_FALSE, &proj[0][0]);

    render2->addShader(Shader("color_shader.glsl"));
    render2->shader().addUniform("u_color");
    render2->shader().setUniform("u_color", glUniform4f, 0.f, 0.f, 1.f, .5f);
    render2->shader().setUniform("u_MVP", glUniformMatrix4fv, 1, GL_FALSE, &proj[0][0]);

    /*
    m_texture = Texture("resources/textures/thumbs_up.png");
    m_texture.bind();
    render1->shader().addUniform("u_textureSlot");
    render1->shader().setUniform("u_textureSlot", glUniform1i, 0);
    */

    glCall(glEnable(GL_BLEND));
    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))

    m_renderer.addRender(render1);
    m_renderer.addRender(render2);
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
