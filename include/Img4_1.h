
#pragma once

#include "tools.h"

class Img4_1
{
public:
    Img4_1(cv::Mat& src);
    cv::Mat createNotchFilter();


    cv::Mat source;
    cv::Mat result;

};
