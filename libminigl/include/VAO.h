//
// Created by kolyne on 10/28/25.
//

#ifndef MINIGL_VAO_H
#define MINIGL_VAO_H

namespace mngl
{
    class VAO
    {
        unsigned int m_VAO;
        unsigned int m_VBO;
        int m_numberOfVertice;
        int m_sizeOfStride;

    public:
        VAO(void* _verticeData, int _numberOfVertice, int _sizeOfVertice, unsigned int _glDrawType);
        void SetAttrib(unsigned int _index, int _nbOfElement, unsigned int _typeOfVertex,
                       unsigned int _normalized, uint64_t _offset);
        void Draw();
    };

}



#endif //MINIGL_VAO_H