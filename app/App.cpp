#include "App.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Helper.h"
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

    m_vao = VertexArray();

    m_vertexBuffer = Buffer<float>(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    m_vertexBuffer.loadBuffer(new float[8]{
                                  -.5f, -.5f,
                                  .5f, -.5f,
                                  .5f, .5f,
                                  -.5f, .5f
                              }, 8);

    m_indexBuffer = Buffer<unsigned int>(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    m_indexBuffer.loadBuffer(new unsigned int[6]{
                                 0, 1, 2,
                                 2, 3, 0
                             }, 6);

    VertexArray::BufferLayout layout;
    layout.push(VertexArray::BufferLayout::LayoutObject{
        2,
        GL_FLOAT,
        GL_FALSE
    });
    m_vao.setLayout(m_vertexBuffer, layout , 0);

    m_shader = Shader("basic.glsl");
    m_shader.addUniform("u_coef");

    m_shader.setUniform("u_coef", glUniform1f, 1.2f);
}


void App::loop() {
    while (!glfwWindowShouldClose(m_window)) {
        glCall(glClear(GL_COLOR_BUFFER_BIT));

        m_indexBuffer.bind();
        glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));


        glfwSwapBuffers(m_window);

        glfwPollEvents();

        m_deltaTime = glfwGetTime() - m_lastTime;
        m_lastTime = glfwGetTime();
    }
}

App::~App() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}