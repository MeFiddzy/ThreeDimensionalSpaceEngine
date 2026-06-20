#include "VertexArray.h"

#include "Helper.h"
#include "glad/glad.h"

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
        layoutObj.size * glSize(layoutObj.type),
        nullptr
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