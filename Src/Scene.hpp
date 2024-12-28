#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "HittableObject.hpp"
#include "Material.hpp"

namespace Tracy
{

struct Scene
{
    std::vector<std::shared_ptr<HittableObject>> objects;
    std::vector<Material> materials;
};

}; // namespace Tracy
