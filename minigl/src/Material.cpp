//
// Created by Coline Constantinian on 06/11/2025.
//

#include <minigl/Material.h>

mngl::Material::Material() : m_ambientColor(Color::White), m_diffuseColor(Color::White), m_diffuseTexture(Texture::Default),
                             m_specularColor({0.5, 0.5,0.5, 1}), m_specularTexture(Texture::Default), m_shininess(32) {
}

void mngl::Material::SetAmbientColor(Color _ambientColor) {
    m_ambientColor = _ambientColor;
}

void mngl::Material::SetDiffuseColor(Color _diffuseColor) {
    m_diffuseColor = _diffuseColor;
}

void mngl::Material::SetDiffuseTexture(Texture* _diffuseTexture) {
    m_diffuseTexture = _diffuseTexture;
}

void mngl::Material::SetSpecularColor(Color _specularColor) {
    m_specularColor = _specularColor;
}

void mngl::Material::SetSpecularTexture(Texture* _specularTexture) {
    m_specularTexture = _specularTexture;
}

void mngl::Material::SetShininess(float _shininess) {
    m_shininess = _shininess;
}

mngl::Color mngl::Material::GetAmbientColor() const {
    return m_ambientColor;
}

mngl::Color mngl::Material::GetDiffuseColor() const {
    return m_diffuseColor;
}

mngl::Texture* mngl::Material::GetDiffuseTexture() const {
    return m_diffuseTexture;
}

mngl::Color mngl::Material::GetSpecularColor() const {
    return m_specularColor;
}

mngl::Texture* mngl::Material::GetSpecularTexture() const {
    return m_specularTexture;
}

float mngl::Material::GetShininess() const {
    return m_shininess;
}

void mngl::Material::Use() const {
        m_diffuseTexture->Use(0);
        m_specularTexture->Use(1);
}

void mngl::Material::Shutdown() const {
        m_specularTexture->Shutdown();
        m_diffuseTexture->Shutdown();
}
