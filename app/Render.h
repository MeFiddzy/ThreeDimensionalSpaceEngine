#pragma once
#include <vector>

#include "Buffer.h"
#include "Helper.h"
#include "ShaderMethods.h"
#include "VertexArray.h"
#include "../helper/HelperVectors.h"

template<typename T>
concept HasBufferLayout = requires {
    { T::bufferLayout } -> std::convertible_to<VertexArray::BufferLayout>;
};

template<typename T>
class Render {
public:
    Render() = default;
    Render(const Render&) = default;
    Render &operator=(const Render&) = default;
    Render(Render&&) = default;
    Render &operator=(Render&&) = default;

    Shader &shader() {
        return m_shader;
    }

    void addShader(Shader &shader) {
        m_shader = std::move(shader);
    }

    void addShader(Shader &&shader) {
        m_shader = std::move(shader);
    }

    void addTriangle(const Triangle<UInt> &triangle) {
        m_triangles.push_back(triangle);
    }

    void addVertex(const T &vertex) {
        m_vertices.emplace_back(vertex);
    }

    void genIndexBuffer(const GLenum usage) {
        m_indexBuffer = Buffer(GL_ELEMENT_ARRAY_BUFFER, usage);
        std::vector<UInt> data;
        data.reserve(m_triangles.size() * 3);

        for (const auto &[v1, v2, v3] : m_triangles) {
            data.push_back(v1);
            data.push_back(v2);
            data.push_back(v3);
        }

        if (!data.empty()) {
            m_indexBuffer.loadBuffer<UInt>(data.data(), data.size());
        }
    }

    void genVertexArray(const GLenum usage) {
        m_vao = VertexArray(true);

        static_assert(HasBufferLayout<T>, "Vertex class must have a buffer layout static variable.");

        const VertexArray::BufferLayout &bufferLayout = T::bufferLayout;
        const std::size_t count = bufferLayout.getVector().size();

        m_vertexBuffers.clear();
        m_vertexBuffers.reserve(count);
        for (std::size_t i = 0; i < count; i++) {
            m_vertexBuffers.emplace_back(GL_ARRAY_BUFFER, usage);
        }

        T::loadComponents(m_vertexBuffers, m_vertices);

        for (std::size_t i = 0; i < count; i++) {
            m_vao.setLayout(m_vertexBuffers[i], bufferLayout, static_cast<UInt>(i));
        }
    }

    void draw() const {
        m_vao.bind();
        m_shader.use();
        m_indexBuffer.bind();
        glCall(glDrawElements(GL_TRIANGLES, 3 * m_triangles.size(), GL_UNSIGNED_INT, nullptr));
    }

    void genBuffers(const GLenum usage) {
        genIndexBuffer(usage);
        genVertexArray(usage);
    }

    std::vector<Buffer> &getVertexBuffers() {
        return m_vertexBuffers;
    }

    Buffer &getIndexBuffer() {
        return m_indexBuffer;
    }

    VertexArray &getVAO() {
        return m_vao;
    }
private:
    std::vector<Buffer> m_vertexBuffers;
    Buffer m_indexBuffer;

    VertexArray m_vao;

    Shader m_shader;

    std::vector<T> m_vertices;
    std::vector<Triangle<UInt>> m_triangles;
};