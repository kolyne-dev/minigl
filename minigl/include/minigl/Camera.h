//
// Created by kolyne on 10/30/25.
//

#ifndef MINIGL_CAMERA_H
#define MINIGL_CAMERA_H
#include "Transformable.h"

namespace mngl
{
    class Camera : public Transformable
    {
        float m_fov;
        float m_aspectRatio;
        float m_zNear;
        float m_zFar;

    public:
        Camera();
        void SetFOV(float _angle);
        void SetAspectRatio(float _ratio);
        [[nodiscard]] glm::mat4 GetPerspectiveTransform() const;
        void SetNearFarPlane(float _zNear, float _zFar);
    };
}

#endif //MINIGL_CAMERA_H
