#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Sphere.hpp"

namespace Tracy
{

struct Material
{
    glm::vec3 Albedo;
};

struct Scene
{
    std::vector<Sphere> spheres;
    std::vector<Material> materials;
};

}; // namespace Tracy
