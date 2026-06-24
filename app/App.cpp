#include "App.h"

#include <fstream>
#include <sstream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Helper.h"
#include "Render.h"
#include "Render3D.h"
#include "ShapeGeneration.h"
#include "Transform.h"
#include "../helper/Direction.h"
#include "../helper/HelperVectors.h"

#include "glm/gtc/matrix_transform.hpp"
#include "materials2D/ColorMaterial.h"
#include "materials2D/TextureMaterial.h"
#include "materials3D/ColorMaterial3D.h"
#include "materials3D/IMaterial3D.h"

const auto g_startingPos = Vec3(0, 0, -2);


App::App(const int width, const int height) {
    m_fovDeg = 50;
    m_nearPlane = .1;
    m_farPlane = 1000.;

    m_cameraDir = Direction(0, 0);
    m_cameraPos = g_startingPos;

    m_width = width;
    m_height = height;

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

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))  {
        glfwDestroyWindow(m_window);
        glfwTerminate();
        m_window = nullptr;
        return;
    }

    m_projMat = glm::perspective(glm::radians(m_fovDeg), static_cast<float>(width) / static_cast<float>(height),
        m_nearPlane, m_farPlane);
    m_viewMat = glm::lookAt(
        m_cameraPos.toGLM(),
        m_cameraPos.toGLM() + m_cameraDir.getRectangleCoords().toGLM(),
        glm::vec3(0, 1, 0)
    );

    auto render = ShapeGeneration::loadFromOBJ("model.obj");
    render->setShaderType(ShaderType::MATERIAL);
    render->addMaterial(new ColorMaterial3D(inputColors(), render->getTransform().getMVP(m_viewMat, m_projMat)));

    render->getTransform().scale = {.2f, .2f, .2f};

    m_renderer3D.addRender(render);

    glCall(glEnable(GL_DEPTH_TEST));

    glCall(glEnable(GL_BLEND));
    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
}

constexpr float g_flyingSpeed = .006f;
constexpr float g_rotatingSpeed = .006f;

void App::loop() {
    while (!glfwWindowShouldClose(m_window)) {
        glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        handleMovement();
        handleLightSourceChange();
        handleSphericalRotations();
        handleResets();

        m_projMat = glm::perspective(glm::radians(m_fovDeg), static_cast<float>(m_width) / static_cast<float>(m_height),
            m_nearPlane, m_farPlane);
        m_viewMat = glm::lookAt(
            m_cameraPos.toGLM(),
            m_cameraPos.toGLM() + m_cameraDir.getRectangleCoords().toGLM(),
            glm::vec3(0, 1, 0)
        );

        updateMVP();

        m_cameraPos = VecSpherical(m_cameraDir.getTheta(), m_cameraDir.getPhi(), g_startingPos.z).getRectangleCoords() + m_cameraOffest;

        m_renderer3D.render(m_window);

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

void App::updateMVP() {
    for (const auto render : m_renderer3D.getRenders()) {
        const auto material3D = static_cast<IMaterial3D *>(render->getMaterial());
        const auto render3D = static_cast<Render3D<Render3DType>*>(render);

        material3D->setMVP(render3D->getTransform().getMVP(m_viewMat, m_projMat));
        material3D->setModel(render3D->getTransform().toModelMatrix());
    }
}

void App::handleMovement() {
    if (glfwGetKey(m_window, GLFW_KEY_S)) {
        m_cameraOffest.z -= g_flyingSpeed;
    }
    if (glfwGetKey(m_window, GLFW_KEY_W)) {
        m_cameraOffest.z += g_flyingSpeed;
    }
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL)) {
        m_cameraOffest.y -= g_flyingSpeed;
    }
    if (glfwGetKey(m_window, GLFW_KEY_SPACE)) {
        m_cameraOffest.y += g_flyingSpeed;
    }
    if (glfwGetKey(m_window, GLFW_KEY_D)) {
        m_cameraOffest.x -= g_flyingSpeed;
    }
    if (glfwGetKey(m_window, GLFW_KEY_A)) {
        m_cameraOffest.x += g_flyingSpeed;
    }
}

void App::handleLightSourceChange() {
    if (glfwGetKey(m_window, GLFW_KEY_L)) {
        auto render = static_cast<Render3D<Render3DType>*>(m_renderer3D.getRender(0));

        static_cast<ColorMaterial3D*>(render->getMaterial())->setLightDir(m_cameraPos * .1f);
    }
}

void App::handleResets() {
    if (glfwGetKey(m_window, GLFW_KEY_R)) {
        if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT)) {
            m_cameraPos = Vec3(0, 0, 0);
            m_cameraDir = Direction(0, 0);
        }

        m_cameraOffest = Vec3(0, 0, 0);
    }
}

float App::modC(float x, float n) {
    while (x >= n) {
        x -= n;
    }
    return x;
}

void App::handleSphericalRotations() {
    if (glfwGetKey(m_window, GLFW_KEY_UP)) {
        m_cameraDir.setPhi(-modC(-(m_cameraDir.getPhi() - g_rotatingSpeed), glm::radians(90.)));
        std::cout << m_cameraDir.getPhi() << '\n';
    }
    if (glfwGetKey(m_window, GLFW_KEY_DOWN)) {
        m_cameraDir.setPhi(m_cameraDir.getPhi() + g_rotatingSpeed);
    }

    if (glfwGetKey(m_window, GLFW_KEY_LEFT)) {
        m_cameraDir.setTheta(m_cameraDir.getTheta() + g_rotatingSpeed);
    }
    if (glfwGetKey(m_window, GLFW_KEY_RIGHT)) {
        m_cameraDir.setTheta(m_cameraDir.getTheta() - g_rotatingSpeed);
    }
}

Color App::inputColors() {
    UInt r, g, b, a;

    std::ifstream stream("color.txt");
    auto clearLine = [&]() {
        char c;
        while (stream.get(c)) {
            if (c == '\n') {
                break;
            }
        }
    };

    stream >> r;
    clearLine();
    stream >> g;
    clearLine();
    stream >> b;
    clearLine();
    stream >> a;
    clearLine();

    return Color(r, g, b, a);
}

glm::quat App::rotate(const glm::quat &q, const float theta, const float phi) {
    return glm::quat(cos(theta / 2), 0, sin(theta / 2), 0) * glm::quat(cos(phi / 2), sin(phi / 2), 0, 0) * q;
}
