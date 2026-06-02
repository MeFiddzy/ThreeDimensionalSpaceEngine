#pragma once
#include <functional>
#include <string>
#include <unordered_map>

#include "Helper.h"

class ShaderMethods {
public:
    struct ShaderSource {
        std::string vertexSrc, fragmentSrc;
    };

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    static unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);

    static unsigned int compileShader(const std::string &source, unsigned int type);

    static ShaderSource parseShader(const std::string &path);

};

class Shader {
    unsigned int m_shaderID{};
    std::string m_shaderPath;

    std::unordered_map<std::string, unsigned int> m_uniforms;
public:
    Shader() = default;
    Shader(const Shader &&obj) noexcept;

    explicit Shader(const char *path) : m_shaderPath(std::string(path)) {
        const auto [vertexSrc, fragmentSrc] =  ShaderMethods::parseShader(path);
        m_shaderID = ShaderMethods::createShader(vertexSrc, fragmentSrc);

        glCall(glUseProgram(m_shaderID));
    }

    Shader &operator=(Shader &&other) {
        if (this == &other)
            return *this;

        m_shaderID = other.m_shaderID;
        m_shaderPath = other.m_shaderPath;
        m_uniforms = std::unordered_map(std::move(other.m_uniforms));

        return *this;
    }

    void use() const {
        glCall(glUseProgram(m_shaderID));
    }

    void addUniform(const std::string &name) {
        if (!m_uniforms.contains(name))
            glCall(m_uniforms[name] = glGetUniformLocation(m_shaderID, name.c_str()));
    }

    template<typename... Args, typename FuncT>
    void setUniform(const std::string &name, FuncT func, Args... args...) {
        glCall(func(m_uniforms[name], args...))
    }

    ~Shader() {
        glDeleteProgram(m_shaderID);
    }
};
