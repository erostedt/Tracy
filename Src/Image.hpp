#pragma once

#include <cstdint>
#include <vector>

namespace Tracy
{

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
    Image(size_t width, size_t height);

    size_t GetWidth() const;
    size_t GetHeight() const;
    size_t GetPixelCount() const;

    const RGBA32 *GetData() const;

    RGBA32 &At(size_t x, size_t y);
    RGBA32 &At(size_t i);

  private:
    size_t m_Width = 0;
    size_t m_Height = 0;
    std::vector<RGBA32> m_Pixels;
};

}; // namespace Tracy
