
#include "Img3.h"

using namespace std;

Img3::Img3(cv::Mat &src)
{
    this->source = src;
}

cv::Mat Img3::adaptiveNoiseReduction(cv::Mat &image, int lKernelRadius, int gKernelRadius)
{
    cv::Mat filtered_img;
    image.copyTo(filtered_img);
    cv::Mat padded(image.rows+gKernelRadius*2, image.cols+gKernelRadius*2, CV_8UC1);
    cv::copyMakeBorder(image, padded, gKernelRadius, gKernelRadius, gKernelRadius, gKernelRadius,
                       cv::BORDER_CONSTANT, cv::mean(image));


    // Go through every pixel and apply the algorithm. f = g - (var_global/var_local)*(g - mean_local)
    for (auto row=gKernelRadius; row<(padded.rows-gKernelRadius); ++row){
        for (auto col=gKernelRadius; col<(padded.cols-gKernelRadius); ++col){

            cv::Mat locKernel = padded(cv::Range(row - lKernelRadius, row + lKernelRadius),
                                         cv::Range(col-lKernelRadius, col + lKernelRadius));
            cv::Mat globKernel = padded(cv::Range(row - gKernelRadius, row + gKernelRadius),
                                        cv::Range(col-gKernelRadius, col + gKernelRadius));
            vector<float> locMean, globMean, locDev, globDev;
            cv::meanStdDev(locKernel, locMean, locDev);
            cv::meanStdDev(globKernel, globMean, globDev);
            // If the local variance is lower, do nothing
            if  (locDev.begin() < globDev.begin())
            {
                filtered_img.at<uchar>(row-gKernelRadius, col-gKernelRadius) = padded.at<uchar>(row, col);
                continue;
            }
            // Select the maximum value inside the kernel window.
            // the radius will be incremented until a value higher than 0 is
            // found, or the maximum allowed radius is used.
            uchar median = 0;
            for (auto radius=1; radius<=lKernelRadius; ++radius){
                cv::Mat roi_img = padded(cv::Range(row-radius, row+radius),
                                         cv::Range(col-radius, col+radius));
                // Convert the ROI cv::Mat to a std::vector.
                vector<uchar> window(pow(2*radius+1, 2));
                for (auto krow = 0; krow < roi_img.rows; ++krow){
                    for (auto kcol = 0; kcol < roi_img.cols; ++kcol){
                        window[krow*roi_img.cols + kcol] =
                                roi_img.at<uchar>(krow, kcol);
                    }
                }
                // Calculate the vector median value. Break the loop if it is
                // not an extreme value.
                int ksize = pow(radius*2 + 1, 2);
                sort(window.begin(), window.end());
                median = window[ksize/2];
                if (median != 0 && median != 255){
                    break;
                }
            }
            filtered_img.at<uchar>(row-lKernelRadius, col-lKernelRadius) = median;
        }
    }
    return filtered_img;
}
