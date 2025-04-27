#include <iostream>
#include <vector>

struct MandelbrotSet
{
    std::vector<int> image;

    double realMin = -2;
    double realMax = 2;
    double imagMin = -1.5;
    double imagMax = 1.5;

    int m_width;
    int m_height;
    const int m_maxIter;

    MandelbrotSet(int width, int height, int maxIter) 
    : m_width(width), m_height(height), m_maxIter(maxIter)
    {
        image.resize(width * height);
    }
}