#pragma once
#include "Render.h"
#include "GLFW/glfw3.h"

template<typename T>
class Renderer {
public:
    void addRender(const Render<T> *render) {
        m_renders.emplace_back(render);
    }

    [[nodiscard]]
    Render<T> *getRender(const UInt index) {
        return m_renders[index];
    }

    [[nodiscard("Pointer will escape the class. Delete it or use save it to prevent a memory leak!")]]
    Render<T> *removeRender(const UInt index) {
        Render<T> *ptr = const_cast<Render<T> *>(m_renders[index]);

        m_renders[index] = nullptr;
        m_renders.erase(m_renders.begin() + index);

        return ptr;
    }

    void render(GLFWwindow* window) {
        glCall(glClear(GL_COLOR_BUFFER_BIT));

        for (const Render<T> *render : m_renders) {
            render->draw();
        }

        glCall(glfwSwapBuffers(window));

        glCall(glfwPollEvents());

   }
private:
    std::vector<const Render<T>*> m_renders;
};
