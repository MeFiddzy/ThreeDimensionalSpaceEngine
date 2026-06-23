#pragma once
#include "Render.h"
#include "Transform.h"

template<typename T>
class Render3D : public Render<T> {
private:
    Transform m_transform;
public:
    Render3D() = default;
    Render3D(Render<T> &&render, const Transform &transform) : Render<T>(std::move(render)), m_transform(transform) {}
    Render3D(const Render3D &other) = default;
    Render3D(Render3D &&other) noexcept {
        *this = std::move(other);
    }
    Render3D &operator=(Render3D &&other) noexcept {
        if (this == &other) {
            return *this;
        }

        Render<T>::operator=(std::move(other));

        this->m_transform = other.m_transform;

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
