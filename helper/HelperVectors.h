#pragma once

#include <any>

#include "../app/Helper.h"
#include "../app/VertexArray.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

struct Vec3 {
    Vec3() = default;

    Vec3(const float x, const float y, const float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vec3 &operator=(const Vec3 &other) {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;

        return *this;
    }

    Vec3 &operator+(const Vec3 &other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;

        return *this;
    }

    Vec3 &operator-(const Vec3 &other) {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;

        return *this;
    }

    Vec3 &operator*(const float other) {
        this->x *= other;
        this->y *= other;
        this->z *= other;

        return *this;
    }

    glm::vec3 toGLM() const {
        return glm::vec3(x, y, z);
    }

    float x, y, z;

    static void loadComponents(std::vector<Buffer> &buffers, const std::vector<Vec3> &vertcies);
    static VertexArray::BufferLayout bufferLayout;
};

inline VertexArray::BufferLayout Vec3::bufferLayout = VertexArray::BufferLayout(LO(3, GL_FLOAT, GL_FALSE));

inline void Vec3::loadComponents(std::vector<Buffer> &buffers, const std::vector<Vec3> &vertcies) {
    auto data = std::vector<float>();
    UInt size = 0;

    for (const auto &vertex : vertcies) {
        data.emplace_back(vertex.x);
        data.emplace_back(vertex.y);
        data.emplace_back(vertex.z);

        size += 3;
    }

    buffers[0].loadBuffer(&data[0], size);
}

struct Vec2 {
    Vec2() = default;

    Vec2(const float x, const float y) {
        this->x = x;
        this->y = y;
    }

    float x, y;

    static void loadComponents(std::vector<Buffer> &buffers, const std::vector<Vec2> &vertcies);

    Vec2 operator*(const float s) const {
        return Vec2(s * x, s * y);
    }

    Vec2 operator/(const float s) const {
        return Vec2(x / s, y / s);
    }

    static VertexArray::BufferLayout bufferLayout;
};

inline VertexArray::BufferLayout Vec2::bufferLayout = VertexArray::BufferLayout(LO(2, GL_FLOAT, GL_FALSE));

inline void Vec2::loadComponents(std::vector<Buffer> &buffers, const std::vector<Vec2> &vertcies) {
    auto data = std::vector<float>();
    UInt size = 0;

    for (const auto &vertex : vertcies) {
        data.emplace_back(vertex.x);
        data.emplace_back(vertex.y);

        size += 2;
    }

    buffers[0].loadBuffer(&data[0], size);
}

struct Quaternion {
    float w, x, y, z;

    Quaternion(const glm::quat &q) {
        w = q.w;
        x = q.x;
        y = q.y;
        z = q.z;
    }

    Quaternion(float w, float x, float y, float z) {
        this->w = w;
        this->x = x;
        this->y = y;
        this->z = z;
    }

    glm::quat toGLM() const {
        return glm::quat(w, x, y, z);
    }

    Quaternion &operator+(const Quaternion &other) const {
        Quaternion q = Quaternion(
            w + other.w,
            x + other.x,
            y + other.y,
            z + other.z
        );

        return q;
    }
};