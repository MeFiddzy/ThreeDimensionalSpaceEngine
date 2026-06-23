#pragma once
#include "Render.h"
#include "GLFW/glfw3.h"

template<typename T>
class Renderer {
public:
    void addRender(Render<T> *render) {
        m_renders.emplace_back(render);
    }

    [[nodiscard]]
    Render<T> *getRender(const UInt index) {
        return m_renders[index];
    }

    [[nodiscard]]
    auto getRenders() {
        return m_renders;
    }

    [[nodiscard("Pointer will escape the class. Delete it or use save it to prevent a memory leak!")]]
    Render<T> *removeRender(const UInt index) {
        Render<T> *ptr = (m_renders[index]);

        m_renders[index] = nullptr;
        m_renders.erase(m_renders.begin() + index);

        return ptr;
    }

    void render(GLFWwindow* window) {
        for (const Render<T> *render : m_renders) {
            if (render->getShaderType() == ShaderType::MATERIAL) {
                render->getMaterial()->onDraw();
            }

            render->draw();
        }

        glCall(glfwSwapBuffers(window));

        glCall(glfwPollEvents());

   }
private:
    std::vector<Render<T>*> m_renders;
};
