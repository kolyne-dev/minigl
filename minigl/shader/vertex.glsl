#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoor;
layout (location = 2) in vec3 aNormal;

struct Light {
    vec3 position;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

out VERTEX_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    Light MainLight;
} v;

uniform mat4 _projection;
uniform mat4 _view;
uniform mat4 _model;
uniform Light _mainLight;

void main()
{
    gl_Position = _projection * _view * _model * vec4(aPos, 1.0);
    v.TexCoords = vec2(aTexCoor.x, 1-aTexCoor.y);
    v.FragPos = vec3(_view * _model * vec4(aPos, 1.0));
    v.Normal = vec3(transpose(inverse(_view * _model)) * vec4(aNormal, 1.0));
    v.MainLight = _mainLight;
    v.MainLight.position = vec3(_view * vec4(_mainLight.position.x, _mainLight.position.y, -_mainLight.position.z, 1));
}