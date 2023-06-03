#pragma once
#include <string>
#include <vector>
#include <optional>

class PngReader
{
public:
    PngReader(const std::string& fileName);
    ~PngReader();
    using GrayMat = std::vector<std::vector<float>>;
    const GrayMat& GetGrayMat()
    {
        if (!m_GrayMat.has_value())
        {
            GenerateGrayMat();
        }
        return m_GrayMat.value();
    }

    std::pair<int, int> GetSize() const
    {
        return {m_Width / FACTOR, m_Height / FACTOR};
    }
private:
    void GenerateGrayMat();
private:
    std::string m_FileName;
    int m_Width, m_Height, m_Channel;
    unsigned char* m_Pixels;
    static constexpr int FACTOR = 16;
    std::optional<GrayMat> m_GrayMat;
};
