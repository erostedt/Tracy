#include "OpenGL.hpp"

#include "Quad.hpp"

#include <cstddef>

#include <glm/glm.hpp>

namespace Tracy
{

Quad::Quad()
{
    glGenVertexArrays(1, &m_VertexArrayID);
    glGenBuffers(1, &m_VertexBufferID);
    glGenBuffers(1, &m_IndexBufferID);
    Bind();

    glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices), m_Indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, glm::vec3::length(), GL_FLOAT, GL_FALSE, sizeof(QuadVertex),
                          (void *)offsetof(QuadVertex, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, glm::vec2::length(), GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)offsetof(QuadVertex, TextureCoordinate));
    glEnableVertexAttribArray(1);
    Unbind();
}

void Quad::Bind()
{
    glBindVertexArray(m_VertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
}
void Quad::Unbind()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}; // namespace Tracy
