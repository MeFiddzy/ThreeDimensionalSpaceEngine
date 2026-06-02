#pragma once
#include "Helper.h"
#include "glad/glad.h"

template<typename T>
class Buffer {
protected:
    unsigned int m_bufferID{};
    GLenum m_target{}, m_usage{};
public:
    Buffer() = default;

    Buffer(Buffer &obj) {
        *this = Buffer(obj.m_target, m_usage);
    }

    Buffer(const Buffer &&obj) noexcept {
        m_bufferID = obj.m_bufferID;
        m_target = obj.m_target;
        m_usage = obj.m_usage;

        delete &obj;
    }

    ~Buffer() {
        glCall(glDeleteBuffers(1, &m_bufferID));
    }

    Buffer &operator=(Buffer &&other) noexcept {
        if (this == &other) {
            return *this;
        }

        m_bufferID = other.m_bufferID;
        m_target = other.m_target;
        m_usage = other.m_usage;
        return *this;
    }

    explicit Buffer(const GLenum target, const GLenum usage) {
        m_target = target;
        m_usage = usage;

        glCall(glGenBuffers(1, &m_bufferID));
    }

    void loadBuffer(T data[], const unsigned int dataCount) const {
        glCall(glBindBuffer(m_target, m_bufferID));
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

template<typename T>
class BufferArray : public Buffer<T>{
    unsigned int m_size;
public:
    explicit BufferArray(const GLenum target, const GLenum usage, const unsigned int size) : Buffer<T>() {
        m_size = size;
        this->m_target = target;
        this->m_usage = usage;

        glCall(glGenBuffers(size, &(this->m_bufferID)));
    }

    ~BufferArray() {
        glCall(glDeleteBuffers(m_size, this->m_bufferID));
    }
};
