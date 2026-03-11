//
// Created by Coline Constantinian on 06/11/2025.
//

#ifndef MINIGL_LIGHT_H
#define MINIGL_LIGHT_H

#include "Color.h"
#include "Transformable.h"

namespace mngl {
    class Shader;

    class Light : public Transformable{
        Color m_ambientColor;
        Color m_diffuseColor;
        Color m_specularColor;

        float m_constant;
        float m_linear;
        float m_quadratic;

    public:
        Light();
        void SetAmbientColor(Color _ambientColor);
        void SetDiffuseColor(Color _diffuseColor);
        void SetSpecularColor(Color _specularColor);
        void SetConstantAttenuation(float _constant);
        void SetLinearAttenuation(float _constant);
        void SetQuadraticAttenuation(float _constant);

        Color GetAmbientColor();
        Color GetDiffuseColor();
        Color GetSpecularColor();
        float GetConstantAttenuation();
        float GetLinearAttenuation();
        float GetQuadraticAttenuation();

        friend Shader;
    };
} // mngl

#endif //MINIGL_LIGHT_H