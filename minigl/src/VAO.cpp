//
// Created by kolyne on 10/28/25.
//

#include <iostream>
#include <glad/gl.h>
#include <minigl/VAO.h>

mngl::VAO::VAO() :
    m_numberOfVertice(0),
    m_sizeOfStride(0),
    m_VAO(0),
    m_VBO(0)
{
}

mngl::VAO::VAO(void* _verticeData, int _numberOfVertice, int _sizeOfVertice, unsigned int _glDrawType) : VAO()
{
    Create(_verticeData, _numberOfVertice, _sizeOfVertice, _glDrawType);
}

mngl::VAO::~VAO() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}

void mngl::VAO::Create(void* _verticeData, int _numberOfVertice, int _sizeOfVerticeData, unsigned int _glDrawType)
{
    m_numberOfVertice = _numberOfVertice;
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, _sizeOfVerticeData, _verticeData, _glDrawType);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void mngl::VAO::SetAttrib(unsigned int _index, int _nbOfElement, unsigned int _typeOfVertex,
                          unsigned int _normalized, int _sizeOfStride, uint64_t _offset)
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glVertexAttribPointer(_index, _nbOfElement, _typeOfVertex, _normalized, _sizeOfStride, (void*)_offset);
    glEnableVertexAttribArray(_index);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void mngl::VAO::Draw(int _type, int _numberOfVertice) const
{
    glBindVertexArray(m_VAO);
    if (_numberOfVertice == -1)
        _numberOfVertice = m_numberOfVertice;
    glDrawArrays(_type, 0, _numberOfVertice);
    glBindVertexArray(0);
}
