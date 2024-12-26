#pragma once

#include <glm/glm.hpp>

namespace Tracy
{

struct Ray
{
    glm::vec3 Origin;
    glm::vec3 Direction;

    glm::vec3 At(float t) const
    {
        return Origin + t * Direction;
    }
};

}; // namespace Tracy
