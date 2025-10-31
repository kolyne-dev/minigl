//
// Created by kolyne on 10/31/25.
//

#include <glm/vec3.hpp>
#include <minigl/Utils.h>

#include <glm/detail/func_geometric.inl>

void mngl::Utils::GenerateBasicNormal(float* _vertice, int _nbVertice, int _stride, float* _normalOut)
{
    int indexNormal = 0;
    for (int i = 0; i < _nbVertice*_stride; i += _stride * 3)
    {
        glm::vec3 p1(_vertice[i], _vertice[i+1], _vertice[i+2]);
        glm::vec3 p2(_vertice[i+_stride], _vertice[i+_stride+1], _vertice[i+_stride+2]);
        glm::vec3 p3(_vertice[i+_stride*2], _vertice[i+_stride*2+1], _vertice[i+_stride*2+2]);

        glm::vec3 u = p2 - p1;
        glm::vec3 v = p3 - p1;

        glm::vec3 normal = glm::cross(v, u);
        _normalOut[indexNormal] = normal.x;
        _normalOut[indexNormal+1] = normal.y;
        _normalOut[indexNormal+2] = normal.z;
        _normalOut[indexNormal+3] = normal.x;
        _normalOut[indexNormal+4] = normal.y;
        _normalOut[indexNormal+5] = normal.z;
        _normalOut[indexNormal+6] = normal.x;
        _normalOut[indexNormal+7] = normal.y;
        _normalOut[indexNormal+8] = normal.z;
        indexNormal += 9;
    }
}
