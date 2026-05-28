#include "App.h"

#include <fstream>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "../math_physics/HelperVectors.h"

App::App(std::string &&title, int width, int height) {
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwDestroyWindow(m_window);
        glfwTerminate();
        m_window = nullptr;
        return;
    }

    glGenBuffers(1, &m_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);

    glBufferData(
        GL_ARRAY_BUFFER,
        6 * sizeof(float),
        genPositionArray(
            Vec2{0.f, 0.f},
            Vec2{0.5f, 0.f},
            Vec2{0.f, 0.5f}
        ),
        GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    m_shader = createShader(readShader("testing.vs"), readShader("testing.fs"));

    glUseProgram(m_shader);
}

void App::loop() {
    while (!glfwWindowShouldClose(m_window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(m_window);

        glfwPollEvents();

        m_deltaTime = glfwGetTime() - m_lastTime;
        m_lastTime = glfwGetTime();
    }
}

App::~App() {
    glfwDestroyWindow(m_window);
    glfwTerminate();

    glDeleteProgram(m_shader);
}

unsigned int App::createShader(const std::string &vertexShader, const std::string &fragmentShader) {
    const unsigned int program = glCreateProgram();

    const unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    const unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int App::compileShader(const std::string &source, unsigned int type) {
    const unsigned int id = glCreateShader(type);
    const char *src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int res;
    glGetShaderiv(id, GL_COMPILE_STATUS, &res);

    if (res == GL_FALSE) {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

        char *err = static_cast<char*>(alloca(len * sizeof(char)));
        glGetShaderInfoLog(id, len, &len, err);

        std::cout << "[" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "_SHADER_ERROR] " << err << '\n';

        glDeleteShader(id);

        throw std::exception("Shader compilation fail!");
    }

    return id;
}

std::string App::readShader(std::string shaderName) {
    std::fstream fin("shaders\\" + shaderName);

    std::string shaderSource;
    std::string tmp;

    while (std::getline(fin, tmp)) {
        shaderSource += tmp + '\n';
    }

    return shaderSource;
}

[[nodiscard("Need to free the memory!")]]
[[deprecated]]
float *App::genPositionArray(const Vec2 v1, const Vec2 v2, const Vec2 v3) {
    return new float[6]{
        v1.x, v1.y,
        v2.x, v2.y,
        v3.x, v3.y
    };
}
