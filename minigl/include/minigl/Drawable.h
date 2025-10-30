//
// Created by kolyne on 10/30/25.
//

#ifndef MINIGL_DRAWABLE_H
#define MINIGL_DRAWABLE_H

#include "RenderState.h"

namespace mngl
{
    class Window;

    class Drawable
    {
    public:
        virtual ~Drawable() = default;
        virtual void Draw(const Window& _window, RenderState _state) const = 0;
    };
}

#endif //MINIGL_DRAWABLE_H