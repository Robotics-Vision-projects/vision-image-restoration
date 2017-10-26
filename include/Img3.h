
#pragma once

#include "tools.h"
#include "opencv2/imgproc.hpp"

class Img3
{
private:


public:

    Img3(cv::Mat& src);

    void adaptiveNoiseReduction(int lKernelRadius, int gKernelRadius);

    cv::Mat source;
    cv::Mat result;

};
