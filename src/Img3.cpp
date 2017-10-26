
#include "Img3.h"

using namespace std;

Img3::Img3(cv::Mat &src)
{
    this->source = src;
}

void Img3::adaptiveNoiseReduction(int lKernelRadius, double globDev)
{
    cv::Mat filtered_img(source.size(), CV_8UC1);
    cv::Mat padded(source.rows+lKernelRadius*2, source.cols+lKernelRadius*2, CV_8UC1);
    cv::copyMakeBorder(source, padded, lKernelRadius, lKernelRadius, lKernelRadius, lKernelRadius,
                       cv::BORDER_CONSTANT, cv::mean(source));


    // Go through every pixel and apply the algorithm. f = g - (dev_global/dev_local)*(g - mean_local)
    for (auto row=lKernelRadius; row<(padded.rows-lKernelRadius); ++row){
        for (auto col=lKernelRadius; col<(padded.cols-lKernelRadius); ++col){

            cv::Mat locKernel = padded(cv::Range(row - lKernelRadius, row + lKernelRadius),
                                         cv::Range(col-lKernelRadius, col + lKernelRadius));

            cv::Scalar locMean, locDev;
            cv::meanStdDev(locKernel, locMean, locDev);

            // if the local variance is lower, do nothing
            // this means that we underestimated the noise
            // if local variance is 0, do nothing because we can't divide by 0
            if  (locDev[0] < globDev || locDev[0] == 0)
            {
                filtered_img.at<uchar>(row-lKernelRadius, col-lKernelRadius) = padded.at<uchar>(row, col);
            }
            // otherwise calculate value of f(u,v)
            else
            {

                uchar g = padded.at<uchar>(row, col);
                // use deviation instead of variance for more blurring
                float ratio = globDev/locDev[0];

                // getting f and rounding to nearest integer,
                uchar f = (uchar)(0.5 + g - ratio*(g - locMean[0]));
                filtered_img.at<uchar>(row-lKernelRadius, col-lKernelRadius) = f;
            }
        }
    }

    result = filtered_img.clone();
}

