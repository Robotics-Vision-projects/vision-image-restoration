#pragma once

#include <opencv2/core.hpp>


class Filters
{

public:

    /// \brief Substitute each pixel by the local maxima. The process
    /// is iterative, iterating over different kernel sizes until the
    /// specified maximum is reached.
    static cv::Mat max_filter(cv::Mat& image, int radius);

    /// \brief Substitute each pixel by the local median, excluding
    /// the maximum and minimum values of the intensity range.
	static cv::Mat adaptive_median_filter(cv::Mat &image, int max_rad);

    /// \brief Increment every pixel by the specified value.
    static cv::Mat intensity_enhancement(cv::Mat &gray_img, int increment);
};