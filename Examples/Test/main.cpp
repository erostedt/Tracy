#include "OpenGL.hpp"

#include <cstdlib>
#include <memory>

#include "Camera.hpp"
#include "HittableObject.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Sphere.hpp"
#include "Window.hpp"

using namespace Tracy;

const size_t WIDTH = 800;
const size_t HEIGHT = 600;

int main()
{
    auto window = Window::Create("Tracy", WIDTH, HEIGHT);
    auto camera = ProjectionCamera(60, WIDTH, HEIGHT, 0.01f, 100.0f);
    const auto shader = CreateShader("../Shaders/vertex.vert", "../Shaders/fragment.frag");

    GL_CHECK(glUseProgram(shader));
    GL_CHECK(glUniform1i(glGetUniformLocation(shader, "texture1"), 0));

    Renderer renderer;
    std::vector<Material> materials = {{{1.0f, 0.0f, 0.0f}}, {{0.0f, 1.0f, 0.0f}}, {{0.0f, 0.0f, 1.0f}}};
    std::vector<std::shared_ptr<HittableObject>> objects = {
        std::make_shared<Sphere>(glm::vec3{-1.0f, 0.0f, -5.0f}, 0.5f),
        std::make_shared<Sphere>(glm::vec3{1.0f, 0.0f, -5.0f}, 0.5f),
        std::make_shared<Sphere>(glm::vec3{1.6f, 0.0f, -6.0f}, 0.5f),
    };

    const Scene scene = {objects, materials};
    while (window->Show())
    {
        const auto frame = window->NewFrame();
        Size size = frame->GetSize();
        camera.SetViewport(size);
        camera.Update(0.16);
        renderer.Render(scene, camera);
    }

    glDeleteProgram(shader);
    return 0;
}
