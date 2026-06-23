#pragma once
#include "Render.h"
#include "TexturedShape.h"

class ShapeGeneration {
public:
    static Render<TexturedShape> *connectPoints2D(const std::vector<Vec2> &points) {
        auto *render = new Render<TexturedShape>;

        for (UInt i = 1; i < points.size() - 1; i++) {
            render->addTriangle(Triangle<UInt>(0, i, i + 1));
        }

        float minX = points[0].x, maxX = points[0].x;
        float minY = points[0].y, maxY = points[0].y;
        for (const Vec2 &point : points) {
            minX = std::min(minX, point.x);
            maxX = std::max(maxX, point.x);
            minY = std::min(minY, point.y);
            maxY = std::max(maxY, point.y);
        }

        const float dX = maxX - minX;
        const float dY = maxY - minY;

        for (UInt i = 0; i < points.size(); i++) {
            render->addVertex(TexturedShape(
                points[i],
                Vec2{
                    dX != 0.f ? (points[i].x - minX) / dX : 0.f,
                    dY != 0.f ? (points[i].y - minY) / dY : 0.f
                }
            ));
        }

        render->genBuffers(GL_STATIC_DRAW);
        return render;
    }
};
