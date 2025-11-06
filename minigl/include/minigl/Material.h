//
// Created by Coline Constantinian on 06/11/2025.
//

#ifndef MINIGL_MATERIAL_H
#define MINIGL_MATERIAL_H

#include "Color.h"
#include "Texture.h"

namespace mngl {
    class Material {
        Color m_ambientColor;
        Color m_diffuseColor;
        Texture* m_diffuseTexture;
        Color m_specularColor;
        Texture* m_specularTexture;
        float m_shininess;

    public:
        Material();
        void SetAmbientColor(Color _ambientColor);
        void SetDiffuseColor(Color _diffuseColor);
        void SetDiffuseTexture(Texture* _diffuseTexture);
        void SetSpecularColor(Color _specularColor);
        void SetSpecularTexture(Texture* _specularTexture);
        void SetShininess(float _shininess);

        Color GetAmbientColor() const;
        Color GetDiffuseColor() const;
        Texture* GetDiffuseTexture() const;
        Color GetSpecularColor() const;
        Texture* GetSpecularTexture() const;
        float GetShininess() const;

        void Use() const;
        void Shutdown() const;

    friend Shader;
    };
} // mngl

#endif //MINIGL_MATERIAL_H