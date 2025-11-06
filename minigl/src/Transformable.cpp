//
// Created by kolyne on 10/29/25.
//

#include <minigl/Transformable.h>

#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

mngl::Transformable::Transformable() : m_position({0.f, 0.f, 0.f}),
                                       m_rotation({0.f, 0.f, 0.f}),
                                       m_scale({1.f, 1.f, 1.f})
{
}

glm::fvec3 mngl::Transformable::GetPosition()
{
    return m_position;
}

void mngl::Transformable::SetPosition(const glm::fvec3& _position)
{
    m_position = _position;
}

void mngl::Transformable::Move(const glm::fvec3& _position)
{
    m_position += _position;
}

glm::fvec3 mngl::Transformable::GetRotation()
{
    return m_rotation;
}

void mngl::Transformable::SetRotation(const glm::fvec3& _rotation)
{
    m_rotation = _rotation;
}

void mngl::Transformable::Rotate(const glm::fvec3& _rotation)
{
    m_rotation += _rotation;
}

glm::fvec3 mngl::Transformable::GetScale()
{
    return m_scale;
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
    glm::vec3 invertedZ = {m_position.x, m_position.y, -m_position.z};
    return glm::translate(glm::mat4(1.0f), invertedZ)
        * glm::scale(glm::mat4(1.f), m_scale)
        * glm::toMat4(glm::quat(m_rotation));
}
