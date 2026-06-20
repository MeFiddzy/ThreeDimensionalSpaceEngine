#include "ShaderMethods.h"

#include <fstream>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <string>

#include "glad/glad.h"


unsigned int ShaderMethods::createShader(const std::string &vertexShader, const std::string &fragmentShader) {
    const unsigned int program = glCreateProgram();

    const unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    const unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    int linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE) {
        int len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
        char *err = static_cast<char*>(alloca(len * sizeof(char)));
        glGetProgramInfoLog(program, len, &len, err);
        std::cout << "[SHADER_LINK_ERROR] " << err << '\n';
    }
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int ShaderMethods::compileShader(const std::string &source, unsigned int type) {
    const unsigned int id = glCreateShader(type);
    const char *src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int res;
    glGetShaderiv(id, GL_COMPILE_STATUS, &res);

    if (res == GL_FALSE) {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

        char *err = static_cast<char*>(alloca(len * sizeof(char)));
        glGetShaderInfoLog(id, len, &len, err);

        std::cout << "[" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "_SHADER_ERROR] " << err << '\n';

        glDeleteShader(id);

        throw std::exception("Shader compilation fail!");
    }

    return id;
}

ShaderMethods::ShaderSource ShaderMethods::parseShader(const std::string &path) {
    std::fstream fin("resources\\shaders\\" + path);
    std::string line;

    std::stringstream ss[2];

    ShaderType type = ShaderType::NONE;

    while (getline(fin, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[static_cast<unsigned int>(type)] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

Shader::Shader(Shader &&obj) noexcept {
    m_shaderID = obj.m_shaderID;
    m_shaderPath = obj.m_shaderPath;
    m_uniforms = std::unordered_map(std::move(obj.m_uniforms));

    obj.m_shaderID = 0;
}
