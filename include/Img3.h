
#pragma once

#include "tools.h"
#include "opencv2/imgproc.hpp"

class Img3
{
private:

    cv::Mat adaptiveNoiseReduction(cv::Mat &image, int lKernelRadius, int gKernelRadius);

public:

    Img3(cv::Mat& src);

    cv::Mat source;
    cv::Mat result;

};
