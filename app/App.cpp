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

App::App(const int width, const int height) {
    m_fovDeg = 50;
    m_nearPlane = .1;
    m_farPlane = 1000.;

    m_cameraDir = Direction(glm::radians(40.), glm::radians(0.));
    m_cameraPos = Vec3(0, 0, 0);

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

    auto render = new Render3D<Render3DType>(Render<Render3DType>(), Transform(
        Vec3(0., 0., 1.),
        Vec3(.6, .6, .6),
        Quaternion(1., 0., 0., 0.)
    ));

    render->addMaterial(new ColorMaterial3D(Color(1.f, 0.f, 0.f, 1.f), render->getTransform().getMVP(m_viewMat, m_projMat)));

    render->setShaderType(ShaderType::MATERIAL);

    render->addVertex(Vec3(-0.5, -0.5, -0.5)); // 0
    render->addVertex(Vec3( 0.5, -0.5, -0.5)); // 1
    render->addVertex(Vec3( 0.5,  0.5, -0.5)); // 2
    render->addVertex(Vec3(-0.5,  0.5, -0.5)); // 3
    render->addVertex(Vec3(-0.5, -0.5,  0.5)); // 4
    render->addVertex(Vec3( 0.5, -0.5,  0.5)); // 5
    render->addVertex(Vec3( 0.5,  0.5,  0.5)); // 6
    render->addVertex(Vec3(-0.5,  0.5,  0.5)); // 7


    render->addTriangle(Triangle<UInt>(0, 1, 2));
    render->addTriangle(Triangle<UInt>(0, 2, 3));

    render->addTriangle(Triangle<UInt>(4, 6, 5));
    render->addTriangle(Triangle<UInt>(4, 7, 6));

    render->addTriangle(Triangle<UInt>(0, 3, 7));
    render->addTriangle(Triangle<UInt>(0, 7, 4));

    render->addTriangle(Triangle<UInt>(1, 5, 6));
    render->addTriangle(Triangle<UInt>(1, 6, 2));

    render->addTriangle(Triangle<UInt>(0, 4, 5));
    render->addTriangle(Triangle<UInt>(0, 5, 1));

    render->addTriangle(Triangle<UInt>(3, 2, 6));
    render->addTriangle(Triangle<UInt>(3, 6, 7));

    render->genBuffers(GL_STATIC_DRAW);

    glCall(glEnable(GL_DEPTH_TEST));

    glCall(glEnable(GL_BLEND));
    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))

    m_renderer3D.addRender(render);
}


void App::loop() {
    while (!glfwWindowShouldClose(m_window)) {
        glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        if (glfwGetKey(m_window, GLFW_KEY_UP)) {
            m_cameraDir.setPhi(m_cameraDir.getPhi() + .0001f);
        }

        m_projMat = glm::perspective(glm::radians(m_fovDeg), static_cast<float>(m_width) / static_cast<float>(m_height),
            m_nearPlane, m_farPlane);
        m_viewMat = glm::lookAt(
            m_cameraPos.toGLM(),
            m_cameraPos.toGLM() + m_cameraDir.getRectangleCoords().toGLM(),
            glm::vec3(0, 1, 0)
        );

        auto u = static_cast<Render3D<Render3DType>*>(m_renderer3D.getRender(0));
        u->setTransform(Transform{
            u->getTransform().pos,
            u->getTransform().scale,
            u->getTransform().rotation + Quaternion(0., 0., 0., 0.),
        });

        updateMVP();

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
    }
}
