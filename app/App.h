#pragma once
#include <string>

#include "../math_physics/HelperVectors.h"

struct GLFWwindow;

class App {
public:
    App(std::string &&title, int width, int height);

    void loop();

    ~App();

    [[nodiscard]] const GLFWwindow *getWindow() const { return m_window; }

    [[nodiscard]] double getDeltaTIme() const { return m_deltaTime; }
private:
    class ShaderMethods {
    public:
        struct ShaderSource {
            std::string vertexSrc, fragmentSrc;
        };

        enum class ShaderType {
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1
        };

        static unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);

        static unsigned int compileShader(const std::string &source, unsigned int type);

        static ShaderSource parseShader(std::string path);

    };

    GLFWwindow* m_window;

    static float *genPositionArray(Vec2 v1, Vec2 v2, Vec2 v3);

    unsigned int m_buffer{};

    double m_lastTime{};
    double m_deltaTime{};

    unsigned int m_shader;
};
