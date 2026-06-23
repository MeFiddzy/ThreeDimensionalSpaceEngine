#pragma once
#include "Render.h"
#include "Transform.h"

template<typename T>
class Render3D : public Render<T> {
private:
    Transform m_transform;
public:
    Render3D(Render<T> &&render, const Transform &transform) : Render<T>(render), m_transform(transform) {}
    Render3D(const Render3D &other) = default;
    Render3D(Render3D &&other) noexcept {
        *this = other;
    }
    Render3D &operator=(Render3D &&other) noexcept {
        if (this == &other) {
            return *this;
        }

        this->m_transform = other.m_transform;
        this->m_shader = other.m_shader;
        this->m_material = other.m_material;
        this->m_shaderType = other.m_shaderType;
        this->m_indexBuffer = other.m_indexBuffer;
        this->m_vertexBuffers = other.m_vertexBuffers;
        this->m_vertices = other.m_vertices;
        this->m_vao = other.m_vao;
        this->m_triangles = other.m_triangles;

        other.m_indexBuffer = Buffer();
        for (auto &buff : other.m_vertexBuffers) {
            buff = Buffer();
        }
        other.m_shader = Shader();
        other.m_vao = VertexArray();

        return *this;
    }
    Render3D &operator=(const Render3D &other) = default;

    void setTransform(const Transform &transform) {
            m_transform = transform;
    }

    Transform &getTransform() {
        return m_transform;
    }
};
