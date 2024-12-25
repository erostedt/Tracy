#pragma once
#include "OpenGL.hpp"

#include <array>
#include <cstddef>
#include <glm/glm.hpp>

namespace Tracy
{

struct QuadVertex
{
    glm::vec3 Position;
    glm::vec2 TextureCoordinate;
};

class Quad
{
    using VerticesType = std::array<QuadVertex, 4>;
    using IndicesType = std::array<uint32_t, 6>;

  public:
    Quad()
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

    void Bind()
    {
        glBindVertexArray(m_VertexArrayID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
    }
    void Unbind()
    {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

  private:
    VerticesType m_Vertices = {
        QuadVertex{{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
        QuadVertex{{1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
        QuadVertex{{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        QuadVertex{{-1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    };
    IndicesType m_Indices = {0, 1, 2, 0, 2, 3};

    uint32_t m_VertexArrayID;
    uint32_t m_VertexBufferID;
    uint32_t m_IndexBufferID;
};

}; // namespace Tracy
