#pragma once
#include "Helper.h"

class Texture {
private:
    std::string m_filePath;
    unsigned char* m_buffer{nullptr};
    int m_width{0}, m_height{0}, m_BPP{0};

    UInt m_rendererID{0};
public:
    ~Texture();
    Texture() = default;
    explicit Texture(const std::string &path);

    void bind(UInt slot = 0) const;
    void unBind() const;

    [[nodiscard]] auto getWidth() const { return m_width; }
    [[nodiscard]] auto getHeight() const { return m_height; }
    [[nodiscard]] auto getBPP()const { return m_BPP; }
};
