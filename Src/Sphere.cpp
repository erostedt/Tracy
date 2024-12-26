#include "Sphere.hpp"

namespace Tracy
{

Sphere::Sphere(glm::vec3 position, float radius) : Position(position), Radius(radius)
{
}

float Sphere::IntersectsAt(const Ray &ray) const
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

HitPayload Sphere::Hit(const Ray &ray, float distance) const
{
    HitPayload payload;
    payload.HitDistance = distance;
    payload.WorldPosition = ray.At(distance);
    payload.WorldNormal = glm::normalize(payload.WorldPosition - Position);
    return payload;
}

}; // namespace Tracy
