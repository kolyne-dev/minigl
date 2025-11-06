#version 330 core
out vec4 FragColor;

struct Light {
    vec3 position;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct Material {
    vec4 ambient;
    vec4 diffuse;
    sampler2D diffuseTexture;
    vec4 specular;
    sampler2D specularTexture;
    float shininess;
};

in VERTEX_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    Light MainLight;
} v;

uniform Material _mainMaterial;


void main()
{
    ivec2 decalSize = textureSize(_mainMaterial.diffuseTexture, 0);
    vec4 ambient = _mainMaterial.ambient * texture(_mainMaterial.diffuseTexture, v.TexCoords) * v.MainLight.ambient;

    vec3 norm = normalize(v.Normal);
    vec3 lightDir = normalize(v.MainLight.position - v.FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = (diff * _mainMaterial.diffuse * texture(_mainMaterial.diffuseTexture, v.TexCoords)) * v.MainLight.diffuse;

    vec3 viewDir = normalize(-v.FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), _mainMaterial.shininess);
    vec4 specular = (spec * _mainMaterial.specular * texture(_mainMaterial.specularTexture, v.TexCoords)) * v.MainLight.specular;

    FragColor = (ambient + diffuse + specular);
}