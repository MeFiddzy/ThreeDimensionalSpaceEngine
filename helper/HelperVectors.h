#pragma once

struct Vec3 {
    Vec3();

    Vec3(const float x, const float y, const float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vec3 &operator=(const Vec3 other) {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;

        return *this;
    }

    Vec3 &operator+(const Vec3 other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;

        return *this;
    }

    Vec3 &operator-(const Vec3 other) {
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



    float x, y, z;
};

struct Vec2 {
    Vec2();

    Vec2(const float x, const float y) {
        this->x = x;
        this->y = y;
    }

    float x, y;
};