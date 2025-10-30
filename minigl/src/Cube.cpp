//
// Created by kolyne on 10/30/25.
//

#include <iostream>
#include <glad/gl.h>
#include <minigl/Cube.h>

#include <minigl/Color.h>
#include <minigl/Texture.h>

mngl::Cube::Cube(Color _mainColor) : m_vertices{
                                         -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                                         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
                                         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                                         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                                         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                                         -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

                                         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                                         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                                         0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                                         0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                                         -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
                                         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

                                         -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                                         -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                                         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                                         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                                         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                                         -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                                         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                                         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                                         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                                         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                                         0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                                         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                                         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                                         0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
                                         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                                         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                                         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                                         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                                         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                                         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                                         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                                         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                                         -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
                                         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
                                     }, m_mainColor(_mainColor), m_texture(nullptr)
{
    m_vao.Create(m_vertices, 36, sizeof(float) * 5, GL_STATIC_DRAW);
    m_vao.SetAttrib(0, 3, GL_FLOAT, GL_FALSE, 0);
    m_vao.SetAttrib(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
}

void mngl::Cube::SetColor(Color _mainColor)
{
    m_mainColor = _mainColor;
}

void mngl::Cube::SetTexture(Texture* _texture)
{
    m_texture = _texture;
}

void mngl::Cube::Draw(const Window& _window, RenderState _state) const
{
    _state.shader->SetMatrix4("model", _state.transform * GetTransform());
    _state.shader->SetColor("MainColor", m_mainColor);
    _state.shader->Use();
    if (m_texture != nullptr)
    {
        _state.shader->SetTexture("Texture", *m_texture);
        m_texture->Use();
        m_vao.Draw();
        m_texture->Shutdown();
    }
    else
    {
        m_vao.Draw();
    }
    _state.shader->Shutdown();
}
