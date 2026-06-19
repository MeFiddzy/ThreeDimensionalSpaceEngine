#pragma once
#include <vector>

#include "Buffer.h"
#include "Helper.h"
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

    void addTriangle(const Triangle<UInt> &triangle) {
        m_triangles.push_back(triangle);
    }

    void addVertex(const T &vertex) {
        m_vertices.emplace_back(vertex);
    }

    [[nodiscard]]
    Buffer getIndexBuffer(const GLenum usage) const {
        Buffer indexBuffer(GL_ELEMENT_ARRAY_BUFFER, usage);
        std::vector<UInt> data;
        data.reserve(m_triangles.size() * 3);

        for (const auto &[v1, v2, v3] : m_triangles) {
            data.push_back(v1);
            data.push_back(v2);
            data.push_back(v3);
        }

        if (!data.empty()) {
            indexBuffer.loadBuffer<UInt>(data.data(), data.size());
        }

        return indexBuffer;
    }

    [[nodiscard]]
    VertexArray getVertexArray(const GLenum usage) {
        VertexArray vao(true);

        static_assert(HasBufferLayout<T>, "Vertex class must have a buffer layout static variable.");

        const VertexArray::BufferLayout &bufferLayout = T::bufferLayout;
        const std::size_t count = bufferLayout.getVector().size();

        m_buffers.clear();
        m_buffers.reserve(count);
        for (std::size_t i = 0; i < count; i++) {
            m_buffers.emplace_back(GL_ARRAY_BUFFER, usage);
        }

        T::loadComponents(m_buffers, m_vertices);

        for (std::size_t i = 0; i < count; i++) {
            vao.setLayout(m_buffers[i], bufferLayout, static_cast<UInt>(i));
        }

        return vao;
    }

    std::vector<Buffer> &getVertexBuffers() {
        return m_buffers;
    }
private:
    std::vector<Buffer> m_buffers;
    std::vector<T> m_vertices;
    std::vector<Triangle<UInt>> m_triangles;
};