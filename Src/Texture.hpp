#pragma once

#include <cassert>
#include <cstdint>

#include "Image.hpp"
#include "OpenGL.hpp"

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
    Texture(size_t width, size_t height, TextureParameters parameters = DEFAULT_TEXTURE_PARAMETERS)
        : m_Width(width), m_Height(height)
    {
        GenerateTexture(parameters);
    }

    ~Texture()
    {
        glDeleteTextures(1, &m_ID);
    }

    void Bind(uint32_t texture_slot = 0)
    {
        glActiveTexture(GL_TEXTURE0 + texture_slot);
        glBindTexture(GL_TEXTURE_2D, m_ID);
    }

    void Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void UploadImage(const Image *image)
    {
        assert(image->GetWidth() == m_Width);
        assert(image->GetHeight() == m_Height);

        Bind();
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, image->GetData());
        Unbind();
    }

  private:
    void GenerateTexture(TextureParameters parameters)
    {
        glGenTextures(1, &m_ID);
        Bind();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, parameters.min_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, parameters.mag_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, parameters.wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, parameters.wrap_t);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        Unbind();
    }

  protected:
    size_t m_Width;
    size_t m_Height;
    uint32_t m_ID;
};

}; // namespace Tracy
