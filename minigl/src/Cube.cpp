//
// Created by kolyne on 10/30/25.
//

#include <iostream>
#include <glad/gl.h>
#include <minigl/Cube.h>

#include <minigl/Texture.h>

#include "minigl/Utils.h"

mngl::Cube::Cube() : m_vertices{
                                         glm::vec3(-1, -1, -1),
                                         glm::vec3(1, -1, -1),
                                         glm::vec3(1, 1, -1),
                                         glm::vec3(-1, 1, -1),
                                         glm::vec3(-1, -1, 1),
                                         glm::vec3(1, -1, 1),
                                         glm::vec3(1, 1, 1),
                                         glm::vec3(-1, 1, 1)
                                     }, m_texCoords{
                                         glm::vec2(0, 0),
                                         glm::vec2(1, 0),
                                         glm::vec2(1, 1),
                                         glm::vec2(0, 1)
                                     }, m_normals{
                                         glm::vec3(0, 0, 1),
                                         glm::vec3(1, 0, 0),
                                         glm::vec3(0, 0, -1),
                                         glm::vec3(-1, 0, 0),
                                         glm::vec3(0, 1, 0),
                                         glm::vec3(0, -1, 0)
                                     }
                                     , m_indices{

                                         0, 1, 3, 3, 1, 2,
                                         1, 5, 2, 2, 5, 6,
                                         5, 4, 6, 6, 4, 7,
                                         4, 0, 7, 7, 0, 3,
                                         3, 2, 7, 7, 2, 6,
                                         4, 5, 0, 0, 5, 1
                                     }, m_texInds{
                                         0, 1, 3, 3, 1, 2
                                     }
{
    for (int i = 0; i < 36; i++) {
        m_allVertices[i * 3 + 0] = m_vertices[m_indices[i]].x;
        m_allVertices[i * 3 + 1] = m_vertices[m_indices[i]].y;
        m_allVertices[i * 3 + 2] = m_vertices[m_indices[i]].z;
    }
    for (int i = 0; i < 36; i++) {
        m_allVertices[36*3+i * 2 + 0] = m_texCoords[m_texInds[i % 6]].x;
        m_allVertices[36*3+i * 2 + 1] = m_texCoords[m_texInds[i % 6]].y;
    }
    // for (int i = 0; i < 36; i++) {
    //     m_allVertices[36*5+i * 3 + 0] = m_normals[m_indices[i / 6]].x;
    //     m_allVertices[36*5+i * 3 + 1] = m_normals[m_indices[i / 6]].y;
    //     m_allVertices[36*5+i * 3 + 2] = m_normals[m_indices[i / 6]].z;
    // }
    Utils::GenerateBasicNormal(m_allVertices, 36, 3, &m_allVertices[36 * 5]);

    m_vao.Create(m_allVertices, 36, (36 * 8) * sizeof(float), GL_STATIC_DRAW);
    m_vao.SetAttrib(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    m_vao.SetAttrib(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 36 * 3 * sizeof(float));
    m_vao.SetAttrib(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 36 * 5 * sizeof(float));
}


mngl::Cube::Cube(Material _mainMaterial) : Cube() {
    SetMaterial(_mainMaterial);
}

void mngl::Cube::SetMaterial(Material _mainMaterial) {
    m_mainMaterial = _mainMaterial;
}

mngl::Material mngl::Cube::GetMaterial() const {
    return m_mainMaterial;
}

void mngl::Cube::Draw(const Window& _window, RenderState _state) const
{
    _state.shader->SetMatrix4("_model", _state.transform * GetTransform());
    m_mainMaterial.Use();
    _state.shader->SetMaterial("_mainMaterial", m_mainMaterial);
    _state.shader->Use();
    m_vao.Draw();
    _state.shader->Shutdown();
    m_mainMaterial.Shutdown();
}
