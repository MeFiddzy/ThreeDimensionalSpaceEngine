#pragma once
#include <vector>

#include "Buffer.h"
#include "Helper.h"

class VertexArray {
public:
    class BufferLayout {
    public:
        BufferLayout() = default;
        BufferLayout(BufferLayout &obj) {
            m_layout = std::vector(obj.m_layout);
        }
        BufferLayout(const BufferLayout &&obj) noexcept {
            m_layout = std::vector(std::move(obj.m_layout));

            delete &obj;
        }

        struct LayoutObject {
            unsigned int size;
            GLType type;
            bool normalized;
        };
    private:
        std::vector<LayoutObject> m_layout;
    public:
        void push(const LayoutObject &obj) { m_layout.push_back(obj); }

        auto getVector() const { return m_layout; }
    };

    VertexArray() = default;

    explicit VertexArray(bool);

    VertexArray(const VertexArray &&obj) noexcept;

    VertexArray &operator=(VertexArray &&other) {
        if (this == &other) {
            return *this;
        }

        m_vaoID = other.m_vaoID;
        other.m_vaoID = 0;
    }

    template<typename T>
    void setLayout(const Buffer<T> &buffer, BufferLayout &layout, const unsigned int index) const {
        bind();
        buffer.bind();

        UInt stride = 0;
        for (const auto& obj : layout.getVector())
            stride += obj.size * sizeof(T);

        enableVertexAttribArray(index);

        ULLong pointer = 0;

        for (UInt i = 0; i < layout.getVector().size(); i++) {
            glCall(glEnableVertexAttribArray(index + i));
            glCall(glVertexAttribPointer(i, layout.getVector()[i].size, layout.getVector()[i].type, layout.getVector()[i].normalized, stride, reinterpret_cast<void*>(pointer)));

            pointer += layout.getVector()[i].size * sizeof(T);
        }
    }

    void bind() const;

    void enableVertexAttribArray(unsigned int index) const;
    void disableVertexAttribArray(unsigned int index) const;

    static void unBind();
private:
    unsigned int m_vaoID{};
};