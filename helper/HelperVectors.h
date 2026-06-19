#pragma once

#include <any>

#include "../app/Helper.h"
#include "../app/VertexArray.h"
#include "../app/VertexArray.h"

struct Vec3 {
    Vec3();

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

    [[nodiscard]]
    float dotProd(const Vec3 other) const {
        return this->x * other.x +
            this->y * other.y +
            this->z * other.z;
    }

    [[nodiscard]]
    Vec3 crossProd(const Vec3 other) const {
        return Vec3(
            this->y * other.z - this->z * other.y,
            this->x * other.z - this->z * other.x,
            this->x * other.y - this->y * other.x
        );
    }

    [[nodiscard]]
    float absoluteValue() const {
        return std::sqrt(x * x + y * y + z * z);
    }
    float x, y, z;
};

struct Vec2 {
    Vec2();

    Vec2(const float x, const float y) {
        this->x = x;
        this->y = y;
    }

    float x, y;

    static void loadComponents(std::vector<Buffer> &buffers, const std::vector<Vec2> &vertcies);

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
