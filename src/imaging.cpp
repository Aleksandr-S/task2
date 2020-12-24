#include "imaging.h"

Imaging::Imaging()
{
}

bool Imaging::load(const std::string& id, const std::string& fileName)
{
    cv::Mat img;
    img = cv::imread(fileName, cv::IMREAD_COLOR);
    if (img.empty())
        return false;
	
    m_images.emplace(std::make_pair(id, img));

    return true;
}

bool Imaging::stor(const std::string& id, const std::string& fileName)
{
	std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_JPEG_QUALITY );
    compression_params.push_back(100);
	
    auto search = m_images.find(id);
    if (search != m_images.end())
        return cv::imwrite(fileName, m_images[id], compression_params);

    return false;
}

bool Imaging::blur(const std::string& idFrom, const std::string& idTo, size_t size)
{
    auto search = m_images.find(idFrom);
    if (search != m_images.end()) {
        cv::Mat &src = m_images[idFrom];
        cv::Mat dst(src);
        cv::blur(src, dst, cv::Size(size, size));

        m_images.emplace(std::make_pair(idTo, dst));

        return true;
	}

    return false;
}

bool Imaging::resize(const std::string& idFrom,
                     const std::string& idTo,
                     size_t width,
                     size_t height)
{
    auto search = m_images.find(idFrom);
    if (search != m_images.end()) {
        cv::Mat &src = m_images[idFrom];
        cv::Mat dst(src);
        cv::Size size(width > 0 ? width : src.cols,
                      height > 0 ? height : src.rows);
        cv::resize(src, dst, size);

        m_images.emplace(std::make_pair(idTo, dst));

        return true;
    }

    return false;
}
