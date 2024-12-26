#pragma once

#include <glm/glm.hpp>

#include "Size.hpp"

namespace Tracy
{

class ProjectionCamera
{

  public:
    ProjectionCamera(float fov_degrees, size_t width, size_t height, float near_clip, float far_clip);

  public:
    float GetAspectRatio() const;

    void MoveTo(const glm::vec3 &position);
    void Translate(const glm::vec3 &delta);

    void Rotate(const glm::vec3 &delta);
    glm::vec3 GetPosition() const;

    void Update(float delta_time);

    const glm::mat4 &GetViewMatrix() const;
    const glm::mat4 &GetInverseViewMatrix() const;

    const glm::mat4 &GetProjectionMatrix() const;
    const glm::mat4 &GetInverseProjectionMatrix() const;

    uint32_t GetViewportWidth() const;
    uint32_t GetViewportHeight() const;
    void SetViewport(Size size);

    glm::vec2 ImageCoordinate(size_t x, size_t y) const;

  private:
    float m_FOVDegrees;
    size_t m_ViewportWidth;
    size_t m_ViewportHeight;
    float m_NearClip;
    float m_FarClip;

    glm::mat4 m_ViewMatrix;
    glm::mat4 m_InverseViewMatrix;

    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_InverseProjectionMatrix;

    glm::vec3 m_Position = glm::vec3{0, 0, 0};
    glm::vec3 m_Forward = glm::vec3{0, 0, -1};
};

}; // namespace Tracy
