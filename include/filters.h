#pragma once

#include <opencv2/core.hpp>


class Filters
{

public:

    /// \brief Substitute each pixel by the local maxima
    static cv::Mat max_filter(cv::Mat& image);
};