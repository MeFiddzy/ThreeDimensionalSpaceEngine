#pragma once

#include <iostream>
#include "glad/glad.h"

inline void clearErrors(const char *function = nullptr, const char *file = nullptr, const int line = -1, bool print = false) {
    while (const auto err = glGetError()) {
        if (print && function && file && line) {
            std::cout << "[OPENGL_ERROR] (" << function << " " << file << ":" << line << ") Error Code:" << err << '\n';
            __debugbreak();
        }
    }
}

using GLType = unsigned int;
using UInt = unsigned int;
using ULLong = unsigned long long;

#define glCall(x) clearErrors(); x; clearErrors(#x, __FILE__, __LINE__, true);