#pragma once
#include "OpenGL.hpp"

#include <cassert>
#include <cstdint>

#include "Image.hpp"

namespace Tracy
{

struct TextureParameters
{
    int min_filter;
    int mag_filter;
    int wrap_s;
    int wrap_t;
};

const TextureParameters DEFAULT_TEXTURE_PARAMETERS = {GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};

class Texture
{
  public:
    Texture(size_t width, size_t height, TextureParameters parameters = DEFAULT_TEXTURE_PARAMETERS);
    ~Texture();

    void Bind(uint32_t texture_slot = 0);
    void Unbind();

    void UploadImage(const Image *image);

  private:
    void GenerateTexture(TextureParameters parameters);

  protected:
    size_t m_Width;
    size_t m_Height;
    uint32_t m_ID;
};

}; // namespace Tracy
