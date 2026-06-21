#include "App.h"

#include <fstream>
#include <sstream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Helper.h"
#include "Render.h"
#include "ShapeGeneration.h"
#include "../helper/HelperVectors.h"

#include "glm/gtc/matrix_transform.hpp"
#include "materials/ColorMaterial.h"
#include "materials/TextureMaterial.h"

App::App(const int width, const int height) {
    s_width = width;
    s_height = height;

    if (!glfwInit()) {
        m_window = nullptr;
        return;
    }
    m_window = glfwCreateWindow(width, height, "Title", nullptr, nullptr);

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

    m_proj = glm::ortho<float>(0, width, height, 0, -1.f, 1.f);

    auto *render1 = ShapeGeneration::connectPoints({
        Vec2(300,300),
        Vec2(500,300),
        Vec2(500,500),
        Vec2(300,500),
    });
    render1->setShaderType(ShaderType::MATERIAL);
    render1->addMaterial(new ColorMaterial(Color(1.f, 0.f, 0.f, .5f), m_proj));

    auto *render2 = ShapeGeneration::connectPoints({
        Vec2(100, 100),
        Vec2(200, 100),
        Vec2(400, 500),
        Vec2(100, 200)
    });
    render2->setShaderType(ShaderType::MATERIAL);
    render2->addMaterial(new ColorMaterial(Color(0.f, 0.f, 1.f, .5f), m_proj));

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

int App::s_height = 0;
int App::s_width = 0;

void App::handleDT() {
    m_deltaTime = glfwGetTime() - m_lastTime;
    m_lastTime = glfwGetTime();
}
