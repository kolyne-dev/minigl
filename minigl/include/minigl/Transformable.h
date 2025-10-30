//
// Created by kolyne on 10/29/25.
//

#ifndef MINIGL_TRANSFORMABLE_H
#define MINIGL_TRANSFORMABLE_H

#include <glm/glm.hpp>

namespace mngl
{
    class Transformable
    {
        glm::fvec3 m_position;
        glm::fvec3 m_rotation;
        glm::fvec3 m_scale;

    public:
        virtual ~Transformable() = default;
        Transformable();
        void SetPosition(const glm::fvec3& _position);
        void Move(const glm::fvec3& _position);

        void SetRotation(const glm::fvec3& _rotation);
        void Rotate(const glm::fvec3& _rotation);

        void SetScale(const glm::fvec3& _scale);
        void Scale(const glm::fvec3& _scale);

        [[nodiscard]] glm::mat4 GetTransform() const;
    };
} // mngl

#endif //MINIGL_TRANSFORMABLE_H
