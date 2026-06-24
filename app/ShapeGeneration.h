#pragma once
#include "Render.h"
#include "TexturedShape.h"

class ShapeGeneration {
public:
    ShapeGeneration() = delete;

    static Render3D<Vec3> *loadFromOBJ(const std::string &path) {
        Render3D<Vec3> *render = new Render3D(Render<Vec3>(), Transform());

        std::vector<Vec3> positions;
        std::unordered_map<UInt, UInt> cache;

        std::ifstream file(path);
        std::string line;

        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string tag;
            ss >> tag;

            if (tag == "v") {
                Vec3 p;
                ss >> p.x >> p.y >> p.z;
                positions.push_back(p);
            }
            else if (tag == "f") {
                std::vector<UInt> faceVerts;
                std::string token;
                while (ss >> token) {
                    size_t firstSlash = token.find('/');
                    UInt p = std::stoi(token.substr(0, firstSlash));
                    faceVerts.push_back(p);
                }

                for (size_t i = 1; i + 1 < faceVerts.size(); i++) {
                    UInt tri[3] = { faceVerts[0], faceVerts[i], faceVerts[i + 1] };
                    UInt outIndices[3];

                    for (int j = 0; j < 3; j++) {
                        UInt objIndex = tri[j];
                        auto it = cache.find(objIndex);

                        if (it != cache.end()) {
                            outIndices[j] = it->second;
                        } else {
                            UInt newIndex = static_cast<UInt>(render->getVertices().size());
                            render->addVertex(positions[objIndex - 1]);
                            cache[objIndex] = newIndex;
                            outIndices[j] = newIndex;
                        }
                    }

                    render->addTriangle(Triangle(outIndices[0], outIndices[1], outIndices[2]));
                }
            }
        }

        render->genBuffers(GL_STATIC_DRAW);

        return render;
    }

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
