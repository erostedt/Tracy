#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "HittableObject.hpp"

namespace Tracy
{

struct Material
{
    glm::vec3 Albedo;
};

struct Scene
{
    std::vector<std::shared_ptr<HittableObject>> objects;
    std::vector<Material> materials;
};

}; // namespace Tracy
