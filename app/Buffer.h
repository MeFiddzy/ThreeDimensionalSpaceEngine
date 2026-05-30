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

    ~Buffer() {
        glCall(glDeleteBuffers(1, &m_bufferID));
    }

    explicit Buffer(const GLenum target, const GLenum usage) {
        m_target = target;
        m_usage = usage;

        glCall(glGenBuffers(1, &m_bufferID));
    }

    void loadBuffer(T data[], const unsigned int dataCount) {
        glCall(glBindBuffer(m_target, m_bufferID));
        glCall(glBufferData(m_target, sizeof(T) * dataCount, data, m_usage));

        glCall(glBindBuffer(m_target, 0));
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
