#pragma once
#include "OpenGL.hpp"

#include <memory>

#include <glfw3.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Size.hpp"

namespace Tracy
{

class Frame
{
  public:
    Frame(GLFWwindow *window);
    ~Frame();

    Size GetSize();

  private:
    GLFWwindow *m_window;
};

class Window
{
  public:
    std::unique_ptr<Frame> NewFrame();

    void SetBackgroundColor(const glm::vec4 &color);

    void SetBlendingFunction(const uint32_t source_factor, const uint32_t destination_factor);

    bool Show() const;
    bool ShouldClose() const;
    void Close() const;

    GLFWwindow *GetNativeWindow() const;

    static std::unique_ptr<Window> Create(const char *name, int width, int height,
                                          OpenGLVersion gl_version = OPEN_GL_410);

    ~Window();

  private:
    GLFWwindow *m_native_window;
};

}; // namespace Tracy
