#pragma once

#include <glm/glm.hpp>

#include "Ray.hpp"

namespace Tracy
{

struct HitPayload
{
    float HitDistance;
    glm::vec3 WorldPosition;
    glm::vec3 WorldNormal;

    bool Missed() const
    {
        return HitDistance < 0.0f;
    }
};

struct HittableObject
{
    virtual float IntersectsAt(const Ray &ray) const = 0;
    virtual HitPayload Hit(const Ray &ray, float distance) const = 0;
    virtual ~HittableObject() = default;
    static HitPayload Miss()
    {
        return {.HitDistance = -1.0f};
    }
};

}; // namespace Tracy
