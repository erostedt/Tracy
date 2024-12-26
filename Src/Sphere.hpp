#pragma once

#include "HittableObject.hpp"

namespace Tracy
{

struct Sphere : public HittableObject
{
    glm::vec3 Position;
    float Radius;

    Sphere(glm::vec3 position, float radius);
    float IntersectsAt(const Ray &ray) const override;
    HitPayload Hit(const Ray &ray, float distance) const override;
};

}; // namespace Tracy
