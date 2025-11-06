//
// Created by kolyne on 10/30/25.
//

#include <glm/ext/matrix_clip_space.hpp>
#include <minigl/Camera.h>

mngl::Camera::Camera() : m_fov(glm::radians(75.f)), m_aspectRatio(4.f / 3.f), m_zFar(100.f), m_zNear(0.1f)
{
}

void mngl::Camera::SetFOV(float _angle)
{
    m_fov = _angle;
}

void mngl::Camera::SetAspectRatio(float _ratio)
{
    m_aspectRatio = _ratio;
}

glm::mat4 mngl::Camera::GetPerspectiveTransform() const
{
    return glm::perspective(m_fov, m_aspectRatio, m_zNear, m_zFar);
}

void mngl::Camera::SetNearFarPlane(float _zNear, float _zFar)
{
    m_zNear = _zNear;
    m_zFar = _zFar;
}

glm::mat4 mngl::Camera::GetTransform() const {
    return glm::inverse(Transformable::GetTransform());
}
