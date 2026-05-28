#pragma once

struct Vec3 {
    Vec3();

    Vec3(const float x, const float y, const float z) {
        this->x = x;
        this->y = y;
        this->z = z;
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