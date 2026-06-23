#pragma once
#include "../helper/HelperVectors.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

struct Transform {
    Vec3 pos{0., 0., 0.};
    Vec3 scale{1., 1., 1.};
    Quaternion rotation{1., 0, 0, 0};

    Transform() = default;

    Transform(const Vec3 &pos, const Vec3 &scale, const Quaternion &rotation) {
        this->pos = pos;
        this->scale = scale;
        this->rotation = rotation;
    }

    glm::mat4 toModelMatrix() const {
        glm::mat4 mat(1.);

        mat = glm::translate(mat, pos.toGLM());
        mat *= glm::mat4_cast(rotation.toGLM());
        mat = glm::scale(mat, scale.toGLM());

        return mat;
    }
};
