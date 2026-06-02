#include "VertexArray.h"

#include "Helper.h"
#include "glad/glad.h"


VertexArray::VertexArray(bool) {
    glCall(glGenVertexArrays(1, &m_vaoID));
    bind();
}

VertexArray::VertexArray(const VertexArray &&obj) noexcept {
    m_vaoID = obj.m_vaoID;

    delete &obj;
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
