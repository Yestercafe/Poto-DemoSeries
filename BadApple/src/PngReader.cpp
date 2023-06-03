#include "PngReader.h"

#include <cassert>
#include <format>
#include <stb_image.h>
#include <algorithm>
#include <iostream>

PngReader::PngReader(const std::string& fileName) : m_Pixels(nullptr)
{
    m_Pixels = stbi_load(fileName.c_str(), &m_Width, &m_Height, &m_Channel, 0);
    assert(m_Pixels);
    assert(m_Width == 512 && m_Height == 384);
}

PngReader::~PngReader()
{
    if (m_Pixels)
    {
        delete[] m_Pixels;
        m_Pixels = nullptr;
    }
}

void PngReader::GenerateGrayMat()
{
    if (m_GrayMat.has_value()) return;
    m_GrayMat = std::vector(m_Width / FACTOR, std::vector(m_Height / FACTOR, 0.f));
    auto& grayMat = m_GrayMat.value();
    for (int bx = 0; bx < m_Width / FACTOR; ++bx)
    {
        for (int by = 0; by < m_Height / FACTOR; ++by)
        {
            float avg = 0.f;
            for (int ox = 0; ox < FACTOR; ++ox)
            {
                for (int oy = 0; oy < FACTOR; ++oy)
                {
                    unsigned char* pixelOffset = m_Pixels + ((bx * FACTOR + ox) + m_Width * (by * FACTOR + oy)) * m_Channel;
                    unsigned char r = pixelOffset[0];
                    unsigned char g = pixelOffset[1];
                    unsigned char b = pixelOffset[2];
                    float localAvg = (r + g + b) / 3 / 255.f;
                    localAvg = std::clamp(localAvg, 0.f, 1.f);
                    avg += localAvg;
                }
            }
            avg /= FACTOR * FACTOR;

            grayMat[bx][by] = avg;
        }
    }
}
