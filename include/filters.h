#pragma once

#include <opencv2/core.hpp>


class Filters
{

public:

    /// \brief Substitute each pixel by the local maxima. The process
    /// is iterative, iterating over different kernel sizes until the
    /// specified maximum is reached.
    static cv::Mat max_filter(cv::Mat& image, int radius);
};