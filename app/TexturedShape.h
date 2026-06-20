#pragma once
#include "../helper/HelperVectors.h"

struct TexturedShape {
    Vec2 pos{};
    Vec2 texturePos{};

    TexturedShape(const Vec2 &pos, const Vec2 &texturePos);

    static void loadComponents(std::vector<Buffer> &buffers, const std::vector<TexturedShape> &vertcies);

    static VertexArray::BufferLayout bufferLayout;
};
