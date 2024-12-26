#include "Image.hpp"

#include <algorithm>
#include <vector>

namespace Tracy
{

Image::Image(size_t width, size_t height) : m_Width(width), m_Height(height)
{
    m_Pixels.clear();
    m_Pixels.reserve(width * height);
    std::fill_n(std::back_inserter(m_Pixels), width * height, RGBA32{0, 0, 0, 255});
}

size_t Image::GetWidth() const
{
    return m_Width;
}

size_t Image::GetHeight() const
{
    return m_Height;
}

size_t Image::GetPixelCount() const
{
    return GetWidth() * GetHeight();
}

const RGBA32 *Image::GetData() const
{
    return m_Pixels.data();
}

RGBA32 &Image::At(size_t x, size_t y)
{
    return m_Pixels[y * m_Width + x];
}

RGBA32 &Image::At(size_t i)
{
    return m_Pixels[i];
}

}; // namespace Tracy
