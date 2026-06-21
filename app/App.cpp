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
#include "glm/glm.hpp"
#include "materials/ColorMaterial.h"
#include "materials/TextureMaterial.h"

float App::s_span = 4.f;

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

    const float aspectRatioInv = static_cast<float>(height) / static_cast<float>(width);

    glm::mat4 proj = glm::ortho<float>(-s_span / 2, s_span / 2, -aspectRatioInv * 2.f, aspectRatioInv * 2.f, -1.f, 1.f);

    auto *render1 = ShapeGeneration::connectPoints({
        ub(300,300),
        ub(500,300),
        ub(500,500),
        ub(300,500),
    });
    render1->setShaderType(ShaderType::MATERIAL);
    render1->addMaterial(new ColorMaterial(Color(1.f, 0.f, 0.f, .5f), proj));

    auto *render2 = ShapeGeneration::connectPoints({
        ub(100, 100),
        ub(200, 100),
        ub(400, 500),
        ub(100, 200)
    });
    render2->setShaderType(ShaderType::MATERIAL);
    render2->addMaterial(new ColorMaterial(Color(0.f, 0.f, 1.f, .5f), proj));

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

Vec2 App::px(const Vec2 &vec) {
    return vec * (s_width / s_span);
}

Vec2 App::u(const Vec2 &vec) {
    return vec / (s_width / s_span);
}

Vec2 App::ub(const UInt x, const UInt y) {
    return u(Vec2(
        static_cast<float>(x) - static_cast<float>(s_width) / 2.f,
        static_cast<float>(s_height) / 2.f - static_cast<float>(y)
    ));
}

void App::handleDT() {
    m_deltaTime = glfwGetTime() - m_lastTime;
    m_lastTime = glfwGetTime();
}
