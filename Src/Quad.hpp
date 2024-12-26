#pragma once

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
    Quad();
    void Bind();
    void Unbind();

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
