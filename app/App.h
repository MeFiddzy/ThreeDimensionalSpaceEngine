#pragma once
#include <string>

#include "Buffer.h"
#include "Color.h"
#include "Render.h"
#include "Renderer.h"
#include "ShaderMethods.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "VertexArray.h"
#include "../helper/Direction.h"

struct TexturedShape;
struct GLFWwindow;

using Render3DType = Vec3;

class App {
public:
    App(int width, int height);

    void loop();

    ~App();

    [[nodiscard]] const GLFWwindow *getWindow() const { return m_window; }

    [[nodiscard]] double getDeltaTIme() const { return m_deltaTime; }
private:
    void handleDT();
    void updateMVP();
    void handleMovement();
    void handleLightSourceChange();
    void handleResets();

    float modC(float x, float n);

    void handleSphericalRotations();

    Color inputColors();

    glm::quat rotate(const glm::quat &q, float theta, float phi);

    int m_width;
    int m_height;

    float m_fovDeg;
    float m_nearPlane;
    float m_farPlane;

    Vec3 m_cameraPos;
    Direction m_cameraDir{};

    Vec3 m_cameraOffest{};

    GLFWwindow* m_window;

    Texture m_texture;

    Renderer<Render3DType> m_renderer3D;
    Renderer<TexturedShape> m_renderer2D;

    glm::mat4 m_projMat;
    glm::mat4 m_viewMat;

    double m_lastTime{};
    double m_deltaTime{};
};
