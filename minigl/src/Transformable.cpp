//
// Created by kolyne on 10/29/25.
//

#include <minigl/Transformable.h>

#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <glm/gtx/quaternion.hpp>

mngl::Transformable::Transformable() : m_position({0.f, 0.f, 0.f}),
                                       m_rotation({0.f, 0.f, 0.f}),
                                       m_scale({1.f, 1.f, 1.f})
{
}

void mngl::Transformable::SetPosition(const glm::fvec3& _position)
{
    m_position = _position;
}

void mngl::Transformable::Move(const glm::fvec3& _position)
{
    m_position += _position;
}

void mngl::Transformable::SetRotation(const glm::fvec3& _rotation)
{
    m_rotation = _rotation;
}

void mngl::Transformable::Rotate(const glm::fvec3& _rotation)
{
    m_rotation += _rotation;
}

void mngl::Transformable::SetScale(const glm::fvec3& _scale)
{
    m_scale = _scale;
}

void mngl::Transformable::Scale(const glm::fvec3& _scale)
{
    m_scale *= _scale;
}

glm::mat4 mngl::Transformable::GetTransform() const
{
    return glm::scale(glm::mat4(1.f), m_scale)
           * glm::translate(glm::mat4(1.0f), m_position)
           * glm::toMat4(glm::quat(m_rotation));
}
