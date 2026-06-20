#include "TexturedShape.h"

TexturedShape::TexturedShape(const Vec2 &pos, const Vec2 &texturePos) {
    this->pos = pos;
    this->texturePos = texturePos;
}

void TexturedShape::loadComponents(std::vector<Buffer> &buffers, const std::vector<TexturedShape> &vertcies) {
    auto dataP = std::vector<float>();
    auto dataT = std::vector<float>();

    UInt sizeP = 0;
    UInt sizeT = 0;

    for (const auto &vertex : vertcies) {
        dataP.emplace_back(vertex.pos.x);
        dataP.emplace_back(vertex.pos.y);

        dataT.emplace_back(vertex.texturePos.x);
        dataT.emplace_back(vertex.texturePos.y);

        sizeP += 2;
        sizeT += 2;
    }

    buffers[0].loadBuffer(&dataP[0], sizeP);
    buffers[1].loadBuffer(&dataT[0], sizeT);
}

VertexArray::BufferLayout TexturedShape::bufferLayout = VertexArray::BufferLayout(LO(2, GL_FLOAT, GL_FALSE), LO(2, GL_FLOAT, GL_FALSE));

