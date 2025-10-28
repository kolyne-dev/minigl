//
// Created by kolyne on 10/28/25.
//

#include <glad/gl.h>
#include "../include/VAO.h"

mngl::VAO::VAO(void* _verticeData, int _numberOfVertice, int _sizeOfStride, unsigned int _glDrawType) :
    m_numberOfVertice(_numberOfVertice),
    m_sizeOfStride(_sizeOfStride),
    m_VAO(0),
    m_VBO(0)
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_sizeOfStride * m_numberOfVertice, _verticeData, _glDrawType);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void mngl::VAO::SetAttrib(unsigned int _index, int _nbOfElement, unsigned int _typeOfVertex,
                          unsigned int _normalized, uint64_t _offset)
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glVertexAttribPointer(_index, _nbOfElement, _typeOfVertex, _normalized, m_sizeOfStride, (void*)_offset);
    glEnableVertexAttribArray(_index);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void mngl::VAO::Draw()
{
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, m_numberOfVertice);
    glBindVertexArray(0);
}
