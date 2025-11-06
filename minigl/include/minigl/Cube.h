//
// Created by kolyne on 10/30/25.
//

#ifndef MINIGL_CUBE_H
#define MINIGL_CUBE_H
#include "Drawable.h"
#include "Material.h"
#include "Transformable.h"
#include "VAO.h"

namespace mngl
{
    class Cube : public Transformable, public Drawable
    {
        VAO m_vao;
        glm::vec3 m_vertices[8];
        glm::vec2 m_texCoords[4];
        glm::vec3 m_normals[6];

        int m_indices[6 * 6];
        int m_texInds[6];

        float m_allVertices[36 * 8]{};

        Material m_mainMaterial;

    public:
        Cube();
        Cube(Material _mainMaterial);
        void SetMaterial(Material _mainMaterial);
        Material GetMaterial() const;
        void Draw(const Window& _window, RenderState _state) const override;
    };
} // mngl

#endif //MINIGL_CUBE_H
