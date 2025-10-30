//
// Created by kolyne on 10/30/25.
//

#ifndef MINIGL_CUBE_H
#define MINIGL_CUBE_H
#include "Color.h"
#include "Drawable.h"
#include "Transformable.h"
#include "VAO.h"

namespace mngl
{
    class Cube : public Transformable, public Drawable
    {
        VAO m_vao;
        float m_vertices[36*5];
        Texture* m_texture;
        Color m_mainColor;

    public:
        Cube(Color _mainColor = Color::White);
        void SetColor(Color _mainColor);
        void SetTexture(Texture* _texture);
        void Draw(const Window& _window, RenderState _state) const override;
    };
} // mngl

#endif //MINIGL_CUBE_H