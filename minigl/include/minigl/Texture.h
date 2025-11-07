//
// Created by kolyne on 10/29/25.
//

#ifndef MINIGL_TEXTURE_H
#define MINIGL_TEXTURE_H

#include <string>
#include "Shader.h"

namespace mngl
{
    class Texture
    {
        unsigned int m_textureID;
        int m_width;
        int m_height;
        int m_nbChannel;

    public:
        Texture(const std::string& _path, bool _mipmap = true, bool _unpackAlignment = false);
        void Use(int _textureIndex = 0);
        void Shutdown(int _textureIndex = 0);

        static Texture* Default;

        friend Shader;
    };
} // mngl

#endif //MINIGL_TEXTURE_H
