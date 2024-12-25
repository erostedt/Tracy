#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

struct RGBA32
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;
};

class Image
{
  public:
    Image(size_t width, size_t height) : m_Width(width), m_Height(height)
    {
        m_Pixels.clear();
        m_Pixels.reserve(width * height);
        std::fill_n(std::back_inserter(m_Pixels), width * height, RGBA32{0, 0, 0, 255});
    }

    inline size_t GetWidth() const
    {
        return m_Width;
    }

    inline size_t GetHeight() const
    {
        return m_Height;
    }

    inline size_t GetPixelCount() const
    {
        return GetWidth() * GetHeight();
    }

    inline const RGBA32 *GetData() const
    {
        return m_Pixels.data();
    }

    inline RGBA32 &At(size_t x, size_t y)
    {
        return m_Pixels[y * m_Width + x];
    }

    inline RGBA32 &At(size_t i)
    {
        return m_Pixels[i];
    }

  private:
    size_t m_Width = 0;
    size_t m_Height = 0;
    std::vector<RGBA32> m_Pixels;
};
