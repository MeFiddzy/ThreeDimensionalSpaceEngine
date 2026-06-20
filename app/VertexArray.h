#pragma once
#include <vector>

#include "Buffer.h"
#include "Helper.h"

class VertexArray {
public:
    class BufferLayout {
    public:
        struct LayoutObject {
            unsigned int size;
            GLenum type;
            bool normalized;
        };

        BufferLayout() = default;

        BufferLayout(const BufferLayout& obj)
            : m_layout(obj.m_layout) {}

        BufferLayout(BufferLayout&& obj) noexcept
            : m_layout(std::move(obj.m_layout)) {}

        explicit BufferLayout(std::vector<LayoutObject> objs)
            : m_layout(std::move(objs)) {}

        template<typename... Args>
        explicit BufferLayout(Args&&... objs) {
            m_layout.reserve(sizeof...(objs));
            (m_layout.push_back(std::forward<Args>(objs)), ...);
        }

        BufferLayout& operator=(const BufferLayout& obj) {
            if (this != &obj)
                m_layout = obj.m_layout;
            return *this;
        }

        BufferLayout& operator=(BufferLayout&& obj) noexcept {
            if (this != &obj)
                m_layout = std::move(obj.m_layout);
            return *this;
        }

    private:
        std::vector<LayoutObject> m_layout;

    public:
        void push(const LayoutObject& obj) {
            m_layout.push_back(obj);
        }
        void push(LayoutObject&& obj) {
            m_layout.push_back(std::move(obj));
        }

        [[nodiscard]]
        const std::vector<LayoutObject>& getVector() const {
            return m_layout;
        }
    };

    VertexArray() = default;

    explicit VertexArray(bool);

    VertexArray(VertexArray &&obj) noexcept;

    VertexArray &operator=(VertexArray &&other) noexcept {
        if (this == &other) {
            return *this;
        }

        m_vaoID = other.m_vaoID;
        other.m_vaoID = 0;

        return *this;
    }

    void setLayout(const Buffer &buffer, const BufferLayout &layout, UInt index) const;

    void bind() const;

    void enableVertexAttribArray(unsigned int index) const;
    void disableVertexAttribArray(unsigned int index) const;

    static void unBind();

    ~VertexArray() {
        if (!m_vaoID)
            return;

        glCall(glDeleteVertexArrays(1, &m_vaoID));
    }
private:
    unsigned int m_vaoID{};
};