#version 330 core
out vec4 FragColor;
in vec2 TexCoor;

uniform sampler2D Texture;
uniform vec4 MainColor;

void main()
{
    ivec2 decalSize = textureSize(Texture, 0);

    if (decalSize != ivec2(1, 1))
        FragColor = MainColor * texture(Texture, TexCoor);
    else
        FragColor = MainColor;
}