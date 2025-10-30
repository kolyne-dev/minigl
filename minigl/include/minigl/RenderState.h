//
// Created by kolyne on 10/30/25.
//

#ifndef MINIGL_RENDERSTATE_H
#define MINIGL_RENDERSTATE_H
#include <glm/glm.hpp>

#include "Shader.h"

namespace mngl
{
    struct RenderState
    {
        glm::mat4 transform;
        Shader* shader;
    };
}

#endif //MINIGL_RENDERSTATE_H