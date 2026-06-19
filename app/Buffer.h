#pragma once
#include "Helper.h"
#include "glad/glad.h"

class Buffer {
protected:
    unsigned int m_bufferID{};
    GLenum m_target{}, m_usage{};

    void release() {
        if (m_bufferID != 0) {
            glCall(glDeleteBuffers(1, &m_bufferID));
            m_bufferID = 0;
        }
    }

public:
    Buffer() = default;

    explicit Buffer(const GLenum target, const GLenum usage)
        : m_target(target), m_usage(usage) {
        glCall(glGenBuffers(1, &m_bufferID));
    }

    Buffer(const Buffer &) = delete;
    Buffer &operator=(const Buffer &) = delete;

    Buffer(Buffer &&obj) noexcept
        : m_bufferID(obj.m_bufferID), m_target(obj.m_target), m_usage(obj.m_usage) {
        obj.m_bufferID = 0;
    }

    Buffer &operator=(Buffer &&other) noexcept {
        if (this == &other) {
            return *this;
        }

        release();

        m_bufferID = other.m_bufferID;
        m_target = other.m_target;
        m_usage = other.m_usage;

        other.m_bufferID = 0;

        return *this;
    }

    ~Buffer() {
        release();
    }

    template<typename T>
    void loadBuffer(T data[], const unsigned int dataCount) {
        bind();
        glCall(glBufferData(m_target, sizeof(T) * dataCount, data, m_usage));
    }

    void bind() const {
        glCall(glBindBuffer(m_target, m_bufferID));
    }

    void unBind() const {
        glCall(glBindBuffer(m_target, 0));
    }

    [[nodiscard]]
    unsigned int getBuffer() const {
        return m_bufferID;
    }
};