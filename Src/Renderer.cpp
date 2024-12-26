#include "Renderer.hpp"

#include <algorithm>
#include <limits>
#include <memory>

#include "Camera.hpp"
#include "Image.hpp"
#include "Quad.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Texture.hpp"

namespace Tracy
{

static inline RGBA32 ToByteColor(glm::vec4 float_color)
{
    RGBA32 rgba32;
    rgba32.R = std::clamp(float_color.r * 255.0f, 0.0f, 255.0f);
    rgba32.G = std::clamp(float_color.g * 255.0f, 0.0f, 255.0f);
    rgba32.B = std::clamp(float_color.b * 255.0f, 0.0f, 255.0f);
    rgba32.A = std::clamp(float_color.a * 255.0f, 0.0f, 255.0f);
    return rgba32;
}

static glm::vec4 TraceRay(const Ray &ray, const Scene &scene)
{
    size_t closest_sphere_index = std::numeric_limits<size_t>::max();
    float closest_sphere_distance = std::numeric_limits<float>::infinity();
    for (size_t i = 0; i < scene.spheres.size(); ++i)
    {
        const auto &sphere = scene.spheres[i];
        auto distance = sphere.IntersectsAt(ray);
        if (distance > 0.0f && distance < closest_sphere_distance)
        {
            closest_sphere_index = i;
            closest_sphere_distance = distance;
        }
    }

    if (closest_sphere_index == std::numeric_limits<size_t>::max())
    {
        auto a = 2.0f * (glm::normalize(ray.Direction).y + 1.0f);
        auto white = glm::vec4(1.0f);
        auto blue = glm::vec4(0.5f, 0.7f, 1.0f, 1.0f);
        return (1.0f - a) * white + a * blue;
    }

    return {scene.materials.at(closest_sphere_index).Albedo, 1.0};
}

static Ray GenerateRayAt(const ProjectionCamera &camera, uint32_t pixel_x, uint32_t pixel_y)
{
    float x = 2.0f * static_cast<float>(pixel_x) / camera.GetViewportWidth() - 1.0f;
    float y = 2.0f * static_cast<float>(pixel_y) / camera.GetViewportHeight() - 1.0f;
    glm::vec4 target = camera.GetInverseProjectionMatrix() * glm::vec4(x, y, 1.0f, 1.0f);
    glm::vec3 ray_direction =
        glm::vec3(camera.GetInverseViewMatrix() * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0.0f));

    return {camera.GetPosition(), ray_direction};
}

void Renderer::Render(const Scene &scene, const ProjectionCamera &camera)
{
    if (m_Image == nullptr || camera.GetViewportWidth() != m_Image->GetWidth() ||
        camera.GetViewportHeight() != m_Image->GetHeight())
    {
        m_Image = std::make_unique<Image>(camera.GetViewportWidth(), camera.GetViewportHeight());
        m_Texture = (std::make_unique<Texture>(camera.GetViewportWidth(), camera.GetViewportHeight()));
    }

    m_Quad.Bind();

    for (uint32_t y = 0; y < camera.GetViewportHeight(); ++y)
    {
        for (uint32_t x = 0; x < camera.GetViewportWidth(); ++x)
        {
            const auto ray = GenerateRayAt(camera, x, y);
            auto color = TraceRay(ray, scene);
            m_Image->At(x, y) = ToByteColor(color);
        }
    }

    m_Texture->UploadImage(m_Image.get());
    m_Texture->Bind();
    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}

}; // namespace Tracy
