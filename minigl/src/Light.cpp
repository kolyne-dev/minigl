//
// Created by Coline Constantinian on 06/11/2025.
//

#include <minigl/Light.h>

mngl::Light::Light() : m_ambientColor({0.2f, 0.2f, 0.2f, 1.f}),
                       m_diffuseColor({0.75f, 0.75f, 0.75f, 1.0f}),
                       m_specularColor(Color::White) {
}

void mngl::Light::SetAmbientColor(Color _ambientColor) {
    m_ambientColor = _ambientColor;
}

void mngl::Light::SetDiffuseColor(Color _diffuseColor) {
    m_diffuseColor = _diffuseColor;
}

void mngl::Light::SetSpecularColor(Color _specularColor) {
    m_specularColor = _specularColor;
}

mngl::Color mngl::Light::GetAmbientColor() {
    return m_ambientColor;
}

mngl::Color mngl::Light::GetDiffuseColor() {
    return m_diffuseColor;
}

mngl::Color mngl::Light::GetSpecularColor() {
    return m_specularColor;
}
