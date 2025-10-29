//
// Created by kolyne on 10/29/25.
//

#include <glad/gl.h>
#include <ext/stb_image.h>
#include <minigl/Texture.h>
#include <iostream>

mngl::Texture::Texture(const std::string& _path, bool _mipmap, bool _unpackAlignment) : m_height(0), m_nbChannel(0), m_textureID(0), m_width(0)
{

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    unsigned char* data = stbi_load(_path.c_str(), &m_width, &m_height, &m_nbChannel, 0);

    if (data)
    {
        if (_unpackAlignment)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        }
        if (m_nbChannel == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        if (m_nbChannel == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        if (_mipmap)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    } else
    {
        std::cout << "stbi_load: Can't load image." << std::endl;
    }

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void mngl::Texture::Use()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void mngl::Texture::Shutdown()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
