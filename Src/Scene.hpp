#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Ray.hpp"

namespace Tracy
{

struct Material
{
    glm::vec3 Albedo;
};

struct HitPayload
{
    float HitDistance;
    glm::vec3 WorldPosition;
    glm::vec3 WorldNormal;

    bool Missed() const
    {
        return HitDistance < 0.0f;
    }

    static HitPayload Miss()
    {
        return {.HitDistance = -1.0f};
    }
};

struct Sphere
{
    glm::vec3 Position;
    float Radius = 0.5;

    float Intersects(const Ray &ray) const
    {
        glm::vec3 origin = ray.Origin - Position;

        float a = glm::dot(ray.Direction, ray.Direction);
        float b = 2.0f * glm::dot(origin, ray.Direction);
        float c = glm::dot(origin, origin) - Radius * Radius;

        float discriminant = b * b - 4.0f * a * c;
        if (discriminant < 0.0f)
        {
            return -1.0f;
        }

        return (-b - glm::sqrt(discriminant)) / (2.0f * a);
    }

    HitPayload Hit(const Ray &ray, float distance) const
    {
        HitPayload payload;
        payload.HitDistance = distance;
        payload.WorldPosition = ray.At(distance);
        payload.WorldNormal = glm::normalize(payload.WorldPosition - Position);
        return payload;
    }
};

struct Scene
{
    std::vector<Sphere> spheres;
    std::vector<Material> materials;
};

}; // namespace Tracy
