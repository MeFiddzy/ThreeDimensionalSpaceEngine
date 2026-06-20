#include "Texture.h"

#include "stb_image.h"

#define textureSlot(x) (GL_TEXTURE0 + x)
#define textureSlotReverse(x) (x - GL_TEXTURE0)

Texture::~Texture() {
    glCall(glDeleteTextures(1, &m_rendererID));
}

Texture::Texture(const std::string &path) : m_filePath(path){
    stbi_set_flip_vertically_on_load(1);
    m_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);

    glCall(glGenTextures(1, &m_rendererID));
    bind();

    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer));

    unBind();

    if (m_buffer) {
        stbi_image_free(m_buffer);
    }
}

void Texture::bind(const UInt slot) const {
    glCall(glActiveTexture(textureSlot(slot)));
    glCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::unBind() const {
    glCall(glBindTexture(GL_TEXTURE_2D, 0));
}
