#include "OpenGL.hpp"

#include "Texture.hpp"

#include <cassert>
#include <cstdint>

#include "Image.hpp"

namespace Tracy
{

Texture::Texture(size_t width, size_t height, TextureParameters parameters) : m_Width(width), m_Height(height)
{
    GenerateTexture(parameters);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_ID);
}

void Texture::Bind(uint32_t texture_slot)
{
    glActiveTexture(GL_TEXTURE0 + texture_slot);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::UploadImage(const Image *image)
{
    assert(image->GetWidth() == m_Width);
    assert(image->GetHeight() == m_Height);

    Bind();
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, image->GetData());
    Unbind();
}

void Texture::GenerateTexture(TextureParameters parameters)
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

}; // namespace Tracy
