#include "VertexArray.h"

#include "Helper.h"
#include "glad/glad.h"


UInt VertexArray::BufferLayout::getStride() const {
    UInt stride = 0;

    for (const auto &layoutObj : m_layout) {
        stride += layoutObj.size * glSize(layoutObj.type);
    }

    return stride;
}

void *VertexArray::BufferLayout::getPointer(const UInt index) const {
    if (index > m_layout.size())
        return nullptr;

    UInt ptr = 0;

    for (UInt i = 0; i < index; i++) {
        ptr += m_layout[i].size * glSize(m_layout[i].type);
    }

    return reinterpret_cast<void *>(ptr);
}

VertexArray::VertexArray(bool) {
    glCall(glGenVertexArrays(1, &m_vaoID));
    bind();
}

VertexArray::VertexArray(VertexArray &&obj) noexcept
    : m_vaoID(obj.m_vaoID) {
    obj.m_vaoID = 0;
}

void VertexArray::setLayout(const Buffer &buffer, const BufferLayout &layout, const UInt index) const {
    bind();
    buffer.bind();

    const auto &layoutObj = layout.getVector()[index];

    enableVertexAttribArray(index);

    glCall(glVertexAttribPointer(
        index,
        layoutObj.size,
        layoutObj.type,
        layoutObj.normalized,
        layout.getStride(),
        layout.getPointer(index)
    ));
}

void VertexArray::bind() const {
    glCall(glBindVertexArray(m_vaoID));
}


void VertexArray::enableVertexAttribArray(const unsigned int index) const {
    bind();
    glCall(glEnableVertexAttribArray(index));
}


void VertexArray::disableVertexAttribArray(unsigned int index) const {
    bind();
    glCall(glDisableVertexAttribArray(index));
}


void VertexArray::unBind() {
    glCall(glBindVertexArray(0));
}