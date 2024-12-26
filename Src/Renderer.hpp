#pragma once

#include <memory>

#include "Camera.hpp"
#include "Image.hpp"
#include "Quad.hpp"
#include "Scene.hpp"
#include "Texture.hpp"

namespace Tracy
{

class Renderer
{
  public:
    void Render(const Scene &scene, const ProjectionCamera &camera);

  private:
    Quad m_Quad;
    std::unique_ptr<Texture> m_Texture;
    std::unique_ptr<Image> m_Image;
};

}; // namespace Tracy
