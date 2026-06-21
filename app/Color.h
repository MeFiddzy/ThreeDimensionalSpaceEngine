#pragma once
#include "Helper.h"

struct Color {
    float r{}, g{}, b{}, a{};

    ~Color() = default;
    Color() = default;
    Color(const UInt r, const UInt g, const UInt b, const UInt a) {
       this->r = static_cast<float>(r) / 255.f;
       this->g = static_cast<float>(g) / 255.f;
       this->b = static_cast<float>(b) / 255.f;
       this->a = static_cast<float>(a) / 100.f;
    }
    Color(const float r, const float g, const float b, const float a) :
        r(r), g(g), b(b), a(a) {}

    Color(const Color &other) {
        *this = other;
    }
    Color(Color &&other) noexcept {
        *this = std::move(other);
    }
    Color &operator=(const Color &other) = default;
    Color &operator=(Color &&other) noexcept {
        if (this == &other) {
            return *this;
        }

        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;

        return *this;
    }

    bool operator==(const Color &other) const {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }
    bool operator!=(const Color &other) const {
        return !(*this == other);
    }

    float operator[](const UInt index) const {
        switch (index) {
            case 0:
                return r;
                break;
            case 1:
                return g;
                break;
            case 2:
                return b;
                break;
            case 3:
                return a;
                break;
            default:
                return -1.f;

        }
    }
};
