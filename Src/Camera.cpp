#include "Camera.hpp"

#include <glm/detail/type_quat.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <imgui.h>

namespace Tracy
{

ProjectionCamera::ProjectionCamera(float fov_degrees, size_t width, size_t height, float near_clip, float far_clip)
    : m_FOVDegrees(fov_degrees), m_ViewportWidth(width), m_ViewportHeight(height), m_NearClip(near_clip),
      m_FarClip(far_clip)
{

    const float aspect_ratio = GetAspectRatio();
    m_ViewMatrix = glm::mat4(1.0f);
    m_InverseViewMatrix = glm::inverse(m_ViewMatrix);

    m_ProjectionMatrix = glm::perspective(glm::radians(fov_degrees), aspect_ratio, near_clip, far_clip);
    m_InverseProjectionMatrix = glm::inverse(m_ProjectionMatrix);
}

float ProjectionCamera::GetAspectRatio() const
{
    return static_cast<float>(m_ViewportWidth) / m_ViewportHeight;
}

void ProjectionCamera::MoveTo(const glm::vec3 &position)
{
    Translate(position - m_Position);
}

void ProjectionCamera::Translate(const glm::vec3 &delta)
{
    m_Position += delta;
    const glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), delta);
    m_ViewMatrix = m_ViewMatrix * glm::inverse(translation_matrix);
}

void ProjectionCamera::Rotate(const glm::vec3 &delta)
{
    float pitch = glm::radians(delta.x);
    float yaw = glm::radians(delta.y);
    float roll = glm::radians(delta.z);

    glm::mat4 rx = glm::rotate(glm::mat4(1.0f), pitch, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 ry = glm::rotate(glm::mat4(1.0f), yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rz = glm::rotate(glm::mat4(1.0f), roll, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 rotation = rz * ry * rx;
    m_ViewMatrix = rotation * m_ViewMatrix;
}

const glm::mat4 &ProjectionCamera::GetViewMatrix() const
{
    return m_ViewMatrix;
}

const glm::mat4 &ProjectionCamera::GetInverseViewMatrix() const
{
    return m_InverseViewMatrix;
}

const glm::mat4 &ProjectionCamera::GetProjectionMatrix() const
{
    return m_ProjectionMatrix;
}

const glm::mat4 &ProjectionCamera::GetInverseProjectionMatrix() const
{
    return m_InverseProjectionMatrix;
}

uint32_t ProjectionCamera::GetViewportWidth() const
{
    return m_ViewportWidth;
}
uint32_t ProjectionCamera::GetViewportHeight() const
{
    return m_ViewportHeight;
}

void ProjectionCamera::SetViewport(Size size)
{
    if (size.Width == m_ViewportWidth && size.Height == m_ViewportHeight)
    {
        return;
    }

    m_ViewportWidth = size.Width;
    m_ViewportHeight = size.Height;

    m_ProjectionMatrix = glm::perspective(glm::radians(m_FOVDegrees), GetAspectRatio(), m_NearClip, m_FarClip);
    m_InverseProjectionMatrix = glm::inverse(m_ProjectionMatrix);
}

glm::vec3 ProjectionCamera::GetPosition() const
{
    return m_Position;
}

void ProjectionCamera::Update(float delta_time)
{
    const auto &io = ImGui::GetIO();
    const float translation_speed = 0.1f;
    const float angular_speed = 0.1f;
    bool moved = false;

    constexpr glm::vec3 world_up = {0.0f, 1.0f, 0.0f};
    glm::vec3 right = glm::cross(m_Forward, world_up);
    float yaw = 0.0f;
    float pitch = 0.0f;

    if (io.KeysDown[ImGuiKey_W])
    {
        m_Position += m_Forward * translation_speed * delta_time;
        moved = true;
    }

    if (io.KeysDown[ImGuiKey_S])
    {
        m_Position -= m_Forward * translation_speed * delta_time;
        moved = true;
    }

    if (io.KeysDown[ImGuiKey_A])
    {
        m_Position -= right * translation_speed * delta_time;
        moved = true;
    }

    if (io.KeysDown[ImGuiKey_D])
    {
        m_Position += right * translation_speed * delta_time;
        moved = true;
    }

    if (io.KeysDown[ImGuiKey_E])
    {
        m_Position += world_up * translation_speed * delta_time;
        moved = true;
    }

    if (io.KeysDown[ImGuiKey_Q])
    {
        m_Position -= world_up * translation_speed * delta_time;
        moved = true;
    }

    if (io.KeysDown[ImGuiKey_RightArrow])
    {
        yaw += angular_speed * delta_time;
        moved = true;
    }

    if (io.KeysDown[ImGuiKey_LeftArrow])
    {
        yaw -= angular_speed * delta_time;
        moved = true;
    }

    if (io.KeysDown[ImGuiKey_UpArrow])
    {
        pitch -= angular_speed * delta_time;
        moved = true;
    }

    if (io.KeysDown[ImGuiKey_DownArrow])
    {
        pitch += angular_speed * delta_time;
        moved = true;
    }

    if (yaw != 0.0f || pitch != 0.0f)
    {
        glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitch, right), glm::angleAxis(-yaw, world_up)));
        m_Forward = q * m_Forward;
    }

    if (moved)
    {
        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Forward, world_up);
        m_InverseViewMatrix = glm::inverse(m_ViewMatrix);
    }
}

}; // namespace Tracy
