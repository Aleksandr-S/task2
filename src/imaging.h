#pragma once

#include <string>
#include <unordered_map>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

class Imaging
{
public:
    Imaging();

    bool load(const std::string& id, const std::string& fileName);
    bool stor(const std::string& id, const std::string& fileName);
    bool blur(const std::string& idFrom, const std::string& idTo, size_t size);
    bool resize(const std::string& idFrom, const std::string& idTo, size_t width, size_t height);

private:
    std::unordered_map<std::string, cv::Mat> m_images;
};
